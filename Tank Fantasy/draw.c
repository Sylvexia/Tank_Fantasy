#include "draw.h"

void draw_start(START_SCREEN start)
{
    al_draw_bitmap(start.startscreen,0,0,0);
    al_draw_bitmap(start.startbut.img,start.startbut.but_x,
                   start.startbut.but_y,0);
    al_draw_bitmap(start.rankbut.img,start.rankbut.but_x,
                   start.rankbut.but_y,0);
    al_draw_bitmap(start.quitbut.img,start.quitbut.but_x,
                   start.quitbut.but_y,0);
}

void draw_start_show_button(START_SCREEN start,ALLEGRO_MOUSE_STATE* mouse_state)
{
    if( start.startbut.but_x<=mouse_state->x &&
        mouse_state->x      <=start.startbut.but_x+start.startbut.but_w)
    {
        if( start.startbut.but_y <=mouse_state->y &&
            mouse_state->y       <start.startbut.but_y+start.startbut.but_h)
        {
            al_draw_rectangle(  start.startbut.but_x,
                                start.startbut.but_y,
                                start.startbut.but_x+start.startbut.but_w,
                                start.startbut.but_y+start.startbut.but_h,
                                al_map_rgb(255,255,255),1);
        }

        else if(start.rankbut.but_y  <=mouse_state->y &&
                mouse_state->y      <start.rankbut.but_y+start.rankbut.but_h)
        {
            al_draw_rectangle(  start.rankbut.but_x,
                                start.rankbut.but_y,
                                start.rankbut.but_x+start.rankbut.but_w,
                                start.rankbut.but_y+start.rankbut.but_h,
                               al_map_rgb(255,255,255),1);
        }
        else if(start.quitbut.but_y <=mouse_state->y &&
                mouse_state->y      <=start.quitbut.but_y+start.quitbut.but_h)
        {
            al_draw_rectangle(  start.quitbut.but_x,
                                start.quitbut.but_y,
                                start.quitbut.but_x+start.quitbut.but_w,
                                start.quitbut.but_y+start.quitbut.but_h,
                                al_map_rgb(255,255,255),1);
        }
    }
}

void draw_setting(START_SCREEN start)
{
    al_draw_bitmap(start.startscreen,0,0,0);
    al_draw_bitmap(start.returnbut.img,
                   start.returnbut.but_x,
                   start.returnbut.but_y,0);
}

void draw_setting_show_button(START_SCREEN start,ALLEGRO_MOUSE_STATE* mouse_state)
{
    if(mouse_state->x > start.returnbut.but_x&&
       mouse_state->x < start.returnbut.but_x + start.returnbut.but_w)
       {
           if(mouse_state->y > start.returnbut.but_y&&
              mouse_state->y < start.returnbut.but_y + start.returnbut.but_h)
              {
                  al_draw_rectangle(start.returnbut.but_x,
                                    start.returnbut.but_y,
                                    start.returnbut.but_x + start.returnbut.but_w,
                                    start.returnbut.but_y + start.returnbut.but_h,
                                    al_map_rgb(255,255,255),1);
              }
       }
}

void draw_rank(START_SCREEN start)
{
    al_draw_bitmap(start.rankscreen,0,0,0);
    al_draw_bitmap(start.returnbut.img,
                   1165,695,0);
}

void draw_rank_show_button(START_SCREEN start,ALLEGRO_MOUSE_STATE* mouse_state)
{
    if(mouse_state->x > 1165&&
       mouse_state->x < 1165 + start.returnbut.but_w)
       {
           if(mouse_state->y > 695&&
              mouse_state->y < 695 + start.returnbut.but_h)
              {
                  al_draw_rectangle(1165,695,1165 + start.returnbut.but_w,695 + start.returnbut.but_h,
                                    al_map_rgb(255,255,255),1);
              }
       }

}

void draw_score(int *score,time_t t1,time_t t2,ALLEGRO_FONT *font,CAMERA* cam)
{

    t2 = time(NULL);
    al_draw_textf(font, al_map_rgb(255,0,0), scr_w/2+cam->cameraPosition[0] , cam->cameraPosition[1], ALLEGRO_ALIGN_CENTRE,"score : %d",*score-(t2-t1));
}

