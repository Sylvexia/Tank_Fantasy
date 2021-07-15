#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "camera.h"
#include "setting.h"
#include "control.h"
#include "mechanics.h"
#include "draw.h"
#include "level.h"
#include "enemy.h"
#include "collision.h"
#include "tank.h"
#include "firebar.h"
#include "save.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro_native_dialog.h>
enum gamestate{
    STATE_START,    //0
    STATE_LV1,      //1
    STATE_LVUP1,    //2
    STATE_LV2,      //3
    STATE_LVUP2,    //4
    STATE_LV3,      //5
    STATE_WIN,      //6
    STATE_DEATH,    //7
    STATE_END,      //8
};

typedef struct SAVE
{
    float tank_hp;
    int score;
    int tank_type;
}SAVE;

int title_screen();
int lvup1(int *lv);
int lvup2(int *lv);
int lvl_1(int *score);
int lvl_2(int *score,int lv);
int lvl_3(int *score,int lv);
int winscreen(int score);
int death_screen();

#endif // _GAME_STATE_H_
