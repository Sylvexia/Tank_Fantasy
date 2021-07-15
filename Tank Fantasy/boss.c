#include"boss.h"


void init_boss(BOSS_STATE *boss_state,BULLET *bullet)
{

    boss_state->img=al_load_bitmap("media/pictures/boss/boss.png");

    boss_state->width=al_get_bitmap_width(boss_state->img);
    boss_state->height= al_get_bitmap_height(boss_state->img);

    boss_state->x=10;
    boss_state->y=10;
    boss_state->ox=10;
    boss_state->oy=10;
    boss_state->center_x=boss_state->x+boss_state->width/2;
    boss_state->center_y=boss_state->y+boss_state->height/2;

    boss_state->hp=total_hp;
    boss_state->speed=5;
    boss_state->damage=1;//collision damage
    boss_state->laser.damage=0.5;
    boss_state->dir=rand()%4;
    boss_state->r=300;

    boss_state->mode=1;

    boss_state->bullet=bullet;

    boss_state->is_damaged=false;

    init_boss_angle(boss_state);//¼Ò¦¡¤G¤l¼u¥Î


    boss_state->emitTime.timer=0;
    boss_state->emitTime.active=false;
    boss_state->emitTime.finish=1;//5*1/60 s


    boss_state->Timer.timer=0;
    boss_state->Timer.active=true;
    boss_state->Timer.finish=300;





}


void init_boss_angle(BOSS_STATE* boss_state)
{

    int number=0;

    double angle[angle_num]= {0.3, 0.5, 0.7, 1, 1.5, 2, 2.5,2.7, 2.9, 3,
                              3.2, 3.5, 3.8, 4, 4.3, 4.5, 4.7, 5, 5.2, 5.5,
                              5.7,5.9, 6.1, 6.3
                             };

    for(number=0; number<angle_num; number++)
    {
        boss_state->angle[number]=angle[number];
    }

}

void init_b_bullet(BULLET* bullet)
{
    int number=0;

    for(number=0; number<ballnum; number++)
    {
        bullet[number].x=-100;
        bullet[number].y=-100;
        bullet[number].d=55;
        bullet[number].speed=10;
        bullet[number].r=30;
        bullet[number].angle=0;
        bullet[number].active=false;
        bullet[number].hp=100;
        bullet[number].damage=1;
    }
}




