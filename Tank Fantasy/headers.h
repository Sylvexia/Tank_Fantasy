
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>


bool load_joystick_info(ALLEGRO_JOYSTICK *joystick);
void hotplug_detection(ALLEGRO_EVENT *events,ALLEGRO_JOYSTICK *joystick);
void print_joystick_sticks_log(ALLEGRO_EVENT *events);
void print_joystick_button_down_log(ALLEGRO_EVENT *events);
void print_joystick_button_up_log(ALLEGRO_EVENT *events);
void print_joystick_log(ALLEGRO_EVENT events);

