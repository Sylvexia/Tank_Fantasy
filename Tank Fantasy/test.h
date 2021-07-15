#include <allegro5/allegro.h>
#include <math.h>




void print_joystick_sticks_log(ALLEGRO_EVENT *events);
void print_joystick_button_down_log(ALLEGRO_EVENT *events);
void print_joystick_button_up_log(ALLEGRO_EVENT *events);
void print_joystick_log(ALLEGRO_EVENT events);
bool load_joystick_info(ALLEGRO_JOYSTICK *joystick);


