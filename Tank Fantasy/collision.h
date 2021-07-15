#ifndef _COLLISION_H_
#define _COLLISION_H
#include "tank.h"
#include "obstacle.h"
#include "enemy.h"
#include "firebar.h"
#include "boss.h"


bool col_rect_to_rect(float x1,float w1,float y1,float h1,
                      float x2,float w2,float y2,float h2);

bool col_cir_to_cir(float x1,float y1,float r1,
                float x2,float y2,float r2);

void col_push_tank(TANK* tank,
                   float x2,float y2,float w2,float h2,float xo2,float yo2);

void col_tank_obs(TANK* tank, OBSTACLE* obs);

void col_tank_enemy_rect(TANK* tank,ENEMY* enemy);

void col_tank_wall(TANK* tank,OBSTACLE *obs);

void col_tank_spike(TANK* tank,OBSTACLE *obs);

void col_tank_firebar(TANK* tank,FIREBAR *fire);

void col_bullet_enemy(TANK* tank,ENEMY* enemy);

void col_tank_boss(TANK *tank, BOSS_STATE *boss_state);

void col_portal_1(TANK *tank);

void col_portal_2(TANK *tank);
#endif // _COLLISION_H_
