#include "game_state.h"
int title_screen()
{
    ALLEGRO_EVENT events;
    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_KEYBOARD_STATE key_state;
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1/60.0);

    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    START_SCREEN startscreen;
    init_start(&startscreen);
    enum titlestate titlestate=TITLE_FIRST;

    al_start_timer(timer);

    while(1)
    {
        switch(titlestate)
        {
            case TITLE_FIRST:
            {
                if(!al_is_event_queue_empty(event_queue))
                {

                    while(al_get_next_event(event_queue,&events))
                    {
                        al_get_mouse_state(&mouse_state);
                        switch(events.type)
                        {
                            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                                titlestate=mouse_startscreen(&mouse_state,startscreen);
                                break;

                            case ALLEGRO_EVENT_KEY_DOWN:
                            if(events.keyboard.keycode==ALLEGRO_KEY_R){
                                delete_save();
                            }
                            case ALLEGRO_EVENT_TIMER:
                                if(events.timer.source==timer)
                                {
                                    draw_start(startscreen);
                                    draw_start_show_button(startscreen,&mouse_state);
                                    al_flip_display();
                                    al_clear_to_color(al_map_rgb(0, 0, 0));
                                }
                                break;
                        }
                    }
                }
                break;
            }

            case TITLE_START:
            {
                destroy_start(&startscreen);
                al_destroy_event_queue(event_queue);
                al_destroy_timer(timer);
                return STATE_LV1;
                break;
            }


            case TITLE_RANK:
            {
                if(!al_is_event_queue_empty(event_queue))
                {
                    while(al_get_next_event(event_queue,&events))
                    {
                        al_get_keyboard_state(&key_state);
                        al_get_mouse_state(&mouse_state);
                        switch(events.type)
                        {
                            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                                titlestate=mouse_rankscreen(&mouse_state,startscreen);
                                break;

                            break;
                            case ALLEGRO_EVENT_TIMER:
                                draw_rank(startscreen);
                                draw_rank_show_button(startscreen,&mouse_state);
                                printf_save();
                                al_flip_display();
                                al_clear_to_color(al_map_rgb(0, 0, 0));
                                break;
                        }
                    }
                }
                break;
            }


            case TITLE_QUIT:
            {
                destroy_start(&startscreen);
                al_destroy_event_queue(event_queue);
                al_destroy_timer(timer);
                return STATE_END;
                break;
            }

        }
    }
}

