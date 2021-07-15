#ifndef _DRAW_H_
#define _DRAW_H_

#include "tank.h"
#include "obstacle.h"
#include "camera.h"
#include "level.h"
#include "enemy.h"
#include "firebar.h"
#include "boss.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

void draw_start(START_SCREEN start);
void draw_start_show_button(START_SCREEN start,ALLEGRO_MOUSE_STATE* mouse_state);
void draw_setting(START_SCREEN start);
void draw_setting_show_button(START_SCREEN,ALLEGRO_MOUSE_STATE* mouse_state);
void draw_lvup1_show_button(ALLEGRO_MOUSE_STATE* mouse_state,LEVELUP lvup,
                            ALLEGRO_FONT *font);
void draw_lvup2_show_button(ALLEGRO_MOUSE_STATE* mouse_state,LEVELUP lvup,
                            ALLEGRO_FONT *font);
void draw_backbround(ALLEGRO_BITMAP *background);
void draw_wall(OBSTACLE *obs);
void draw_firebar(FIREBAR *firebar);
void draw_spike(OBSTACLE *obs);
void draw_tank(TANK* tank0);
void draw_tank_health_bar(TANK* tank);
void draw_tank_aim(ALLEGRO_MOUSE_STATE* mouse_state,TANK* tank,CAMERA* cam);
void draw_tank_bullet(TANK* tank);
void draw_damaged_tank(TANK* tank);
void draw_enemy(ENEMY *enemy);
void draw_score(int *score,time_t t1,time_t t2,ALLEGRO_FONT *font,CAMERA* cam);
void draw_lvupscreen(LEVELUP lvup);

void draw_boss_health_bar(BOSS_STATE *boss_state,CAMERA *camera);
void draw_boss_bullet(BOSS_STATE *boss_state);
void draw_boss_bitmap(BOSS_STATE *boss_state);
void draw_damaged_boss(BOSS_STATE* boss_state);
void draw_ptank_health_bar(TANK *tank);//¤ñ¨Ò¦å±ø
void draw_bs_psi(BOSS_STATE *boss_state,TANK *tank,CAMERA *camera);

void draw_portal_1();
void draw_portal_2();

#endif // _DRAW_H_
