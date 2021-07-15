#ifndef _TANK_H
#define _TANK_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "obstacle.h"

#define scr_w 1366
#define scr_h 768
#define BULL_NUM 300
#define bulletRange 1400

typedef struct BULLET
{
    bool active;
    int r;
    int hp;
    int damage;
    float x;
    float y;
    float d;
    float speed;
    float angle;

    float vx;
    float vy;
}BULLET;

typedef struct TANK
{
    float x;
    float y;
    float ox;
    float oy;
    float center_x;
    float center_y;

    float r;
    float h;
    float w;

    float angle;
    float speed;

    int dir;
    float vx;
    float vy;
    float hp;
    float max_hp;

    bool is_damaged;
    bool auto_shoot;
    bool lvl_up;

    ALLEGRO_BITMAP* img;
    ALLEGRO_TIMER* reload;
    ALLEGRO_TIMER* reload2;

    BULLET* bullet;
    BULLET* bullet2;

} TANK;

void init_tank(TANK* tank_ptr,BULLET* bullet,BULLET* bullet2);
void init_bullet(BULLET* bullet);
void destroy_tank(TANK* tank);

void tank_auto_able(TANK *tank);
void tank_auto_disable(TANK *tank);
void tank_is_damaged(TANK *tank_ptr,OBSTACLE *obstacle_ptr);
void tank_center_coord(TANK* tank);
void tank_shoot(TANK *tank);
void tank_shoot2(TANK *tank);
void tank_bullet_move(TANK *tank);
void tank_new(TANK *tank);

#endif // _TANK_H