int lvl_1(int* score)
{
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();                 //init the event
    ALLEGRO_EVENT events;

    ALLEGRO_KEYBOARD_STATE key_state;                                           //get keyboard continuous input
    ALLEGRO_MOUSE_STATE mouse_state;                                            //get joystick continuous input

    ALLEGRO_TIMER *timer = al_create_timer(1/60.0);
    ALLEGRO_FONT *font= al_load_font("media/fonts/DFT_TL9.TTC", 50, 0);         //specify the fps currently 60hz
    ALLEGRO_TRANSFORM camera;//視角
    ALLEGRO_SAMPLE_ID backgroundId;

    LEVEL level_1;
    TANK tank0;
    *score=10000;
    time_t t1, t2;
    CAMERA cam;
    FIREBAR firebar[FIREBAR_NUM];
    OBSTACLE wall[WALL_NUM];
    BULLET bullet[BULL_NUM];
    BULLET bullet2[BULL_NUM];
    ENEMY enemy_rand[ENEMY_NUM];

    float enemy_rand_data[][2]={   700,600,
                                    500,300,
                                    600,500,
                                    2000,1200,
                                    1602,1682,
                                    1800,1400,
                                    1600,1400,
                                    1865,1752,
                                    1954,2486,
                                    1025,658,
                                    800,2173,
                                    900,675,
                                    738,162,
                                    984,684,
                                    2800,1400,
                                    2300,1503,
                                    3000,1564,
                                    2500,1800,
                                    -1,-1};

    float wall_data[][4]={  100,700,200,100,//x,y,w,h
                                100,800,100,500,
                                200,100,100,500,
                                200,600,300,100,
                                200,1200,200,100,
                                300,100,200,100,
                                400,700,100,200,
                                400,1200,200,200,
                                500,100,100,200,
                                500,400,100,300,
                                600,100,400,100,
                                600,600,300,100,
                                600,1300,200,100,
                                700,1200,200,100,
                                900,600,100,200,
                                900,900,100,300,
                                1000,100,500,100,
                                1000,1100,600,100,
                                1500,100,100,200,
                                1500,400,200,200,
                                1500,600,100,500,
                                1600,200,100,200,
                                {-1,-1,-1,-1}};

    float firebar_loc_data[][2]={
                                    1300,500,
                                    1300,1000,
                                    500,1800,
                                    1200,1800,
                                    2000,800,
                                    2000,1600,
                                    2400,1200
                                    -1,-1};

    float firebar_turnspeed_data[][1]={ 1,
                                        0.5,
                                        0.7,
                                        0.5,
                                        1.2,
                                        0.6,
                                        0.8,
                                        -1,
                                        };

    bool exit = false;

    init_level_1(&level_1);
    init_bullet(bullet);
    init_bullet2(bullet2);
    init_tank(&tank0,bullet,bullet2);
    init_camera(&cam,&camera);
    init_wall(wall,wall_data);
    init_firebar(firebar,firebar_loc_data,firebar_turnspeed_data);
    init_enemy_rand(enemy_rand,enemy_rand_data);

    regist(event_queue,timer);

    al_register_event_source(event_queue,
                             al_get_timer_event_source(tank0.reload));

    al_start_timer(timer);
    al_play_sample(level_1.background_music1, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &backgroundId);
    t1=time(NULL);

    while(!exit)
    {
        if(!al_is_event_queue_empty(event_queue))
        {
            while(al_get_next_event(event_queue,&events))
            {

                al_get_mouse_state(&mouse_state);
                al_get_keyboard_state(&key_state);

                switch(events.type)
                {
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:
                        exit=true;
                        break;

                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                        if(!tank0.auto_shoot)
                        {
                            tank_auto_able(&tank0);
                        }
                        break;

                    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                        if(tank0.auto_shoot)
                        {
                            tank_auto_disable(&tank0);
                        }
                        break;

                    case ALLEGRO_EVENT_MOUSE_AXES:
                        mouse_tank_angle(&mouse_state,&tank0,&cam);
                        break;

                    case ALLEGRO_EVENT_KEY_DOWN:

                        if(events.keyboard.keycode==ALLEGRO_KEY_ESCAPE){
                            if(al_show_native_message_box(NULL,
                                "Quit","Do you want to quit this game?",NULL,
                                NULL, ALLEGRO_MESSAGEBOX_YES_NO))
                                {
                                    destroy_tank(&tank0);
                                    destroy_level_1(&level_1);
                                    al_destroy_event_queue(event_queue);
                                    al_destroy_font(font);
                                    fix_camara(&cam);
                                    return STATE_START;
                                }
                        }
                        if(events.keyboard.keycode==ALLEGRO_KEY_Q)
                        {
                            fix_camara(&cam);
                            destroy_tank(&tank0);
                            destroy_level_1(&level_1);
                            al_destroy_event_queue(event_queue);
                            al_destroy_font(font);
                            t2 = time(NULL);
                            *score=*score-(t2-t1);
                            al_destroy_timer(timer);
                            return STATE_LVUP1;
                        }

                        if(events.keyboard.keycode==ALLEGRO_KEY_E)
                        {
                            if(tank0.auto_shoot)
                            {
                                tank_auto_disable(&tank0);
                                break;
                            }
                            if(!tank0.auto_shoot)
                            {
                                tank_auto_able(&tank0);
                            }
                        }
                        break;

                    case ALLEGRO_EVENT_TIMER:

                        if(tank0.hp<=0)
                        {
                            destroy_tank(&tank0);
                            destroy_level_1(&level_1);
                            al_destroy_event_queue(event_queue);
                            al_destroy_font(font);
                            fix_camara(&cam);
                            return STATE_DEATH;
                        }

                        if(tank0.lvl_up)
                        {
                            fix_camara(&cam);
                            destroy_tank(&tank0);
                            destroy_level_1(&level_1);
                            al_destroy_event_queue(event_queue);
                            al_destroy_font(font);
                            t2 = time(NULL);
                            *score=*score-(t2-t1);
                            al_destroy_timer(timer);
                            return STATE_LVUP1;
                        }

                        if((events.timer.source==tank0.reload)&&
                           (tank0.auto_shoot))
                        {
                            tank_shoot(&tank0);
                        }

                        if(events.timer.source==timer)
                            {
                                tank_new(&tank0);
                                enemy_new(enemy_rand,&tank0);
                                control_keyboard(&tank0,&key_state);

                                tank_bullet_move(&tank0);
                                //enemy_track_move(enemy_track,&tank0);
                                enemy_random_move(enemy_rand);

                                firebar_rotate(&tank0,firebar);

                                col_bullet_enemy(&tank0,&enemy_rand);
                                col_tank_enemy(&tank0,&enemy_rand);
                                col_tank_firebar(&tank0,firebar);
                                col_tank_wall(&tank0,wall);
                                col_portal_1(&tank0);

                                tank_center_coord(&tank0);
                                CameraUpdate(&cam,&tank0);

                                draw_backbround(level_1.background);
                                draw_wall(wall);
                                draw_firebar(firebar);
                                draw_enemy(enemy_rand);
                                draw_tank_aim(&mouse_state,&tank0,&cam);
                                draw_tank(&tank0);
                                draw_tank_health_bar(&tank0);
                                draw_tank_bullet(&tank0);
                                draw_damaged_tank(&tank0);
                                draw_score(score, t1, t2, font,&cam);
                                draw_portal_1();

                                al_flip_display();
                                al_clear_to_color(al_map_rgb(0, 0, 0));
                            }

                        break;
                }
            }
        }
    }
}

