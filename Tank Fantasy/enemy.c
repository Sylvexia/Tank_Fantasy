#include "enemy.h"

void init_enemy_track(ENEMY* enemy,float enemy_data[][2])
{
    int i=0;
    for(i=0;i<ENEMY_NUM;i++)
    {
        if(enemy_data[i][0]==-1)
        {
            enemy[i].x=enemy_data[i][0];
            break;
        }

        enemy[i].x=enemy[i].ox=enemy_data[i][0];
        enemy[i].y=enemy[i].oy=enemy_data[i][1];
        enemy[i].img=al_load_bitmap("media/pictures/enemy/enemy_track.png");
        enemy[i].w=al_get_bitmap_width(enemy[i].img);
        enemy[i].h=al_get_bitmap_height(enemy[i].img);
        enemy[i].r=enemy[i].w/2;

        enemy[i].center_x=enemy[i].x+enemy[i].r;
        enemy[i].center_y=enemy[i].y+enemy[i].r;

        enemy[i].speed=5;
        enemy[i].hp=50;
        enemy[i].damage=0.25;
        enemy[i].alive=false;
        enemy[i].used=false;
        enemy[i].is_damaged=false;
    }

}

void init_enemy_rand(ENEMY* enemy,float enemy_data[][2])
{
    int i=0;
    for(i=0;i<ENEMY_NUM;i++)
    {
        if(enemy_data[i][0]==-1)
        {
            enemy[i].x=enemy_data[i][0];
            break;
        }

        enemy[i].x=enemy[i].ox=enemy_data[i][0];
        enemy[i].y=enemy[i].oy=enemy_data[i][1];
        enemy[i].img=al_load_bitmap("media/pictures/enemy/enemy_random.jpg");
        enemy[i].w=al_get_bitmap_width(enemy[i].img);
        enemy[i].h=al_get_bitmap_height(enemy[i].img);
        enemy[i].r=enemy[i].w/2;

        enemy[i].center_x=enemy[i].x+enemy[i].r;
        enemy[i].center_y=enemy[i].y+enemy[i].r;

        enemy[i].speed=3;
        enemy[i].hp=10;
        enemy[i].damage=0.25;
        enemy[i].alive=false;
        enemy[i].used=false;
        enemy[i].is_damaged=false;
    }

}

float enemy_tank_dist(ENEMY* enemy,TANK* tank)
{
    float dx=tank->x-enemy->x;
    float dy=tank->y-enemy->y;
    return (sqrt(dx*dx+dy*dy));
}

void enemy_track_move(ENEMY* enemy,TANK* tank)
{
    float dist,dx,dy;
    int i;
    for(i=0;i<ENEMY_NUM;i++)
    {
        if(enemy[i].x==-1)
            break;
        if(enemy[i].alive==true)
        {
            dx=tank->x-enemy[i].x;
            dy=tank->y-enemy[i].y;
            dist=sqrt(dx*dx+dy*dy);
            enemy[i].vx=dx/dist*enemy[i].speed;
            enemy[i].vy=dy/dist*enemy[i].speed;

            enemy[i].x+=enemy[i].vx;
            enemy[i].y+=enemy[i].vy;
        }
    }
    return;
}

void enemy_random_move(ENEMY *enemy)
{
    int i=0;
    double unit_step_x=0.0;
    double unit_step_y=0.0;
    srand(time(0));

    for(i=0;i<ENEMY_NUM;i++)
    {
        unit_step_x=rand()%3-1;
        unit_step_y=rand()%3-1;
        if(enemy[i].x==-1)
            break;
        if(enemy[i].alive==true)
        {
                if(enemy[i].x<=0&&enemy[i].y<=0)
                {
                    enemy[i].x=unit_step_x*unit_step_x;
                    enemy[i].y=unit_step_y*unit_step_y;
                    enemy[i].center_x=enemy[i].x+enemy[i].r;
                    enemy[i].center_y=enemy[i].y+enemy[i].r;
                }
                else if(enemy[i].x<=0&&enemy[i].y>0)
                {
                    enemy[i].x=unit_step_x*unit_step_x;
                    enemy[i].y+=unit_step_y*enemy[i].speed;
                    enemy[i].center_x=enemy[i].x+enemy[i].r;
                    enemy[i].center_y=enemy[i].y+enemy[i].r;
                }
                else if(enemy[i].x>0&&enemy[i].y<=0)
                {
                    enemy[i].y=unit_step_y*unit_step_y;
                    enemy[i].x+=unit_step_x*enemy[i].speed;
                    enemy[i].center_x=enemy[i].x+enemy[i].r;
                    enemy[i].center_y=enemy[i].y+enemy[i].r;
                }
                else
                {
                    enemy[i].x+=unit_step_x*enemy[i].speed;
                    enemy[i].y+=unit_step_y*enemy[i].speed;
                    enemy[i].center_x=enemy[i].x+enemy[i].r;
                    enemy[i].center_y=enemy[i].y+enemy[i].r;
                }
        }
    }

}

void enemy_new(ENEMY* enemy,TANK* tank)
{
    int i=0;
    float dist,dx,dy;
    for(i=0;i<ENEMY_NUM;i++)
    {
        if(enemy[i].x==-1)
            break;

        if(!enemy[i].used)
        {
            dx=tank->x-enemy[i].x;
            dy=tank->y-enemy[i].y;
            dist=sqrt(dx*dx+dy*dy);
            if(dist<TRIGGER)
            {
                enemy[i].used=true;
                enemy[i].alive=true;
            }

        }

        if(enemy[i].alive)
        {
            enemy[i].ox=enemy[i].x;
            enemy[i].oy=enemy[i].y;
        }

        if(enemy[i].hp<0)
        {
            enemy[i].alive=false;
        }

    }

}
