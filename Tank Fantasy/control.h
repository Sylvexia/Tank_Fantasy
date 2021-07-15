#include "tank.h"
#include "camera.h"
#include "level.h"
#include "math.h"

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define STATIC 4
#define AUTOMODE 1
void control_keyboard(TANK* tank_ptr,ALLEGRO_KEYBOARD_STATE* key_state);
void control_joystick(TANK* tank_ptr,ALLEGRO_JOYSTICK_STATE* joy_state,
                   ALLEGRO_JOYSTICK *joystick);

void move_up(TANK* tank_ptr);
void move_down(TANK* tank_ptr);
void move_left(TANK* tank_ptr);
void move_right(TANK* tank_ptr);

int mouse_startscreen(ALLEGRO_MOUSE_STATE* mouse,START_SCREEN start);
int mouse_setscreen(ALLEGRO_MOUSE_STATE* mouse,START_SCREEN start);

void mouse_tank_angle(ALLEGRO_MOUSE_STATE *mouse_state,TANK* tank,CAMERA *cam);
void find_bUV(BULLET *bullet);