int lvup1(int *lv)
{
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();                 //init the event
    ALLEGRO_EVENT events;
    ALLEGRO_FONT *font= al_load_font("media/fonts/DFT_TL9.TTC", 50, 0);
    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_TIMER *timer = al_create_timer(1/60.0);

    LEVELUP lvup;
    init_lvup(&lvup);

    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    while(1){
    if(!al_is_event_queue_empty(event_queue))
        {
            while(al_get_next_event(event_queue,&events))
            {
                al_get_mouse_state(&mouse_state);
                switch(events.type)
                {
                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                        switch(mouse_lvup(&mouse_state,lvup)){
                            case 1:
                                *lv=1;
                                destroy_lvup(&lvup);
                                al_destroy_event_queue(event_queue);
                                al_destroy_font(font);
                                return STATE_LV2;
                                break;
                            case 2:
                                *lv=2;
                                destroy_lvup(&lvup);
                                al_destroy_event_queue(event_queue);
                                al_destroy_font(font);
                                return STATE_LV2;
                                break;
                            case 3:
                                *lv=3;
                                destroy_lvup(lvup);
                                al_destroy_event_queue(event_queue);
                                al_destroy_font(font);
                                return STATE_LV2;
                                break;
                        }

                        break;

                    case ALLEGRO_EVENT_TIMER:
                        if(events.timer.source==timer)
                        {

                            draw_lvupscreen(lvup);
                            draw_lvup1_show_button(&mouse_state,lvup,font);
                            al_flip_display();
                            al_clear_to_color(al_map_rgb(0, 0, 0));
                        }
                        break;
                }
            }
        }
    }

}