void boss_action(BOSS_STATE *boss_state,TANK *tank,ALLEGRO_KEYBOARD_STATE *key_state )
{

//改變移動方向並計算模式時間,mode=1
    if(boss_state->mode==1)
    {

//計時器
        if(boss_state->Timer.active)
            boss_state->Timer.timer++;

//每20/60秒換方向
        if(boss_state->Timer.timer%60==20)
        {
            boss_state->dir=rand()%4;
        }

//判斷邊界範圍反彈

        if(boss_state->x > 1.3*scr_w)
        {
            boss_state->dir=bLEFT;

        }
        else if(boss_state->x < boss_state->width+250 )
        {
            boss_state->dir=bRIGHT;

        }
        else if(boss_state->y > 1.3*scr_h )
        {
            boss_state->dir=bUP;

        }
        else if(boss_state->y < boss_state->height+250 )
        {
            boss_state->dir=bDOWN;

        }


//切換模式
        if(boss_state->Timer.timer>=300)
        {

            boss_state->dir=bSTATIC;
            boss_state->Timer.timer=0;
            boss_state->mode=2;


        }

    }


///////////////////
    if(boss_state->mode==2)
    {
        if(boss_state->Timer.active)
            boss_state->Timer.timer++;

        boss_state->dir=bSTATIC;


//開始射擊
    boss_emit(boss_state);

//切換模式
        if(boss_state->Timer.timer==boss_state->Timer.finish) // 5s == (5*60) unit 1/60 s
        {

            boss_state->mode=3;
            boss_state->dir=bRIGHT;
            boss_state->Timer.timer=0;
        }

    }

//////////////

    if(boss_state->mode==3)
    {
        if(boss_state->Timer.active)
            boss_state->Timer.timer++;

        //boss基礎速度加快
        boss_state->speed=10;

//控制走的方向
        if(boss_state->Timer.timer<300)
        {
            if(boss_state->Timer.timer%60>50)
            {
                boss_track_move(boss_state,tank);
            }
            else
            {
                if(boss_state->Timer.timer%60==20)
                    boss_state->dir=rand()%4;
            }

//控制邊界範圍反彈

            if(boss_state->x > 1.2*scr_w)
            {
                boss_state->dir=bLEFT;
            }
            else if(boss_state->x < 0)//boss_state->width)
            {
                boss_state->dir=bRIGHT;
            }
            else if(boss_state->y > 1.5*scr_h)
            {
                boss_state->dir=bUP;
            }
            else if(boss_state->y < 0)//boss_state->height )
            {
                boss_state->dir=bDOWN;
            }
        }


        ///////設置爆炸區
        bomb(boss_state,tank);


//控制時間走到固定位置
        double dx=0,dy=0;

        dx=boss_state->x-(300);
        dy=boss_state->y-(300);

        if(boss_state->Timer.timer>=300)
        {

            boss_state->Timer.active=false;


            if(dx>10)
            {
                boss_state->dir=bLEFT;

            }
            else if(dx<-10 )
            {
                boss_state->dir=bRIGHT;

            }

            else if(dy < -10 )
            {
                boss_state->dir=bDOWN;
            }

            else if(dy>10 )
            {
                boss_state->dir=bUP;
            }


//切換模式
            if(-10 <= dx&&dx <= 10 && -10 <= dy && dy <= 10)
            {



                boss_state->mode=4;
                boss_state->dir=bRIGHT;
                boss_state->Timer.active=true;
                boss_state->speed=5;
                boss_state->Timer.timer=0;



            }

        }

    }


/////////////
    if(boss_state->mode==4)
    {

        boss_state->dir=bSTATIC;

        double distance=0.0;
        int dx=0,dy=0;

        double vectorx=0.0;
        double vectory=0.0;
        double range=2000;

        if(boss_state->Timer.active=true)
            boss_state->Timer.timer++;

//計算laser發射端點
        if(boss_state->Timer.timer==5)
        {

            dx=tank->center_x-(boss_state->x+boss_state->width/2);
            dy=tank->center_y-(boss_state->y+boss_state->height/2);
            distance=sqrt(dx*dx+dy*dy);
            vectorx=dx/distance;
            vectory=dy/distance;



            boss_state->laser.x=(boss_state->x+boss_state->width/2)+range*vectorx;
            boss_state->laser.y=(boss_state->y+boss_state->height/2)+range*vectory;
        }

//前置瞄準線
        al_draw_line(boss_state->x+boss_state->width/2,boss_state->y+boss_state->height/2
                     ,boss_state->laser.x,boss_state->laser.y,al_map_rgb(160,10,40),2);



        if(boss_state->Timer.timer>60)
        {

//發射激光
            al_draw_line(boss_state->x+boss_state->width/2,boss_state->y+boss_state->height/2
                         ,boss_state->laser.x,boss_state->laser.y,al_map_rgb(160,10,40),250);
            al_draw_line(boss_state->x+boss_state->width/2,boss_state->y+boss_state->height/2
                     ,boss_state->laser.x,boss_state->laser.y,al_map_rgb(255,255,255),100);

//判斷坦克boss碰撞

            double x1 = boss_state->x+boss_state->width/2;
            double y1 = boss_state->y+boss_state->height/2;
            double x2 = boss_state->laser.x;
            double y2 = boss_state->laser.y;
            double x3 = tank->center_x;
            double y3 = tank->center_y;
            double r=tank->r;
            double h=250;


            if(col_circle_to_line(x1,y1,x2,y2,x3,y3,r,h))
            {

                tank->is_damaged=true;

                tank->hp-=boss_state->laser.damage;
            }
        }

//切換模式
        if(boss_state->Timer.timer==120)
        {

            boss_state->mode=1;
            boss_state->dir=bRIGHT;
            boss_state->Timer.timer=0;

        }

    }


}



