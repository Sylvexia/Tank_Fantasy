#ifndef _SAVE_H_
#define _SAVE_H_
#include <string.h>
#include "game_state.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

typedef struct save{
    char buf[50];
	int score;
}inf;

void printf_save();
bool input_fuc(int keycode,int*input);
void write_save(int score,char *name);

#endif // _SAVE_H_
