#include "collision.h"

bool col_rect_to_rect(float x1,float y1,float w1,float h1,
                      float x2,float y2,float w2,float h2)
{
    if( x1 + w1 >= x2 &&    // r1 right edge past r2 left
        x1 <= x2 + w2 &&    // r1 left edge past r2 right
        y1 + h1 >= y2 &&    // r1 top edge past r2 bottom
        y1 <= y2 + h2)
        {
            return true;
        }
        return false;
}

bool col_cir_to_cir(float x1,float y1,float r1,
                float x2,float y2,float r2)
{
    float distx=x1+r1-x2-r2;
    float disty=y1+r1-y2-r2;
    float dist_square=distx*distx+disty*disty;
    float dist_r=r1+r2;
    if(dist_square<dist_r*dist_r)
        return true;
    return false;
}

bool col_circle_to_line(double firebar_left_mid_x, double firebar_left_mid_y,double firebar_right_mid_x,double firebar_right_mid_y,
                       double tank_center_x,double tank_center_y,double tank_r,double firebar_height)
{
    //坦克對火焰棒
    /*內積求距離法
    ex: a.b = |a||b|cosp
        投影距離=|a|cosp
        最短距離=(b*b-(|a|cosp)*(|a|cosp))開根號
    */
    double x1 = firebar_left_mid_x;
    double y1 = firebar_left_mid_y;
    double x2 = firebar_right_mid_x;
    double y2 = firebar_right_mid_y;
    double x3 = tank_center_x;
    double y3 = tank_center_y;
    double vectorx = x1-x2;//火焰棒向量
    double vectory = y1-y2;
    double distance = sqrt(pow(vectorx,2) + pow(vectory,2));//火焰棒距離
    double vector1x = x1-x3;//坦克與火焰棒其中一端點向量
    double vector1y = y1-y3;
    double distance1 = sqrt(pow(vector1x,2) + pow(vector1y,2));//坦克與火焰棒其中一端點距離
    double vector2x = x2-x3;//坦克與火焰棒另一端點向量
    double vector2y = y2-y3;
    double distance2 = sqrt(pow(vector2x,2) + pow(vector2y,2));//坦克與火焰棒另一端點距離
    double sum1 = (vectorx*vector1x + vectory*vector1y)/distance;//內積
    double sum2 = (vectorx*vector2x + vectory*vector2y)/distance;
    double height1 = sqrt(distance1*distance1 - sum1*sum1);//坦克中心到火焰棒最短距離
    double height2 = labs(distance2*distance2 - sum2*sum2);
    height2 = sqrt(height2);
    if(distance1 < distance){
        if(distance2<distance){
            if(height1 < firebar_height/2 + tank_r || height2 < firebar_height/2 + tank_r){
                return true;
            }
            else
                return false;
        }
    }
    return false;
}

void col_push_tank_rect(TANK* tank,
                   float x2,float y2,float w2,float h2,float ox2,float oy2)
{

    if( tank->y+tank->h >= y2 && tank->oy+tank->h < oy2)//top
        tank->y -= (tank->y+tank->h-y2)+0.2;

    else if( tank->y <= y2+h2 && tank->oy > oy2+h2)//bottom
        tank->y += (y2+h2-tank->y)+0.2;

    else if( tank->x+tank->w >= x2 && tank->ox+tank->w < ox2)//right
        tank->x -= (tank->x+tank->w-x2)+0.2;

    else if( tank->x <= x2+w2 && tank->ox > ox2+w2)//left
        tank->x += (x2+w2-tank->x)+0.2;

    return;
}

void col_tank_obs(TANK* tank, OBSTACLE* obs)
{
    if(col_rect_to_rect(tank->x,tank->y,tank->w,tank->h,
                        obs->x,obs->y,obs->width,obs->height))
    {
        col_push_tank_rect(tank,
                      obs->x,obs->y,obs->width,obs->height,obs->ox,obs->oy);
    }
    return;

}

void col_tank_enemy(TANK* tank,ENEMY* enemy)
{
    int i;
    for(i=0;i<ENEMY_NUM;i++)
    {
        if(enemy[i].x==-1)
            break;
        if(enemy[i].alive)
        {

            if(col_rect_to_rect(tank->x,tank->y,tank->w,tank->h,
                                enemy[i].x,enemy[i].y,enemy[i].w,enemy[i].h))
            {
                tank->hp-=enemy[i].damage;
                col_push_tank_rect(tank,
                              enemy[i].x,enemy[i].y,enemy[i].w,enemy[i].h,enemy[i].ox,enemy[i].oy);
            }
        }

    }
    return;
}