int lvl_2(int* score,int lv)
{
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();                 //init the event
    ALLEGRO_EVENT events;
    ALLEGRO_FONT *font= al_load_font("media/fonts/DFT_TL9.TTC", 50, 0);
    ALLEGRO_KEYBOARD_STATE key_state;                                           //get keyboard continuous input
    ALLEGRO_MOUSE_STATE mouse_state;                                            //get joystick continuous input

    ALLEGRO_TIMER *timer = al_create_timer(1/60.0);                             //specify the fps currently 60hz

    ALLEGRO_TRANSFORM camera;//視角
    ALLEGRO_SAMPLE_ID backgroundId;


    LEVEL level_2;
    CAMERA cam;
    TANK tank0;
    OBSTACLE wall[WALL_NUM];
    OBSTACLE spike[OBS_NUM];

    BULLET bullet[BULL_NUM];
    BULLET bullet2[BULL_NUM];
    ENEMY enemy_track[ENEMY_NUM];
    time_t t1, t2;
    float wall_data[][4]={  100,700,300,100,//x,y,w,h
                            100,1100,200,100,
                            200,200,100,100,
                            200,300,200,100,
                            200,400,100,200,
                            200,800,100,200,
                            200,1200,100,100,
                            200,1600,400,100,
                            300,100,100,200,
                            300,400,200,100,
                            300,500,100,200,
                            300,1000,200,100,
                            300,1300,200,100,
                            400,100,300,100,
                            400,1400,100,200,
                            400,1700,500,100,
                            500,600,100,100,
                            500,800,200,100,
                            500,1100,200,100,
                            500,1400,100,100,
                            600,500,100,200,
                            600,1000,300,100,
                            700,200,100,200,
                            700,600,100,200,
                            700,1200,200,100,
                            700,1400,200,200,
                            800,100,300,100,
                            800,400,200,100,
                            800,700,100,100,
                            900,1600,100,300,
                            1000,700,100,200,
                            1000,1400,100,200,
                            1000,1600,200,100,
                            1000,1800,500,100,
                            1100,200,100,100,
                            1100,400,100,100,
                            1100,500,200,100,
                            1100,900,200,100,
                            1100,1100,100,100,
                            1100,1200,200,100,
                            1200,100,300,100,
                            1200,1500,200,100,
                            1400,200,100,300,
                            1400,600,200,100,
                            1400,1300,100,200,
                            1500,200,300,100,
                            1500,900,100,300,
                            1500,1400,400,200,
                            1500,1900,200,200,
                            1600,900,100,100,
                            1600,1000,100,200,
                            1700,400,100,200,
                            1700,800,200,100,
                            1700,1300,200,100,
                            1700,1800,300,100,
                            1800,300,200,200,
                            1800,1100,100,200,
                            1900,700,100,300,
                            2000,500,200,100,
                            2000,600,100,200,
                            2000,800,200,100,
                            2000,1100,200,200,
                            2000,1600,200,200,
                            2100,900,100,100,
                            2100,1300,200,200,
                            2200,1000,100,200,
                            2200,1500,100,100,
                            {-1,-1,-1,-1}};

    float spike_data[][2]={ 500,900,//x,y,dir
                            800,500,
                            1000,900,
                            1200,1300,
                            1300,1600,
                            1500,1600,
                            1600,1700,
                            {-1,-1,-1}};

    float enemy_track_data[][2]={   500,600,
                                    200,300,
                                    100,500,
                                    1000,1200,
                                    1300,1500,
                                    1400,540,
                                    456,984,
                                    876,354,
                                    1265,368,
                                    2035,340,
                                    2495,677,
                                    894,483,
                                    1900,320,
                                    3425,1807,
                                    3624,1567,
                                    3754,2016,
                                    3800,2800,
                                    3691,3015,
                                    3751,3200,
                                    3954,3016,
                                    4026,2213,
                                    2021,2513,
                                    -1,-1};

    bool exit = false;


    init_level_2(&level_2);
    init_bullet(bullet);
    init_bullet2(bullet2);
    init_wall(wall,wall_data);
    init_spike(spike,spike_data);
    init_tank(&tank0,bullet,bullet2);
    init_camera(&cam,&camera);
    init_enemy_track(enemy_track,enemy_track_data);

    regist(event_queue,timer);

    al_register_event_source(event_queue,
                             al_get_timer_event_source(tank0.reload));
    if(lv%4==1)
    {
        al_register_event_source(event_queue,
            al_get_timer_event_source(tank0.reload2));
    }
    else if(lv%4==2)
    {
        tank0.speed=15;
    }
    else if(lv%4==3)
    {
        al_set_timer_speed(tank0.reload, 1/15.0);
    }

    al_start_timer(timer);
    al_play_sample(level_2.background_music1, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &backgroundId);
    t1=time(NULL);
    while(!exit)
    {
        if(!al_is_event_queue_empty(event_queue))
        {
            while(al_get_next_event(event_queue,&events))
            {
                al_get_mouse_state(&mouse_state);
                al_get_keyboard_state(&key_state);

                switch(events.type)
                {
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:
                        exit=true;
                        break;

                    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                        if(!tank0.auto_shoot)
                        {
                            tank_auto_able(&tank0);
                        }
                        break;

                    case ALLEGRO_EVENT_KEY_DOWN:
                        if(events.keyboard.keycode==ALLEGRO_KEY_ESCAPE){
                            if(al_show_native_message_box(NULL,
                            "Quit","Do you want to quit this game?",NULL,
                            NULL, ALLEGRO_MESSAGEBOX_YES_NO)){
                                destroy_tank(&tank0);
                                destroy_level_2(&level_2);
                                al_destroy_event_queue(event_queue);
                                al_destroy_font(font);
                                fix_camara(&cam);
                                return STATE_START;
                            }
                        }
                        if(events.keyboard.keycode==ALLEGRO_KEY_Q)
                        {
                            destroy_tank(&tank0);
                            destroy_level_2(&level_2);
                            al_destroy_event_queue(event_queue);
                            al_destroy_font(font);
                            t2 = time(NULL);
                            *score=*score-(t2-t1);
                            al_destroy_timer(timer);
                            fix_camara(&cam);
                            return STATE_LVUP2;
                        }

                        if(events.keyboard.keycode==ALLEGRO_KEY_E)
                        {
                            if(tank0.auto_shoot)
                            {
                                tank_auto_disable(&tank0);
                                break;
                            }

                            if(!tank0.auto_shoot)
                            {
                                tank_auto_able(&tank0);
                            }
                        }
                        break;



                    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                        if(tank0.auto_shoot)
                        {
                            tank_auto_disable(&tank0);
                        }
                        break;

                    case ALLEGRO_EVENT_MOUSE_AXES:
                        mouse_tank_angle(&mouse_state,&tank0,&cam);
                        break;

                    case ALLEGRO_EVENT_TIMER:
                        if(tank0.hp<=0)
                        {
                            destroy_tank(&tank0);
                            destroy_level_2(&level_2);
                            al_destroy_event_queue(event_queue);
                            al_destroy_font(font);
                            al_destroy_timer(timer);
                            fix_camara(&cam);
                            return STATE_DEATH;
                        }

                        if(tank0.lvl_up)
                        {
                            destroy_tank(&tank0);
                            destroy_level_2(&level_2);
                            al_destroy_event_queue(event_queue);
                            al_destroy_font(font);
                            t2 = time(NULL);
                            *score=*score-(t2-t1);
                            al_destroy_timer(timer);
                            fix_camara(&cam);
                            return STATE_LVUP2;
                        }
                        if((events.timer.source==tank0.reload)&&
                           (tank0.auto_shoot))
                        {
                            tank_shoot(&tank0);
                        }

                        if((events.timer.source==tank0.reload2)&&
                           (tank0.auto_shoot))
                        {
                            tank_shoot2(&tank0);
                        }
                        if(events.timer.source==timer)
                            {
                                tank_new(&tank0);
                                enemy_new(enemy_track,&tank0);
                                obs_spike_new(spike);
                                control_keyboard(&tank0,&key_state);

                                tank_bullet_move(&tank0);
                                enemy_track_move(&enemy_track,&tank0);
                                obs_move_spike(spike);
                                col_tank_enemy(&tank0,&enemy_track);
                                col_tank_spike(&tank0,spike);
                                col_tank_wall(&tank0,wall);
                                col_bullet_enemy(&tank0,enemy_track);
                                col_portal_2(&tank0);

                                tank_center_coord(&tank0);
                                CameraUpdate(&cam,&tank0);

                                draw_backbround(level_2.background);

                                draw_wall(wall);
                                draw_spike(spike);
                                draw_enemy(enemy_track);
                                draw_tank_aim(&mouse_state,&tank0,&cam);
                                draw_tank(&tank0);
                                draw_tank_health_bar(&tank0);
                                draw_tank_bullet(&tank0);
                                draw_damaged_tank(&tank0);
                                draw_score(score, t1, t2, font,&cam);
                                draw_portal_2();

                                al_flip_display();
                                al_clear_to_color(al_map_rgb(0, 0, 0));

                            }

                        break;
                }
            }
        }
    }
}

