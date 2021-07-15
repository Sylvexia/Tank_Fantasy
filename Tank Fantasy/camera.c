#include "camera.h"

void init_camera(CAMERA* camera,ALLEGRO_TRANSFORM* cam)
{
    camera->cam=cam;

    camera->cameraPosition[0]=0.0;
    camera->cameraPosition[1]=0.0;

}

void change_transform(CAMERA* camera)
{

    al_identity_transform(camera->cam);//確定改變對象
    al_translate_transform(camera->cam,-camera->cameraPosition[0],
                           -camera->cameraPosition[1]);//調整視角座標x,y
    al_use_transform(camera->cam);//display
}

void CameraUpdate(CAMERA* camera,TANK* tank_ptr)
{
    /*
    //視角需變換座標量計算

    width is x to 視角開始變化區的距離
    height is y to 視角開始變化區的距離

    x+width/2 is 角色測量點的x座標
    y+heigh/2 is 角色測量點的Y座標

    cameraPosition[0] is 角色X座標測量點變化值
    cameraPosition[1] is 角色Y座標測量點變化值

    (scr_w/2)為變換視角的X界線
    (scr_h/2)為變換視角的Y界線

    視角座標 X: originX - cameraPosition[0]
    視角座標 Y: originY - cameraPosition[1]
    because 角色移動量與視角座標改變量相反

    */

    camera->cameraPosition[0] =
        -(scr_w / 2) + (tank_ptr->x + tank_ptr->r);
    camera->cameraPosition[1] =
        -(scr_h / 2) + (tank_ptr->y + tank_ptr->r);



    /*

    限制變化量在一個範圍內時，視角座標不變


    */
    if(camera->cameraPosition[0] < 0)
        camera->cameraPosition[0]=0;//視角座標X
    if(camera->cameraPosition[1]<0)
        camera->cameraPosition[1]=0;//視角座標Y

    change_transform(camera);

}

void fix_camara(CAMERA *camera)
{

        camera->cameraPosition[0]=0;//視角座標X
        camera->cameraPosition[1]=0;//視角座標Y

        change_transform(camera);


    //new
    if(camera->cameraPosition[0] > scr_w /2+100)
        camera->cameraPosition[0]=scr_w/2+100;//視角座標X
    if(camera->cameraPosition[1] > scr_h +100)
        camera->cameraPosition[1]=scr_h +100;//視角座標Y
//new
    change_transform(camera);

}