void  boss_new(BOSS_STATE *boss_state)
{

    boss_state->ox=boss_state->x;
    boss_state->oy=boss_state->y;

}


void boss_shoot(BOSS_STATE* boss_state)
{
    int i=0;
    int number=0;
    for(i=0; i<ballnum; i++)
    {

        number=i%angle_num;//angle number

        if(!boss_state->bullet[i].active)
        {
            boss_state->bullet[i].active=true;


            if(boss_state->hp>total_hp/2)
            {

                boss_state->bullet[i].angle=boss_state->angle[number];

            }



            else if(boss_state->hp>total_hp/3)
            {
                boss_state->bullet[i].angle=(rand()%315)*0.02;//隨機發射

            }
            else
            {

                boss_state->bullet[i].angle=(i)*0.0565;//弧度攻擊(*0.02)

            }


            find_bUV(&boss_state->bullet[i]);


            boss_state->bullet[i].d= boss_state->r+boss_state->bullet[i].r;

            boss_state->bullet[i].x=  boss_state->center_x
                                      +(boss_state->bullet[i].d)
                                      *(boss_state->bullet[i].vx );

            boss_state->bullet[i].y=  boss_state->center_y
                                      -(boss_state->bullet[i].d)
                                      *(boss_state->bullet[i].vy );


            break;

        }
    }
}



void boss_bullet_move(BOSS_STATE *boss_state)
{
    int i=0;
    for(i=0; i<ballnum; i++)
    {
        if(boss_state->bullet[i].active)
        {
            if(boss_state->bullet[i].d>bulletRange)//deactivate condition
            {
                boss_state->bullet[i].active=false;
            }

            //move
            boss_state->bullet[i].x+= boss_state->bullet[i].speed
                                      *boss_state->bullet[i].vx;

            boss_state->bullet[i].y-= boss_state->bullet[i].speed
                                      *boss_state->bullet[i].vy;

            boss_state->bullet[i].d+= boss_state->bullet[i].speed;


        }
    }
}


void boss_emit(BOSS_STATE *boss_state)
{

//檢查時間是否到定時
        boss_state->emitTime.timer++;

        if(boss_state->emitTime.timer==boss_state->emitTime.finish)
        {

            boss_state->emitTime.timer=0;
            boss_shoot(boss_state);

        }




}


void boss_center_coord(BOSS_STATE *boss_state)
{
    boss_state->center_x=boss_state->x + boss_state->width/2;
    boss_state->center_y=boss_state->y + boss_state->height/2;
}


void boss_bullet_damage(BOSS_STATE *boss_state,TANK * tank)
{

    OBSTACLE o_bullet;
    int i=0;
    bool fix=false;



    if(boss_state->mode==2)
    {
        for(i=0; i<ballnum; i++)
        {

            o_bullet.x=boss_state->bullet[i].x;
            o_bullet.y=boss_state->bullet[i].y;
            o_bullet.width=boss_state->bullet[i].r*4/3;
            o_bullet.height=boss_state->bullet[i].r*4/3;
            o_bullet.damage=boss_state->bullet[i].damage;

            if(tank->is_damaged==true)
                fix=true;

            tank_is_damaged(tank,&o_bullet);

            if(fix)
                tank->is_damaged=true;


        }
    }


}