int lvup2(int *lv)
{
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();                 //init the event
    ALLEGRO_EVENT events;
    ALLEGRO_FONT *font= al_load_font("media/fonts/DFT_TL9.TTC", 50, 0);
    ALLEGRO_MOUSE_STATE mouse_state;
    ALLEGRO_TIMER *timer = al_create_timer(1/60.0);

    LEVELUP lvup;
    init_lvup2(&lvup);

    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);
    while(1){
    if(!al_is_event_queue_empty(event_queue))
                {
                    while(al_get_next_event(event_queue,&events))
                    {
                        al_get_mouse_state(&mouse_state);
                        switch(events.type)
                        {
                            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                                switch(mouse_lvup(&mouse_state,lvup)){
                                    case 1:
                                        *lv=*lv+10;
                                        destroy_lvup(&lvup);
                                        al_destroy_event_queue(event_queue);
                                        al_destroy_font(font);
                                        return STATE_LV3;
                                        break;
                                    case 2:
                                        *lv=*lv+20;
                                        destroy_lvup(&lvup);
                                        al_destroy_event_queue(event_queue);
                                        al_destroy_font(font);
                                        return STATE_LV3;
                                        break;
                                    case 3:
                                        *lv=*lv+30;
                                        destroy_lvup(lvup);
                                        al_destroy_event_queue(event_queue);
                                        al_destroy_font(font);
                                        return STATE_LV3;
                                        break;
                                }

                                break;

                            case ALLEGRO_EVENT_TIMER:
                                if(events.timer.source==timer)
                                {

                                    draw_lvupscreen(lvup);
                                    draw_lvup2_show_button(&mouse_state,lvup,font);
                                    al_flip_display();
                                    al_clear_to_color(al_map_rgb(0, 0, 0));
                                }
                                break;
                        }
                    }
                }
    }

}