void col_tank_wall(TANK* tank,OBSTACLE *obs)
{
    int i=0;
    for(i=0;i<WALL_NUM;i++)
    {
        if(obs[i].x==-1)
            break;
        if(col_rect_to_rect(tank->x,tank->y,tank->w,tank->h,
                            obs[i].x,obs[i].y,obs[i].width,obs[i].height))
        {
            col_push_tank_rect(tank,
                      obs[i].x,obs[i].y,obs[i].width,obs[i].height,obs[i].ox,obs[i].oy);
        }
    }
    return;
}

void col_tank_spike(TANK* tank,OBSTACLE *obs)
{
    int i=0;
    for(i=0;i<OBS_NUM;i++)
    {
        if(obs[i].x==-1)
            break;

        if(col_rect_to_rect(tank->x,tank->y,tank->w,tank->h,
                            obs[i].x+obs[i].x_ofst,
                            obs[i].y+obs[i].y_ofst,
                            obs[i].width,obs[i].height))
        {
            tank->is_damaged=true;
            tank->hp-=obs[i].damage;
            col_push_tank_rect(tank,
                               obs[i].x+obs[i].x_ofst,
                               obs[i].y+obs[i].y_ofst,
                               obs[i].width,obs[i].height,
                               obs[i].ox+obs[i].x_ofst,
                               obs[i].oy+obs[i].y_ofst);
        }
    }
    return;
}

void col_tank_firebar(TANK* tank,FIREBAR *firebar)
{
    int i=0;
    for(i=0;i<FIREBAR_NUM;i++)
    {
        if(firebar[i].x==-1)
                break;
        if(col_circle_to_line(  firebar[i].left_mid_x,firebar[i].left_mid_y,
                                firebar[i].right_mid_x,firebar[i].right_mid_y,
                                tank->center_x,tank->center_y,tank->r,firebar[i].height))
        {
            tank->is_damaged=true;
            tank->hp-=firebar[i].damage;
        }
    }
}

void col_bullet_enemy(TANK* tank,ENEMY* enemy)
{
    int i=0;int j=0;
    for(i=0;i<BULL_NUM;i++)
    {
        if(tank->bullet[i].active)
        {
            for(j=0;j<ENEMY_NUM;j++)
            {
                if(enemy[j].x==-1)
                    break;

                if(enemy[j].alive)
                {
                    if(col_cir_to_cir(tank->bullet[i].x,tank->bullet[i].y,tank->bullet[i].r,
                                enemy[j].x,enemy[j].y,enemy[j].r))
                    {
                        enemy[j].x+=tank->bullet[i].speed
                                    *cos(tank->bullet[i].angle);
                        enemy[j].y-=tank->bullet[i].speed
                                    *sin(tank->bullet[i].angle);
                        tank->bullet[i].active=false;

                        enemy[j].hp-=tank->bullet[i].damage;
                    }
                }

            }

        }

        if(tank->bullet2[i].active)
        {
            for(j=0;j<ENEMY_NUM;j++)
            {
                if(enemy[j].x==-1)
                    break;

                if(enemy[j].alive)
                {
                    if(col_cir_to_cir(tank->bullet2[i].x,tank->bullet2[i].y,tank->bullet2[i].r,
                                enemy[j].x,enemy[j].y,enemy[j].r))
                    {
                        enemy[j].x+=tank->bullet2[i].speed
                                    *cos(tank->bullet2[i].angle);
                        enemy[j].y-=tank->bullet2[i].speed
                                    *sin(tank->bullet2[i].angle);
                        tank->bullet2[i].active=false;

                        enemy[j].hp-=tank->bullet[i].damage;

                    }
                }

            }

        }
    }
}

void col_tank_boss(TANK *tank, BOSS_STATE *boss_state)
{

        if(col_rect_to_rect(tank->x,tank->y,tank->w,tank->h,
                            boss_state->x,boss_state->y,boss_state->width,boss_state->height))
        {
            tank->is_damaged=true;
            tank->hp-=boss_state->damage;

            col_push_tank_rect(tank,
                          boss_state->x,boss_state->y,boss_state->width,boss_state->height,boss_state->ox,boss_state->oy);
        }

    return;

}

void col_portal_1(TANK *tank)
{
    if(col_rect_to_rect(tank->x,tank->y,tank->w,tank->h,
                        600,1400,200,200))
       {
           tank->lvl_up=true;
       }
}

void col_portal_2(TANK *tank)
{
    if(col_rect_to_rect(tank->x,tank->y,tank->w,tank->h,
                        2000,3400,200,200))
       {
           tank->lvl_up=true;
       }
}