void draw_lvupscreen(LEVELUP lvup)
{
    al_draw_bitmap(lvup.lvupscreen,0,0,0);
    al_draw_bitmap(lvup.s1.img,lvup.s1.but_x,lvup.s1.but_y,0);
    al_draw_bitmap(lvup.s2.img,lvup.s2.but_x,lvup.s2.but_y,0);
    al_draw_bitmap(lvup.s3.img,lvup.s3.but_x,lvup.s3.but_y,0);
}

void draw_lvup1_show_button(ALLEGRO_MOUSE_STATE* mouse_state,LEVELUP lvup,ALLEGRO_FONT *font){

    if(lvup.s1.but_y<=mouse_state->y &&
       mouse_state->y<=lvup.s1.but_y+lvup.s1.but_h){
        if(lvup.s1.but_x<=mouse_state->x &&
            mouse_state->x<=lvup.s1.but_x+lvup.s1.but_w){
            al_draw_rectangle(  lvup.s1.but_x,
            lvup.s1.but_y,
            lvup.s1.but_x+lvup.s1.but_w,
            lvup.s1.but_y+lvup.s1.but_h,
            al_map_rgb(255,255,255),1);
            al_draw_textf(font, al_map_rgb(255,0,0), 300 , 400, ALLEGRO_ALIGN_LEFT,"multiple attact ");
            }

        else if(lvup.s2.but_x<=mouse_state->x &&
        mouse_state->x<=lvup.s2.but_x+lvup.s2.but_w){

            al_draw_rectangle(  lvup.s2.but_x,
            lvup.s2.but_y,
            lvup.s2.but_x+lvup.s2.but_w,
            lvup.s2.but_y+lvup.s2.but_h,
            al_map_rgb(255,255,255),1);
            al_draw_textf(font, al_map_rgb(255,0,0), 300 , 400, ALLEGRO_ALIGN_LEFT,"increase your speed ");
            }

        else if(lvup.s3.but_x<=mouse_state->x &&
        mouse_state->x<=lvup.s3.but_x+lvup.s3.but_w){

            al_draw_rectangle(  lvup.s3.but_x,
            lvup.s3.but_y,
            lvup.s3.but_x+lvup.s3.but_w,
            lvup.s3.but_y+lvup.s3.but_h,
            al_map_rgb(255,255,255),1);
            al_draw_textf(font, al_map_rgb(255,0,0), 300 , 400, ALLEGRO_ALIGN_LEFT,"increase your attack speed ");
            }
       }
}

void draw_lvup2_show_button(ALLEGRO_MOUSE_STATE* mouse_state,LEVELUP lvup,ALLEGRO_FONT *font){

    if(lvup.s1.but_y<=mouse_state->y &&
       mouse_state->y<=lvup.s1.but_y+lvup.s1.but_h){
        if(lvup.s1.but_x<=mouse_state->x &&
            mouse_state->x<=lvup.s1.but_x+lvup.s1.but_w){
            al_draw_rectangle(  lvup.s1.but_x,
            lvup.s1.but_y,
            lvup.s1.but_x+lvup.s1.but_w,
            lvup.s1.but_y+lvup.s1.but_h,
            al_map_rgb(255,255,255),1);
            al_draw_textf(font, al_map_rgb(255,0,0), 300 , 400, ALLEGRO_ALIGN_LEFT,"increase your attack strenght ");
            }

        else if(lvup.s2.but_x<=mouse_state->x &&
        mouse_state->x<=lvup.s2.but_x+lvup.s2.but_w){

            al_draw_rectangle(  lvup.s2.but_x,
            lvup.s2.but_y,
            lvup.s2.but_x+lvup.s2.but_w,
            lvup.s2.but_y+lvup.s2.but_h,
            al_map_rgb(255,255,255),1);
            al_draw_textf(font, al_map_rgb(255,0,0), 300 , 400, ALLEGRO_ALIGN_LEFT,"increase your bullet speed ");
            }

        else if(lvup.s3.but_x<=mouse_state->x &&
        mouse_state->x<=lvup.s3.but_x+lvup.s3.but_w){

            al_draw_rectangle(  lvup.s3.but_x,
            lvup.s3.but_y,
            lvup.s3.but_x+lvup.s3.but_w,
            lvup.s3.but_y+lvup.s3.but_h,
            al_map_rgb(255,255,255),1);
            al_draw_textf(font, al_map_rgb(255,0,0), 300 , 400, ALLEGRO_ALIGN_LEFT,"increase your hp ");
            }
       }
}

