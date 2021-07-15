#include "level.h"

void init_level_1(LEVEL *level_1)
{
    level_1->background=al_load_bitmap
        ("media/pictures/screen/lv1_background.png");
    level_1->background_music1 = al_load_sample
    ("media/audio/music/Dreamer by Hazy - Cinematic - Ambient - No Copyright Music.wav");
}

void destroy_level_1(LEVEL *level_1)
{
    al_destroy_bitmap(level_1->background);
    al_destroy_sample(level_1->background_music1);
}

void init_level_2(LEVEL *level_2)
{
    level_2->background=al_load_bitmap
        ("media/pictures/screen/lv2_background.png");
    level_2->background_music1 = al_load_sample
    ("media/audio/music/Hiraeth by Scott Buckley - Cinematic - Ambient - No Copyright Music.wav");
}

void destroy_level_2(LEVEL *level_2)
{
    al_destroy_bitmap(level_2->background);
    al_destroy_sample(level_2->background_music1);
}

void init_level_3(LEVEL *level_3)
{
    level_3->background=al_load_bitmap
        ("media/pictures/screen/lv3_background.png");
    level_3->background_music1 = al_load_sample
    ("media/audio/music/Chillstep Song (Non Copyrighted Music).wav");
}

void destroy_level_3(LEVEL *level_3)
{
    al_destroy_bitmap(level_3->background);
    al_destroy_sample(level_3->background_music1);
}


void init_start(START_SCREEN* start)
{
    start->startbut.img=al_load_bitmap("media/pictures/buttons/startbut.png");
    start->rankbut.img=al_load_bitmap("media/pictures/buttons/rankbut.png");
    start->quitbut.img=al_load_bitmap("media/pictures/buttons/quitbut.png");
    start->returnbut.img=al_load_bitmap("media/pictures/buttons/return.png");
    start->startscreen=al_load_bitmap("media/pictures/screen/startscreen.png");
    start->rankscreen=al_load_bitmap("media/pictures/screen/rankscreen.png");

    start->startbut.but_h=al_get_bitmap_height(start->startbut.img);
    start->startbut.but_w=al_get_bitmap_width(start->startbut.img);
    start->rankbut.but_h=al_get_bitmap_height(start->rankbut.img);
    start->rankbut.but_w=al_get_bitmap_width(start->rankbut.img);
    start->quitbut.but_h=al_get_bitmap_height(start->quitbut.img);
    start->quitbut.but_w=al_get_bitmap_width(start->quitbut.img);
    start->returnbut.but_h=al_get_bitmap_height(start->returnbut.img);
    start->returnbut.but_w=al_get_bitmap_width(start->returnbut.img);

    start->startbut.but_x=550;
    start->startbut.but_y=400;

    start->rankbut.but_x=start->startbut.but_x;
    start->rankbut.but_y=start->startbut.but_y + start->startbut.but_h;

    start->quitbut.but_x=start->startbut.but_x;
    start->quitbut.but_y=start->rankbut.but_y + start->rankbut.but_h;

    start->returnbut.but_x=550;
    start->returnbut.but_y=600;
}

void init_lvup(LEVELUP *lvup){

    lvup->s1.img=al_load_bitmap("media/pictures/buttons/multiple.png");
    lvup->s2.img=al_load_bitmap("media/pictures/buttons/speedbut.png");
    lvup->s3.img=al_load_bitmap("media/pictures/buttons/attackbut.png");
    lvup->lvupscreen=al_load_bitmap("media/pictures/screen/lvup.png");

    lvup->s1.but_h=al_get_bitmap_height(lvup->s1.img);
    lvup->s1.but_w=al_get_bitmap_width(lvup->s1.img);
    lvup->s2.but_h=al_get_bitmap_height(lvup->s2.img);
    lvup->s2.but_w=al_get_bitmap_width(lvup->s2.img);
    lvup->s3.but_h=al_get_bitmap_height(lvup->s3.img);
    lvup->s3.but_w=al_get_bitmap_width(lvup->s3.img);

    lvup->s1.but_x=80;
    lvup->s1.but_y=150;

    lvup->s2.but_x=lvup->s1.but_x+lvup->s1.but_w;
    lvup->s2.but_y=lvup->s1.but_y;

    lvup->s3.but_x=lvup->s2.but_x+lvup->s2.but_w;
    lvup->s3.but_y=lvup->s1.but_y;

}
void destroy_start(START_SCREEN *start)
{
    al_destroy_bitmap(start->startbut.img);
    al_destroy_bitmap(start->rankbut.img);
    al_destroy_bitmap(start->quitbut.img);
    al_destroy_bitmap(start->startscreen);
    al_destroy_bitmap(start->rankscreen);
}

void init_rank(LEVEL *rankscreen){

    rankscreen->background=al_load_bitmap("media/pictures/screen/rankscreen.png");

}

void destroy_lvup(LEVELUP *lvup){

    al_destroy_bitmap(lvup->s1.img);
    al_destroy_bitmap(lvup->s2.img);
    al_destroy_bitmap(lvup->s3.img);
    al_destroy_bitmap(lvup->lvupscreen);

}

void init_lvup2(LEVELUP *lvup){

    lvup->s1.img=al_load_bitmap("media/pictures/buttons/powerbut.png");
    lvup->s2.img=al_load_bitmap("media/pictures/buttons/quick.png");
    lvup->s3.img=al_load_bitmap("media/pictures/buttons/hp.png");
    lvup->lvupscreen=al_load_bitmap("media/pictures/screen/lvup.png");

    lvup->s1.but_h=al_get_bitmap_height(lvup->s1.img);
    lvup->s1.but_w=al_get_bitmap_width(lvup->s1.img);
    lvup->s2.but_h=al_get_bitmap_height(lvup->s2.img);
    lvup->s2.but_w=al_get_bitmap_width(lvup->s2.img);
    lvup->s3.but_h=al_get_bitmap_height(lvup->s3.img);
    lvup->s3.but_w=al_get_bitmap_width(lvup->s3.img);

    lvup->s1.but_x=80;
    lvup->s1.but_y=150;

    lvup->s2.but_x=lvup->s1.but_x+lvup->s1.but_w;
    lvup->s2.but_y=lvup->s1.but_y;

    lvup->s3.but_x=lvup->s2.but_x+lvup->s2.but_w;
    lvup->s3.but_y=lvup->s1.but_y;

}
