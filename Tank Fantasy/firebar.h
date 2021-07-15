#ifndef _FIREBAR_H_
#define _FIREBAR_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <math.h>
#include "tank.h"
//#include "collision.h"

#define scr_w 1366
#define scr_h 768
#define FIREBAR_NUM 30

typedef struct create_firebar
{
    float x;
    float y;
    int width;
    int height;
    float damage;
    ALLEGRO_BITMAP* img;
    float r;
    float angle;
    int dir;
    float speed;
    float left_mid_x;
    float left_mid_y;
    float right_mid_x;
    float right_mid_y;
    float centerx;
    float centery;
    float turn_speed;
}FIREBAR;
void init_firebar(FIREBAR *firebar_ptr,float firebar_data[][2],float turnspeed[][1]);
//void init_firebar(FIREBAR *firebar_ptr);
void firebar_rotate(TANK* tank,FIREBAR *firebar);
void init_firebar2(FIREBAR *firebar_ptr);


#endif // _OBSTACLE_H_