void bomb(BOSS_STATE *boss_state,TANK *tank)
{


    if(boss_state->Timer.timer==1)
    {
        boss_state->recx=tank->x-300*2;
        boss_state->recy=tank->y-300*2;

        if(boss_state->recx>600)
        {
            boss_state->recx=600;
        }

        if(boss_state->recy>600)
        {
            boss_state->recy=600;
        }


    }


    int i=0;
    int j,k;
    bool fix=false;
    double recX=0,recY=0;

    OBSTACLE trap;

    //畫圈
    for(i=0; i<16; i++)
    {

        j=i%4;
        k=i/4;

        recX=boss_state->recx+330*j;
        recY=boss_state->recy+330*k;



        //爆炸區的資訊
        trap.x=recX;
        trap.y=recY;
        trap.height=200;
        trap.width=200;
        trap.damage=1;


        //畫爆炸區
        al_draw_rectangle(recX,recY,recX+200,recY+200,al_map_rgb(100,0,0),4);



        if( boss_state->Timer.timer%400>100)
        {
            al_draw_filled_rectangle(recX,recY,recX+200,recY+200,al_map_rgb(100,0,0));

            //檢查tank跟爆炸區
            if(tank->is_damaged==true)
            {
                fix=true;
            }

            tank_is_damaged(tank,&trap);

            if(fix==true)
            {

                tank->is_damaged=true;

            }


        }

    }


}





void tank_bullet_damage_b(BOSS_STATE *boss_state,TANK * tank)
{

    OBSTACLE o_bullet;
    int number=0;

    if(boss_state->is_damaged==false)
    {
        for(number=0; number<BULL_NUM; number++)
        {

            o_bullet.x=tank->bullet[number].x-tb_width/2;
            o_bullet.y=tank->bullet[number].y-tb_height/2;
            o_bullet.width=tb_width;
            o_bullet.height=tb_height;
            o_bullet.damage=tank->bullet[number].damage;

            boss_is_damaged(boss_state,&o_bullet);

            if (boss_state->is_damaged==true)
            {
                tank->bullet[number].x=-100;
                tank->bullet[number].y=-100;
                tank->bullet[number].d=55;
                tank->bullet[number].active=false;

                break;
            }

        }
    }

}

void boss_is_damaged(BOSS_STATE *boss_ptr,OBSTACLE *obstacle_ptr)
{
    double centerX=boss_ptr->center_x;
    double centerY=boss_ptr->center_y;
    double obstacleX=obstacle_ptr->x + obstacle_ptr->width/2;
    double obstacleY=obstacle_ptr->y + (obstacle_ptr->height/2);
    if(centerX - obstacleX < (obstacle_ptr->width + boss_ptr->width)/2 &&
            centerX - obstacleX > -(obstacle_ptr->width + boss_ptr->width)/2)
    {
        if(centerY - obstacleY < (obstacle_ptr->height + boss_ptr->height)/2 &&
                centerY - obstacleY > -(obstacle_ptr->height + boss_ptr->height)/2)
        {
            boss_ptr->is_damaged=true;
            boss_ptr->hp-=obstacle_ptr->damage;

        }
        else
        {
            boss_ptr->is_damaged=false;

        }
    }
    else
    {
        boss_ptr->is_damaged=false;

    }
}




void boss_move(BOSS_STATE *boss_state)
{

    switch(boss_state->dir)
    {

    case bRIGHT :
        boss_state->x += boss_state->speed;
        break;

    case bUP :
        boss_state->y -= boss_state->speed;
        break;

    case bLEFT :
        boss_state->x -= boss_state->speed;
        break;
    case bDOWN:
        boss_state->y += boss_state->speed;
        break;


    }

}



void boss_track_move(BOSS_STATE *boss_state,TANK *tank)/*跟隨角色*/
{
    double distance=0.0;
    double unit_vector_x=0.0;
    double unit_vector_y=0.0;
    double dx=0,dy=0;


    dx=tank->x-boss_state->x;
    dy=tank->y-boss_state->y;
    distance=sqrt(dx*dx+dy*dy);
    unit_vector_x=dx/distance;
    unit_vector_y=dy/distance;

    boss_state->x+=unit_vector_x*boss_state->speed;
    boss_state->y+=unit_vector_y*boss_state->speed;

}


