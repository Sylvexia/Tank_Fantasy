#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <allegro5/allegro.h>
#include "tank.h"

typedef struct CAMERA{

    ALLEGRO_TRANSFORM* cam;
    float cameraPosition[2];

}CAMERA;

void CameraUpdate(CAMERA* camera,TANK* tank_ptr);
void change_transform(CAMERA* camera);
void init_camera(CAMERA* camera,ALLEGRO_TRANSFORM* cam);
void fix_camara(CAMERA *camera);

#endif // _CAMERA_H_
