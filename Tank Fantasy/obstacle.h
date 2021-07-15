#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define scr_w 1366
#define scr_h 768
#define WALL_NUM 100
#define OBS_NUM 100

typedef struct create_obstacle
{
    float x;
    float y;
    float ox;
    float oy;

    float x_ofst;
    float y_ofst;
    int width;
    int height;

    float vx;
    float vy;

    float start_p;
    float end_p;

    int dir;

    float damage;
    int hue;

    ALLEGRO_BITMAP* img;
}OBSTACLE;

void init_wall(OBSTACLE *obstacle_ptr,float wall_data[][4]);
void init_spike(OBSTACLE *obs,float data[][2]);

void obs_move_spike(OBSTACLE *obs);
void obs_spike_new(OBSTACLE *obs);
#endif // _OBSTACLE_H_


