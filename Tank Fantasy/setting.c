#include "setting.h"

//about architecture

void init()
{
    al_init();
    al_init_primitives_addon();                                                 //primitive-->draw basic shape like circle line arcs square
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(10);
    al_install_keyboard();
    al_install_joystick();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_native_dialog_addon();
}

void regist(ALLEGRO_EVENT_QUEUE *event_queue,ALLEGRO_TIMER *timer)              //register to event queue
{
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_joystick_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
}

void destroy(ALLEGRO_DISPLAY *display,ALLEGRO_EVENT_QUEUE *event_queue,
             ALLEGRO_TIMER *timer)
{
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
}