int lvl_3(int* score,int lv)
{
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();                 //init the event
    ALLEGRO_EVENT events;
    ALLEGRO_FONT *font= al_load_font("media/fonts/DFT_TL9.TTC", 50, 0);

    ALLEGRO_KEYBOARD_STATE key_state;                                           //get keyboard continuous input
    ALLEGRO_MOUSE_STATE mouse_state;                                            //get joystick continuous input

    ALLEGRO_TIMER *timer = al_create_timer(1/60.0);                             //specify the fps currently 60hz

    ALLEGRO_TRANSFORM camera;//視角
    ALLEGRO_SAMPLE_ID backgroundId;
    CAMERA cam;

    LEVEL level_3;
    TANK tank0;

    BULLET bullet[BULL_NUM];
    BULLET bullet2[BULL_NUM];

    srand(time(0));


    BULLET boss_bullet[ballnum];
    BOSS_STATE boss_state;

    time_t t1, t2;
    bool exit = false;


    init_b_bullet(boss_bullet);
    init_boss(&boss_state,boss_bullet);

    init_level_3(&level_3);
    init_bullet(bullet);
    init_bullet2(bullet2);
    init_tank(&tank0,bullet,bullet2);
    init_camera(&cam,&camera);


    regist(event_queue,timer);



    al_register_event_source(event_queue,
                             al_get_timer_event_source(tank0.reload));
    if(lv%10==1)
    {
        al_register_event_source(event_queue,
            al_get_timer_event_source(tank0.reload2));
    }
    if(lv%10==2)
    {
        tank0.speed=15;
    }
    if(lv%10==3)
    {
        al_set_timer_speed(tank0.reload, 1/15.0);
    }

    if(lv/10==1)
    {
        int i=0;
        for(i=0;i<BULL_NUM;i++)
        {
            tank0.bullet[i].r*=2;
            tank0.bullet[i].damage*=1.5;
        }
    }

    if(lv/10==2)
    {
        int i=0;
        for(i=0;i<BULL_NUM;i++)
        {
            tank0.bullet[i].speed*=1.5;
        }
    }

    if(lv/10==3)
    {
        tank0.hp*=2;
        tank0.max_hp*=2;
    }

    al_start_timer(timer);
    al_start_timer(tank0.reload2);
    al_play_sample(level_3.background_music1, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &backgroundId);
    t1=time(NULL);
    while(!exit)
    {
        if(!al_is_event_queue_empty(event_queue))
        {
            while(al_get_next_event(event_queue,&events))
            {

                al_get_mouse_state(&mouse_state);
                al_get_keyboard_state(&key_state);

                switch(events.type)
                {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    exit=true;
                    break;

                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                    if(!tank0.auto_shoot)
                    {
                        tank_auto_able(&tank0);
                    }
                    break;

                case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                    if(tank0.auto_shoot)
                    {
                        tank_auto_disable(&tank0);
                    }
                    break;

                case ALLEGRO_EVENT_MOUSE_AXES:
                    mouse_tank_angle(&mouse_state,&tank0,&cam);
                    break;

                case ALLEGRO_EVENT_KEY_DOWN:
                    if(events.keyboard.keycode==ALLEGRO_KEY_Q)
                    {
                        destroy_tank(&tank0);
                        destroy_level_3(&level_3);
                        al_destroy_event_queue(event_queue);
                        al_destroy_font(font);
                        t2 = time(NULL);
                        *score=*score-(t2-t1);
                        al_destroy_timer(timer);
                        fix_camara(&cam);
                        return STATE_WIN;
                    }

                    if(events.keyboard.keycode==ALLEGRO_KEY_E)
                    {
                        if(tank0.auto_shoot)
                        {
                            tank_auto_disable(&tank0);
                            break;
                        }
                        if(!tank0.auto_shoot)
                        {
                            tank_auto_able(&tank0);
                        }
                    }
                    break;

                case ALLEGRO_EVENT_TIMER:

                    if((events.timer.source==tank0.reload)&&
                            (tank0.auto_shoot))
                    {
                        tank_shoot(&tank0);
                    }

                    if((events.timer.source==tank0.reload2)&&
                            (tank0.auto_shoot))
                    {
                        tank_shoot2(&tank0);

                    }

                    if(events.timer.source==timer)
                    {
                        draw_backbround(level_3.background);

                        tank_new(&tank0);
                        tank_center_coord(&tank0);
                        control_keyboard(&tank0,&key_state);

                        boss_new(&boss_state);
                        boss_center_coord(&boss_state);
                        boss_action(&boss_state,&tank0,&key_state);
                        boss_move(&boss_state);


                        col_tank_boss(&tank0, &boss_state);


                        boss_bullet_move(&boss_state);
                        tank_bullet_move(&tank0);

                        boss_bullet_damage(&boss_state,&tank0);
                        tank_bullet_damage_b(&boss_state,&tank0);



                        draw_tank_aim(&mouse_state,&tank0,&cam);
                        draw_tank_bullet(&tank0);
                        draw_tank(&tank0);
                        //draw_tank_health_bar(&tank0);//普通血條，會變長度
                        draw_ptank_health_bar(&tank0);
                        draw_damaged_tank(&tank0);

                        draw_boss_bitmap(&boss_state); //draw boss
                        draw_boss_bullet(&boss_state);
                        draw_boss_health_bar(&boss_state,&cam);
                        draw_score(score, t1, t2, font,&cam);



                        draw_bs_psi(&boss_state,&tank0,&cam);
                        CameraUpdate(&cam,&tank0);



                        if(tank0.hp<=0)
                        {


                            destroy_tank(&tank0);
                            destroy_level_3(&level_3);
                            al_destroy_event_queue(event_queue);
                            al_destroy_timer(timer);
                            al_destroy_bitmap(boss_state.img);

                            fix_camara(&cam);
                            return STATE_DEATH;
                        }

                        if(boss_state.hp<=0 )
                        {
                            destroy_tank(&tank0);
                            destroy_level_3(&level_3);
                            t2 = time(NULL);
                            *score=*score-(t2-t1);
                            al_destroy_event_queue(event_queue);
                            al_destroy_timer(timer);
                            al_destroy_bitmap(boss_state.img);
                            al_destroy_font(font);

                            fix_camara(&cam);
                            return STATE_WIN;
                        }


                        al_flip_display();
                        al_clear_to_color(al_map_rgb(0, 0, 0));

                    }

                }
            }
        }
    }

}