void draw_backbround(ALLEGRO_BITMAP *background)
{
    al_draw_bitmap(background,0,0,0);
}

void draw_wall(OBSTACLE *obs)
{
    int i=0;
    for(i=0;i<WALL_NUM;i++)
    {
        if(obs[i].x==-1)
            break;
        al_draw_filled_rectangle(obs[i].x,obs[i].y,
                  obs[i].x+obs[i].width,obs[i].y+obs[i].height,
                  al_color_hsv(obs[i].hue,0.8,0.8));
        al_draw_rectangle(obs[i].x,obs[i].y,
                          obs[i].x+obs[i].width,obs[i].y+obs[i].height,
                          al_color_hsv(0,0,1),3);
    }
}

void draw_spike(OBSTACLE *obs)
{
    int i=0;
    for(i=0;i<OBS_NUM;i++)
    {
        if(obs[i].x==-1)
            break;

        al_draw_bitmap(obs[i].img,obs[i].x,obs[i].y,0);
    }
}

void draw_firebar(FIREBAR *firebar)
{
    int i=0;
    for(i=0;i<FIREBAR_NUM;i++){
        if(firebar[i].x==-1)
            break;
        al_draw_rotated_bitmap(firebar[i].img,firebar[i].width/2,firebar[i].height/2,firebar[i].centerx,firebar[i].centery,
                                  firebar[i].angle,0);
    }

}

void draw_tank(TANK* tank)
{

    al_draw_rotated_bitmap(tank->img,tank->r,tank->r,
                                   tank->center_x,tank->center_y,
                                   -tank->angle,0);    //preangle前面要加負號(定義)
//    al_draw_rectangle(tank->x,tank->y,tank->x+tank->w,tank->y+tank->h,
//                      al_map_rgb(255,255,255),1);
}

void draw_damaged_tank(TANK* tank)
{
    if(tank->is_damaged==true)
    {
        al_draw_tinted_rotated_bitmap(tank->img,al_map_rgb(255,0,0),
            tank->r,tank->r,tank->center_x,tank->center_y,
            -tank->angle,0);
    }
}

void draw_tank_health_bar(TANK* tank)
{
    if(tank->hp>0)
    {
        al_draw_line(tank->x,tank->y+tank->r*2,
                    tank->x+(tank->hp/tank->max_hp)*tank->r*2,tank->y+tank->r*2,
                    al_map_rgb(124,252,0),3);
    }
}

void draw_tank_aim(ALLEGRO_MOUSE_STATE* mouse_state,TANK* tank,CAMERA *cam)
{
    float mouseX,mouseY;

    if(mouse_state->buttons & 1){
        mouseX=mouse_state->x+cam->cameraPosition[0];
        mouseY=mouse_state->y+cam->cameraPosition[1];
        al_draw_line(tank->center_x, tank->center_y, mouseX, mouseY,
                        al_map_rgb(255,255,255), 1);
    }
}

void draw_tank_bullet(TANK* tank)
{
    int i=0;
    for(i=0;i<BULL_NUM;i++)
    {
        if(!tank->bullet[i].active)
            continue;
        if(tank->bullet[i].active)
        {
            al_draw_filled_circle(tank->bullet[i].x,tank->bullet[i].y,
                                  tank->bullet[i].r,al_map_rgb(255,255,255));

        }
    }

    for(i=0;i<BULL_NUM;i++)
    {
        if(!tank->bullet2[i].active)
            continue;
        if(tank->bullet2[i].active)
        {
            al_draw_filled_circle(tank->bullet2[i].x,tank->bullet2[i].y,
                                  tank->bullet2[i].r,al_map_rgb(255,255,255));

        }
    }
}

