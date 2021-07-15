#ifndef _SETTING_H_
#define _SETTING_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void init();
void regist(ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_TIMER *timer);
void destroy(ALLEGRO_DISPLAY *display,ALLEGRO_EVENT_QUEUE *event_queue,
             ALLEGRO_TIMER *timer);

#endif // _SETTING_H_



