#include "firebar.h"

void init_firebar(FIREBAR *firebar_ptr,float firebar_data[][2],float turnspeed[][1])
{
    int i=0;
    for(i=0;i<FIREBAR_NUM;i++)
    {
        if(firebar_data[i][0]==-1)
        {
            firebar_ptr[i].x=firebar_data[i][0];
            break;
        }
        if(turnspeed[i][0]==-1){
            firebar_ptr[i].turn_speed=turnspeed[i][0];
            break;
        }
        firebar_ptr[i].x=firebar_data[i][0];
        firebar_ptr[i].y=firebar_data[i][1];
        firebar_ptr[i].img=al_load_bitmap("media/pictures/obstacle/firebar.png");
        firebar_ptr[i].height=al_get_bitmap_height(firebar_ptr[i].img);
        firebar_ptr[i].width=al_get_bitmap_width(firebar_ptr[i].img);
        firebar_ptr[i].damage=0.5;
        firebar_ptr[i].r=sqrt(pow(al_get_bitmap_height(firebar_ptr[i].img),2) + pow(al_get_bitmap_width(firebar_ptr[i].img),2));
        firebar_ptr[i].angle=0;
        firebar_ptr[i].left_mid_x = firebar_ptr[i].x;
        firebar_ptr[i].left_mid_y = firebar_ptr[i].y + firebar_ptr[i].height/2;
        firebar_ptr[i].right_mid_x = firebar_ptr[i].x + firebar_ptr[i].width;
        firebar_ptr[i].right_mid_y = firebar_ptr[i].y + firebar_ptr[i].height/2;
        firebar_ptr[i].centerx= firebar_ptr[i].x + firebar_ptr[i].width/2;
        firebar_ptr[i].centery= firebar_ptr[i].y + firebar_ptr[i].height/2;
        firebar_ptr[i].turn_speed=turnspeed[i][0];
    }

}

void firebar_rotate(TANK* tank,FIREBAR *firebar)
{
    int i=0;
    float pi=3.1415926;
    for(i=0;i<FIREBAR_NUM;i++){
        if(firebar[i].x==-1)
            break;
        else{
            float x=firebar[i].x;
            float y=firebar[i].y;
            float nx1=0,ny1=0,nx2=0,ny2=0;
            float width=firebar[i].width;
            float height=firebar[i].height;
            nx1 = firebar[i].left_mid_x - firebar[i].centerx;
            ny1 = firebar[i].left_mid_y - firebar[i].centery;
            nx2 = firebar[i].right_mid_x - firebar[i].centerx;
            ny2 = firebar[i].right_mid_y - firebar[i].centery;
            firebar[i].left_mid_x = nx1*cos(-pi/(180*firebar[i].turn_speed)) + ny1*sin(-pi/(180*firebar[i].turn_speed)) + firebar[i].centerx;
            firebar[i].left_mid_y = -nx1*sin(-pi/(180*firebar[i].turn_speed)) + ny1*cos(-pi/(180*firebar[i].turn_speed)) + firebar[i].centery;
            firebar[i].right_mid_x = nx2*cos(-pi/(180*firebar[i].turn_speed)) + ny2*sin(-pi/(180*firebar[i].turn_speed)) + firebar[i].centerx ;
            firebar[i].right_mid_y = -nx2*sin(-pi/(180*firebar[i].turn_speed)) + ny2*cos(-pi/(180*firebar[i].turn_speed)) + firebar[i].centery ;
            //al_draw_rectangle(firebar->x,firebar->y, firebar->x + firebar->width,firebar->y + firebar->height, al_map_rgb(255,255,255),1);
            //al_draw_line(firebar->left_mid_x,firebar->left_mid_y,firebar->right_mid_x ,firebar->right_mid_y,al_map_rgb(255,255,255),firebar->height/2);
            firebar[i].angle=firebar[i].angle+(pi/(180*firebar[i].turn_speed));
        }
    }
}