int winscreen(int score)
{
    ALLEGRO_EVENT events;
    ALLEGRO_KEYBOARD_STATE key_state;
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_TIMER *timer = al_create_timer(1/60.0);
    LEVEL rankscreen;
    int input,n=0;
    char name[12]={0};
    regist(event_queue,timer);
    init_rank(&rankscreen);
    al_start_timer(timer);
    draw_backbround(rankscreen.background);
    while(1){
        if(!al_is_event_queue_empty(event_queue))
                {
                    while(al_get_next_event(event_queue,&events))
                    {
                        al_get_keyboard_state(&key_state);
                        switch(events.type)
                        {
                            case ALLEGRO_EVENT_KEY_CHAR:
                                switch(events.keyboard.keycode){
                                case ALLEGRO_KEY_ENTER:
                                    write_save(score,name);
                                    return STATE_START;
                                    break;
                                case ALLEGRO_KEY_BACKSPACE:
                                    if(n>0){
                                    name[n-1]=0;
                                    n--;
                                    }
                                    break;

                                default:
                                    if(n<10){
                                        if(input_fuc(events.keyboard.keycode,&input)){
                                            name[n]=input;
                                            n++;
                                        }
                                    }
                                    else{
                                        al_show_native_message_box(NULL,
                                        "Warning","only 10 words acceptable",NULL,
                                        NULL, ALLEGRO_MESSAGEBOX_WARN);
                                    }
                                    break;
                                }
                                break;

                            case ALLEGRO_EVENT_TIMER:
                                draw_backbround(rankscreen.background);

                                printf_save();
                                print_input(name,score);
                                al_flip_display();
                                al_clear_to_color(al_map_rgb(0, 0, 0));
                                break;
                        }
                    }
                }
    }
}