void draw_enemy(ENEMY *enemy)
{
    int i=0;
    for(i=0;i<ENEMY_NUM;i++)
    {
        if(enemy[i].x==-1)
            break;
        if(enemy[i].alive==true)
        {
            al_draw_bitmap(enemy[i].img,enemy[i].x,enemy[i].y,0);
        }
    }
}

void draw_boss_health_bar(BOSS_STATE *boss_state,CAMERA *camera)
{

    double hp= (boss_state->hp / total_hp)*scr_w;

    int bottom=10+camera->cameraPosition[0];//hp的底線位置

    if(boss_state->hp >0)
    {
//血條
        al_draw_line(bottom,30+camera->cameraPosition[1],
                     bottom+hp,30+camera->cameraPosition[1],
                     al_map_rgb(124,252,0),30);

//血框
        al_draw_rectangle(bottom,15+camera->cameraPosition[1],
                          bottom+scr_w,45+camera->cameraPosition[1],
                          al_map_rgb(180,252,0),5);

    }

}

void draw_boss_bullet(BOSS_STATE *boss_state)
{
    int i=0;
    for(i=0; i<ballnum; i++)
    {
        if(!boss_state->bullet[i].active)
            continue;
        if(boss_state->bullet[i].active)
        {
            al_draw_filled_circle(boss_state->bullet[i].x,boss_state->bullet[i].y,
                                  boss_state->bullet[i].r,al_map_rgb(130,0,0));


        }
    }
}

void draw_boss_bitmap(BOSS_STATE *boss_state)
{
    if(boss_state->hp > 0)
    {

        if(boss_state->is_damaged==true)
            draw_damaged_boss(boss_state);
        else
            al_draw_bitmap(boss_state->img,boss_state->x,boss_state->y,0);

    }


}

void draw_damaged_boss(BOSS_STATE* boss_state)
{
    if(boss_state->is_damaged==true)
    {
        al_draw_tinted_bitmap(boss_state->img,al_map_rgb(255,0,0),
                              boss_state->x,boss_state->y,0);
    }

    boss_state->is_damaged=false;
}

//比例血條
void draw_ptank_health_bar(TANK *tank)
{

    double hp= (tank->hp / tank->max_hp)*tank->w;

    double bottom=tank->x;//hp的底線位置
    double height=tank->y+tank->h;
    if(tank->hp >0)
    {
//血條
        al_draw_line(bottom,height,
                     bottom+hp,height,
                     al_map_rgb(124,252,0),4);


    }

}

void draw_bs_psi(BOSS_STATE *boss_state,TANK *tank,CAMERA *camera)
{

        double distance=0.0;
        int dx=0,dy=0;

        double vectorx=0.0;
        double vectory=0.0;

        dx=tank->center_x-(boss_state->x+boss_state->width/2);
        dy=tank->center_y-(boss_state->y+boss_state->height/2);
        distance=sqrt(dx*dx+dy*dy);
        vectorx=dx/distance;
        vectory=dy/distance;

        double x1=1200+camera->cameraPosition[0];
        double y1=80+camera->cameraPosition[1];

        double x2=x1+60*vectorx;
        double y2=y1+60*vectory;

        double x3=x1+10*vectorx;
        double y3=y1+10*vectory;

        al_draw_line(x1,y1,x2,y2,al_map_rgb(50,50,50),30);
        al_draw_line(x1,y1,x3,y3,al_map_rgb(100,100,100),30);






}
void draw_portal_1()
{
    al_draw_filled_rectangle(600,1400,800,1600,al_map_rgb(255,255,255));
}

void draw_portal_2()
{
    al_draw_filled_rectangle(2000,3400,2200,3600,al_map_rgb(255,255,255));
}
