#include "obstacle.h"

void init_wall(OBSTACLE *obstacle_ptr,float wall_data[][4])
{
    int i=0;
    for(i=0;i<WALL_NUM;i++)
    {

        if(wall_data[i][0]==-1)
        {
            obstacle_ptr[i].x=wall_data[i][0];
            break;
        }
        obstacle_ptr[i].x=wall_data[i][0]*2;
        obstacle_ptr[i].y=wall_data[i][1]*2;
        obstacle_ptr[i].ox=obstacle_ptr[i].x;
        obstacle_ptr[i].oy=obstacle_ptr[i].y;
        obstacle_ptr[i].width=wall_data[i][2]*2;
        obstacle_ptr[i].height=wall_data[i][3]*2;
        obstacle_ptr[i].hue=rand()%16*16;
    }
}

void init_spike(OBSTACLE *obs,float data[][2])
{
    int i=0;
    for(i=0;i<OBS_NUM;i++)
    {
        if(data[i][0]==-1)
        {
            obs[i].x=-1;
            break;
        }
        obs[i].x_ofst=18;
        obs[i].y_ofst=18;
        obs[i].x=obs[i].ox=data[i][0]*2-obs[i].x_ofst;
        obs[i].y=obs[i].oy=data[i][1]*2-obs[i].y_ofst;
        obs[i].start_p=obs[i].y;
        obs[i].end_p=obs[i].y+200;
        obs[i].dir=0;
        obs[i].vx=2;
        obs[i].vy=2;
        obs[i].width=200;
        obs[i].height=200;
        obs[i].damage=2;
        obs[i].img=al_load_bitmap("media/pictures/obstacle/spike.png");
    }
}

void obs_move_spike(OBSTACLE *obs)
{
    int i=0;
    for(i=0;i<OBS_NUM;i++)
    {
        if(obs[i].x==-1)
            break;

        if(obs[i].dir==0 && obs[i].y<=obs[i].start_p)
            obs[i].dir=2;
        else if(obs[i].dir==2 && obs[i].y>=obs[i].end_p)
            obs[i].dir=0;
        if(obs[i].dir == 0)
            obs[i].y-=obs[i].vy;
        else if(obs[i].dir == 2)
            obs[i].y+=obs[i].vy;
    }
}

void obs_spike_new(OBSTACLE *obs)
{
    int i=0;
    for(i=0;i<OBS_NUM;i++)
    {
        if(obs[i].x==-1)
            break;
        obs[i].ox=obs[i].x;
        obs[i].oy=obs[i].y;
    }
}



