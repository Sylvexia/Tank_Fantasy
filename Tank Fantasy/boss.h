
#ifndef boss_h
#define boss_h

#define ballnum 628
#define angle_num 24
#define total_hp 1000

//當作坦克子彈碰撞用的長寬
#define tb_width 20
#define tb_height 20


#include "tank.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
//#include <allegro5/allegro_image.h>



typedef struct TIME_COUNTER{

    int timer;
    bool active;
    int finish;

}T_COUNTER;



typedef enum {

    bRIGHT,
    bLEFT,
    bDOWN,
    bUP,
    bSTATIC

}DIR;


typedef struct{

    double x;
    double y;

    double angle;
    double d;

    double damage;


}LASER;


typedef struct {

    ALLEGRO_BITMAP* img;
    double x;
    double y;

    double ox;
    double oy;

    double center_x;
    double center_y;

    double recx;//爆炸區使用
    double recy;

    double width;
    double height;

    double hp;
    double angle[angle_num];
    double r;

    int speed;
    int damage;
    int mode;
    bool is_damaged;

    DIR dir;

    BULLET *bullet;

    LASER laser;

    T_COUNTER emitTime;
    T_COUNTER Timer;


}BOSS_STATE;

void init_boss(BOSS_STATE *boss_state,BULLET *bullet);
void init_boss_angle(BOSS_STATE* boss_state);
void init_b_bullet(BULLET* bullet);
void boss_action(BOSS_STATE *boss_state,TANK *tank,ALLEGRO_KEYBOARD_STATE *key_state );
void  boss_new(BOSS_STATE *boss_state);
void boss_shoot(BOSS_STATE* boss_state);
void boss_bullet_move(BOSS_STATE *boss_state);
void boss_emit(BOSS_STATE *boss_state);
void boss_center_coord(BOSS_STATE *boss_state);
void boss_bullet_damage(BOSS_STATE *boss_state,TANK * tank);
void bomb(BOSS_STATE *boss_state,TANK *tank);
void tank_bullet_damage_b(BOSS_STATE *boss_state,TANK * tank);
void boss_is_damaged(BOSS_STATE *boss_ptr,OBSTACLE *obstacle_ptr);
void boss_move(BOSS_STATE *boss_state);
void boss_track_move(BOSS_STATE *boss_state,TANK *tank);
#endif
