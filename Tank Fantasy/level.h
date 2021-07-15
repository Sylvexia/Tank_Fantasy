#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

enum titlestate{

    TITLE_FIRST,
    TITLE_START,
    TITLE_RANK,
    TITLE_SETTING,//?
    TITLE_QUIT,
};

typedef struct BUTTON
{
    ALLEGRO_BITMAP* img;
    float but_w;
    float but_h;
    float but_x;
    float but_y;

}BUTTON;

typedef struct START_SCREEN
{
    ALLEGRO_BITMAP* startscreen;
    ALLEGRO_BITMAP* rankscreen;
    BUTTON startbut;
    BUTTON setbut;//?
    BUTTON quitbut;
    BUTTON returnbut;
    BUTTON rankbut;
}START_SCREEN;

typedef struct LEVEL
{
    ALLEGRO_BITMAP* background;
    ALLEGRO_SAMPLE *background_music1;

}LEVEL;

typedef struct LEVELUP
{
     ALLEGRO_BITMAP* lvupscreen;
     BUTTON s1;
     BUTTON s2;
     BUTTON s3;
}LEVELUP;

void init_level_1(LEVEL *level_1);
void destroy_level_1(LEVEL *level_1);
void init_level_2(LEVEL *level_2);
void destroy_level_2(LEVEL *level_2);
void init_rank(LEVEL *rankscreen);
void init_start(START_SCREEN *start);
void destroy_start(START_SCREEN *start);
void init_lvup(LEVELUP *lvup);

void init_level_3(LEVEL *level_3);
void destroy_level_3(LEVEL *level_3);
#endif // _LEVEL_H_