int death_screen()
{
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();                 //init the event
    ALLEGRO_EVENT events;
    ALLEGRO_KEYBOARD_STATE key_state;                                           //get keyboard continuous input
    ALLEGRO_MOUSE_STATE mouse_state;


    ALLEGRO_TIMER *timer = al_create_timer(1/60.0);

    ALLEGRO_BITMAP* death_pic;
    ALLEGRO_BITMAP* back_pic;
    ALLEGRO_SAMPLE* dead_music;
    ALLEGRO_SAMPLE_ID backgroundId;
    death_pic=al_load_bitmap
              ("media/pictures/screen/game over.png");
    dead_music=al_load_sample("media/audio/music/game_over.wav");


    bool exit=false;

    regist(event_queue,timer);

    al_start_timer(timer);
        al_play_sample(dead_music, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, &backgroundId);
    while(!exit)
    {
        if(!al_is_event_queue_empty(event_queue))
        {
            while(al_get_next_event(event_queue,&events))
            {

                al_get_mouse_state(&mouse_state);
                al_get_keyboard_state(&key_state);

                switch(events.type)
                {
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    exit=true;
                    break;


                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:

                    if(mouse_state.buttons & 1)
                    {

                        al_destroy_event_queue(event_queue);
                        al_destroy_timer(timer);
                        al_destroy_sample(dead_music);

                        return STATE_START;

                    }


                    break;



                case ALLEGRO_EVENT_KEY_DOWN:
                    if(events.keyboard.keycode==ALLEGRO_KEY_Q)
                    {

                        al_destroy_event_queue(event_queue);
                        al_destroy_timer(timer);
                        al_destroy_sample(dead_music);



                        return STATE_START;
                    }

                    break;

                case ALLEGRO_EVENT_TIMER:


                    if(events.timer.source==timer)
                    {
                        al_draw_bitmap(death_pic,0,0,0);

                        al_flip_display();
                        al_clear_to_color(al_map_rgb(0, 0, 0));

                    }



                }
            }
        }
    }

}
