#include "game_state.h"


int main()
{
    init();

    ALLEGRO_DISPLAY *display = al_create_display(scr_w,scr_h);
    al_set_window_title(display,"tank fantasy");
    int score,lv;
    srand(time(0));

    enum gamestate state=STATE_START;
    bool exit = false;
    while(!exit)
    {
        switch(state){
            case STATE_START:
                state=title_screen();
                break;
            case STATE_LV1:
                state=lvl_1(&score);
                break;
            case STATE_LVUP1:
                state=lvup1(&lv);
                break;
            case STATE_LV2:
                state=lvl_2(&score,lv);
                break;
            case STATE_LVUP2:
                state=lvup2(&lv);
                break;
            case STATE_LV3:
                state=lvl_3(&score,lv);
                break;
            case STATE_WIN:
                state=winscreen(score);
                break;
            case STATE_DEATH:
                state=death_screen();
                break;
            case STATE_END:
                exit = true;
                break;
        }
    }
    al_destroy_display(display);
    return 0;
}
