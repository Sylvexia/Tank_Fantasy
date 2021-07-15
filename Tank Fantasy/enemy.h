#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tank.h"

#define ENEMY_NUM 100
#define TRIGGER 700

typedef struct ENEMY
{
    float x;
    float y;
    float ox;
    float oy;
    float w;
    float h;
    float r;
    float center_x;
    float center_y;
    float vx;
    float vy;

    float speed;
    float hp;
    float damage;
    bool alive;
    bool used;

    bool is_damaged;

    ALLEGRO_BITMAP* img;

} ENEMY;


void init_enemy_track(ENEMY* enemy,float wall_data[][2]);
void init_enemy_rand(ENEMY* enemy,float enemy_data[][2]);
void enemy_center(ENEMY *enemy);
void enemy_update(ENEMY *enemy);
void enemy_random_move(ENEMY* enemy);
void enemy_track_move(ENEMY* enemy,TANK* tank);
void enemy_new(ENEMY* enemy,TANK* tank);

float enemy_tank_dist(ENEMY* enemy,TANK* tank);
#endif
