#include "camera.h"

void init_camera(CAMERA* camera,ALLEGRO_TRANSFORM* cam)
{
    camera->cam=cam;

    camera->cameraPosition[0]=0.0;
    camera->cameraPosition[1]=0.0;

}

void change_transform(CAMERA* camera)
{

    al_identity_transform(camera->cam);//�T�w���ܹ�H
    al_translate_transform(camera->cam,-camera->cameraPosition[0],
                           -camera->cameraPosition[1]);//�վ�����y��x,y
    al_use_transform(camera->cam);//display
}

void CameraUpdate(CAMERA* camera,TANK* tank_ptr)
{
    /*
    //�������ܴ��y�жq�p��

    width is x to �����}�l�ܤưϪ��Z��
    height is y to �����}�l�ܤưϪ��Z��

    x+width/2 is ������q�I��x�y��
    y+heigh/2 is ������q�I��Y�y��

    cameraPosition[0] is ����X�y�д��q�I�ܤƭ�
    cameraPosition[1] is ����Y�y�д��q�I�ܤƭ�

    (scr_w/2)���ܴ�������X�ɽu
    (scr_h/2)���ܴ�������Y�ɽu

    �����y�� X: originX - cameraPosition[0]
    �����y�� Y: originY - cameraPosition[1]
    because ���Ⲿ�ʶq�P�����y�Ч��ܶq�ۤ�

    */

    camera->cameraPosition[0] =
        -(scr_w / 2) + (tank_ptr->x + tank_ptr->r);
    camera->cameraPosition[1] =
        -(scr_h / 2) + (tank_ptr->y + tank_ptr->r);



    /*

    �����ܤƶq�b�@�ӽd�򤺮ɡA�����y�Ф���


    */
    if(camera->cameraPosition[0] < 0)
        camera->cameraPosition[0]=0;//�����y��X
    if(camera->cameraPosition[1]<0)
        camera->cameraPosition[1]=0;//�����y��Y

    change_transform(camera);

}

void fix_camara(CAMERA *camera)
{

        camera->cameraPosition[0]=0;//�����y��X
        camera->cameraPosition[1]=0;//�����y��Y

        change_transform(camera);


    //new
    if(camera->cameraPosition[0] > scr_w /2+100)
        camera->cameraPosition[0]=scr_w/2+100;//�����y��X
    if(camera->cameraPosition[1] > scr_h +100)
        camera->cameraPosition[1]=scr_h +100;//�����y��Y
//new
    change_transform(camera);

}

