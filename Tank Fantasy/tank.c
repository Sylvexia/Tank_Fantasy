#include "tank.h"

void init_bullet(BULLET* bullet)
{
    int number=0;

    for(number=0; number<BULL_NUM; number++)
    {
        bullet[number].x=0;
        bullet[number].y=0;
        bullet[number].d=55;
        bullet[number].speed=10;
        bullet[number].r=10;
        bullet[number].angle=0;
        bullet[number].active=false;
        bullet[number].hp=100;
        bullet[number].damage=5;
    }
}

void init_bullet2(BULLET* bullet)
{
    int number=0;

    for(number=0; number<BULL_NUM; number++)
    {
        bullet[number].x=0;
        bullet[number].y=0;
        bullet[number].d=55;
        bullet[number].speed=15;
        bullet[number].r=5;
        bullet[number].angle=0;
        bullet[number].active=false;
        bullet[number].hp=100;
        bullet[number].damage=3;
    }
}

void init_tank(TANK* tank_ptr,BULLET* bullet,BULLET* bullet2)
{
    tank_ptr->img=al_load_bitmap("media/pictures/tank/tank.png");

    tank_ptr->x=800;
    tank_ptr->y=700;
    tank_ptr->center_x=tank_ptr->x + tank_ptr->r;
    tank_ptr->center_y=tank_ptr->y + tank_ptr->r;

    tank_ptr->r=al_get_bitmap_height(tank_ptr->img)/2;
    tank_ptr->w=2*tank_ptr->r;
    tank_ptr->h=2*tank_ptr->r;
    tank_ptr->angle=0;
    tank_ptr->speed=10;
    tank_ptr->vx=0;
    tank_ptr->vy=0;
    tank_ptr->dir=1;
    tank_ptr->hp=tank_ptr->max_hp=100;

    tank_ptr->auto_shoot=false;
    tank_ptr->is_damaged=false;
    tank_ptr->lvl_up=false;
    tank_ptr->reload=al_create_timer(1/10.0);
    tank_ptr->reload2=al_create_timer(1/5.0);

    tank_ptr->bullet=bullet;
    tank_ptr->bullet2=bullet2;
}

void destroy_tank(TANK* tank)
{
    al_destroy_bitmap(tank->img);
    al_destroy_timer(tank->reload);
    al_destroy_timer(tank->reload2);
}

//==========================================

void tank_auto_able(TANK *tank)
{
    tank->auto_shoot=true;
    al_start_timer(tank->reload);
    al_start_timer(tank->reload2);
}

void tank_auto_disable(TANK *tank)
{
    tank->auto_shoot=false;
    al_stop_timer(tank->reload);
    al_stop_timer(tank->reload2);
}

void tank_is_damaged(TANK *tank_ptr,OBSTACLE *obstacle_ptr)
{
    float centerX=tank_ptr->center_x;
    float centerY=tank_ptr->center_y;
    float obstacleX=obstacle_ptr->x + obstacle_ptr->width/2;
    float obstacleY=obstacle_ptr->y + (obstacle_ptr->height/2);
    if(centerX - obstacleX < (obstacle_ptr->width + tank_ptr->r*2)/2 &&
       centerX - obstacleX > -(obstacle_ptr->width + tank_ptr->r*2)/2){
            if(centerY - obstacleY < (obstacle_ptr->height + tank_ptr->r*2)/2 &&
                centerY - obstacleY > -(obstacle_ptr->height + tank_ptr->r*2)/2){
                tank_ptr->is_damaged=true;
                tank_ptr->hp-=obstacle_ptr->damage;
            }
            else{
                tank_ptr->is_damaged=false;
            }
    }
    else{
        tank_ptr->is_damaged=false;
    }
}

void tank_center_coord(TANK *tank)
{
    tank->center_x=tank->x + tank->r;
    tank->center_y=tank->y + tank->r;
}

void tank_shoot(TANK* tank)
{
    int i=0;

    for(i=0;i<BULL_NUM;i++)
    {
        if(!tank->bullet[i].active)
        {
            tank->bullet[i].active=true;
            tank->bullet[i].angle=tank->angle;
            tank->bullet[i].d= tank->r;

            tank->bullet[i].x=  tank->center_x+
                                (tank->bullet[i].r+tank->bullet[i].d)
                                *(cos (tank->bullet[i].angle) );

            tank->bullet[i].y=  tank->center_y-
                                (tank->bullet[i].r+tank->bullet[i].d)
                                *(sin (tank->bullet[i].angle) );
            break;
        }
    }
}

void tank_shoot2(TANK* tank)
{
    int i=0;

    for(i=0;i<BULL_NUM;i++)
    {
        if(!tank->bullet2[i].active)
        {
            tank->bullet2[i].active=true;
            tank->bullet2[i].angle=tank->angle+3.14;
            tank->bullet2[i].d= tank->r;

            tank->bullet2[i].x=  tank->center_x+
                                (tank->bullet2[i].r+tank->bullet2[i].d)
                                *(cos (tank->bullet2[i].angle) );

            tank->bullet2[i].y=  tank->center_y-
                                (tank->bullet2[i].r+tank->bullet2[i].d)
                                *(sin (tank->bullet2[i].angle) );
            break;
        }
    }
}

void tank_bullet_move(TANK *tank)
{
    int i=0;
    for(i=0;i<BULL_NUM;i++)
    {
        if(tank->bullet[i].active)
        {
            if(tank->bullet[i].d>bulletRange)//deactivate condition
            {
                tank->bullet[i].active=false;
            }

            //move
            tank->bullet[i].x+= tank->bullet[i].speed
                                *cos(tank->bullet[i].angle);

            tank->bullet[i].y-= tank->bullet[i].speed
                                *sin(tank->bullet[i].angle);

            tank->bullet[i].d+= tank->bullet[i].speed;
        }
    }
    for(i=0;i<BULL_NUM;i++)
    {
        if(tank->bullet2[i].active)
        {
            if(tank->bullet2[i].d>bulletRange)//deactivate condition
            {
                tank->bullet2[i].active=false;
            }

            //move
            tank->bullet2[i].x+= tank->bullet2[i].speed
                                *cos(tank->bullet2[i].angle);

            tank->bullet2[i].y-= tank->bullet2[i].speed
                                *sin(tank->bullet2[i].angle);

            tank->bullet2[i].d+= tank->bullet2[i].speed;
        }
    }
}

void tank_new(TANK *tank)
{
    tank->vx=0;
    tank->vy=0;
    tank->ox=tank->x;
    tank->oy=tank->y;
    tank->is_damaged=false;
}
