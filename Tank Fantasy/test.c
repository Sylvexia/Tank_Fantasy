#include "test.h"
#include "camera.h"

void print_joystick_sticks_log(ALLEGRO_EVENT *events)
{
    if(events->type == ALLEGRO_EVENT_JOYSTICK_AXIS)
    {
        printf("stick[%d] axis[%d] position:%f\n"
                ,events->joystick.stick
                ,events->joystick.axis
                ,events->joystick.pos);
    }
}

void print_joystick_button_down_log(ALLEGRO_EVENT *events)
{
    if(events->type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN)
        printf("button[%d] has been pressed down \n",events->joystick.button);
}

void print_joystick_button_up_log(ALLEGRO_EVENT *events)
{
    if(events->type == ALLEGRO_EVENT_JOYSTICK_BUTTON_UP)
        printf("button[%d] has been released \n",events->joystick.button);
}

void print_joystick_log(ALLEGRO_EVENT events)
{
    print_joystick_sticks_log(&events);
    print_joystick_button_down_log(&events);
    print_joystick_button_up_log(&events);
}


bool load_joystick_info(ALLEGRO_JOYSTICK *joystick)
{
    if(!al_is_joystick_installed())
    {
        printf("cannot import joystick module");
        return 0;
    }


    if(al_get_num_joysticks()==0)
    {
        printf("don't have joystick??");
        return 0;
    }

    else
    {
        int i=0;int j=0;

        printf("1st player Joystick: '%s'\n\n", al_get_joystick_name(joystick));
        printf("number of joystick %d\n",al_get_num_joysticks());
        printf("number of buttons %d \n",al_get_joystick_num_buttons(joystick));    //how many buttons
        printf("number of sticks %d \n\n",al_get_joystick_num_sticks(joystick));      //how many sticks

        for(i=0;i<al_get_joystick_num_sticks(joystick);i++)
        {
            printf("stick [%d]\tnumber of axes %d \n",
                   i,al_get_joystick_num_axes(joystick,i));
        }

        printf("\n");

        for(i=0;i<al_get_joystick_num_sticks(joystick)+1;i++)
        {
            printf("stick [%d]\tflag:%d\n",
                   i,al_get_joystick_stick_flags(joystick,i));
        }

        printf("\n");

        for(i=0;i<al_get_joystick_num_sticks(joystick);i++)
        {
            printf("stick[%d] name: %s \n",
                   i,al_get_joystick_stick_name(joystick,i));
        }

        printf("\n");

        for(i=0;i<al_get_joystick_num_sticks(joystick);i++)
        {
            for(j=0;j<al_get_joystick_num_axes(joystick,i);j++)
            {
                printf("axes name: %s \tstick[%d]\taxis[%d]\n",
                       al_get_joystick_axis_name(joystick, i, j),i,j);
            }
        }


        printf("\njoystick button name:\n");

        for(i=0;i<al_get_joystick_num_buttons(joystick);i++)
            printf("%s\tbutton[%d]\n",al_get_joystick_button_name(joystick,i),i);

        printf("\n");
    }
    return 1;
}





