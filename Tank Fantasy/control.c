#include "control.h"

void move_up(TANK* tank_ptr)
{
    tank_ptr->vy=-tank_ptr->speed;
    tank_ptr->y+=tank_ptr->vy;
}

void move_down(TANK* tank_ptr)
{
    tank_ptr->vy=tank_ptr->speed;
    tank_ptr->y+=tank_ptr->vy;
}

void move_left(TANK* tank_ptr)
{
    tank_ptr->vx=-tank_ptr->speed;
    tank_ptr->x+=tank_ptr->vx;

}

void move_right(TANK* tank_ptr)
{
    tank_ptr->vx=tank_ptr->speed;
    tank_ptr->x+=tank_ptr->vx;
}

void control_keyboard(TANK* tank_ptr,ALLEGRO_KEYBOARD_STATE* key_state)
{
    tank_ptr->dir=STATIC;
    if(al_key_down(key_state,ALLEGRO_KEY_DOWN) ||
       al_key_down(key_state,ALLEGRO_KEY_S))
        {
            move_down(tank_ptr);
            tank_ptr->dir=DOWN;
        }

    if(al_key_down(key_state,ALLEGRO_KEY_UP) ||
        al_key_down(key_state,ALLEGRO_KEY_W))
        {
            move_up(tank_ptr);
            tank_ptr->dir=UP;
        }

    if(al_key_down(key_state,ALLEGRO_KEY_RIGHT) ||
        al_key_down(key_state,ALLEGRO_KEY_D))
        {
            move_right(tank_ptr);
            tank_ptr->dir=RIGHT;
        }

    if(al_key_down(key_state,ALLEGRO_KEY_LEFT) ||
       al_key_down(key_state,ALLEGRO_KEY_A))
        {
            move_left(tank_ptr);
            tank_ptr->dir=LEFT;
        }
}

void control_joystick(TANK* tank_ptr,ALLEGRO_JOYSTICK_STATE* joy_state,
                   ALLEGRO_JOYSTICK *joystick)
{
    if(al_get_num_joysticks()==0)
        return;

    al_get_joystick_state(joystick,joy_state);

    if(joy_state->stick[2].axis[0])
        tank_ptr->x+=joy_state->stick[2].axis[0]*tank_ptr->speed;
    if(joy_state->stick[2].axis[1])
        tank_ptr->y+=joy_state->stick[2].axis[1]*tank_ptr->speed;

    if(joy_state->stick[0].axis[0])
        tank_ptr->x+=joy_state->stick[0].axis[0]*tank_ptr->speed;
    if(joy_state->stick[0].axis[1])
        tank_ptr->y+=joy_state->stick[0].axis[1]*tank_ptr->speed;

    if(joy_state->stick[0].axis[2])
        tank_ptr->x+=joy_state->stick[0].axis[2]*tank_ptr->speed;
    if(joy_state->stick[1].axis[0])
        tank_ptr->y+=joy_state->stick[1].axis[0]*tank_ptr->speed;

}

void mouse_tank_angle(ALLEGRO_MOUSE_STATE *mouse_state,TANK* tank,CAMERA *cam)
{
    float angle,pi=3.14159;
    float centerX=tank->center_x;
    float centerY=tank->center_y;
    float mouseX=0,mouseY=0;             //find true mouseXY with changing window)

    mouseX=mouse_state->x+cam->cameraPosition[0];
    mouseY=mouse_state->y+cam->cameraPosition[1];

    if(centerX-mouseX>0 && centerY-mouseY>0){  //2
        angle=atan((centerY-mouseY)/(centerX-mouseX));
        tank->angle=pi-angle;
    }
    else if(centerX-mouseX<0 && centerY-mouseY>=0){ //1
        angle=atan((centerY-mouseY)/(centerX-mouseX));
        tank->angle=-angle;
    }
    else if(centerX-mouseX<0 && centerY-mouseY<0){  //4
        angle=atan((centerY-mouseY)/(centerX-mouseX));
        tank->angle= 2*pi-angle;
    }
    else if(centerX-mouseX>0 && centerY-mouseY<=0){ //3
        angle=atan((centerY-mouseY)/(centerX-mouseX));;
        tank->angle=pi-angle;
    }
}

int mouse_startscreen(ALLEGRO_MOUSE_STATE* mouse_state,START_SCREEN start)
{
    if(mouse_state->buttons & 1)
    {
        if( start.startbut.but_x<=mouse_state->x &&
            mouse_state->x      <=start.startbut.but_x+start.startbut.but_w)
            {

                if(start.startbut.but_y <=mouse_state->y &&
                   mouse_state->y       <start.startbut.but_y+start.startbut.but_h)
                    {
                        return TITLE_START;
                    }

                else if(start.rankbut.but_y  <=mouse_state->y &&
                        mouse_state->y      <start.rankbut.but_y+start.rankbut.but_h)
                    {
                        return TITLE_RANK;
                    }

                else if(start.quitbut.but_y <=mouse_state->y &&
                        mouse_state->y      <=start.quitbut.but_y+start.quitbut.but_h)
                    {
                        return TITLE_QUIT;
                    }

                else{
                    return TITLE_FIRST;
                }
            }
         else{
                return TITLE_FIRST;
            }
    }
}

int mouse_rankscreen(ALLEGRO_MOUSE_STATE* mouse_state,START_SCREEN start)
{
    if(mouse_state->buttons & 1)
    {
        if(mouse_state->x > 1165&&
            mouse_state->x < 1165 + start.returnbut.but_w)
            {
                if(mouse_state->y > 695&&
                    mouse_state->y < 695 + start.returnbut.but_h)
                    {
                        return TITLE_FIRST;
                    }
                else{
                    return TITLE_RANK;
                }
            }
        else{
            return TITLE_RANK;
        }

    }
}

int mouse_lvup(ALLEGRO_MOUSE_STATE* mouse_state,LEVELUP lvup){

    if(mouse_state->buttons & 1){
        if(lvup.s1.but_y<=mouse_state->y &&
            mouse_state->y<=lvup.s1.but_y+lvup.s1.but_h){
                if(lvup.s1.but_x<=mouse_state->x &&
                    mouse_state->x<=lvup.s1.but_x+lvup.s1.but_w){
                    return 1;
                    }
                else if(lvup.s2.but_x<=mouse_state->x &&
                    mouse_state->x<=lvup.s2.but_x+lvup.s2.but_w ){
                    return 2;
                    }
                else if(lvup.s3.but_x<=mouse_state->x &&
                    mouse_state->x<=lvup.s3.but_x+lvup.s3.but_w){
                    return 3;
                    }
                }
        }
}

void find_bUV(BULLET *bullet)
//找但單位向量
{

    bullet->vx=cos (bullet->angle);
    bullet->vy=sin (bullet->angle);
}
