#include "save.h"

void printf_save(){

    ALLEGRO_FONT *font= al_load_font("media/fonts/DFT_TL9.TTC", 50, 0);
    char buf[50];
    int i;
    ALLEGRO_FILE *f=NULL;
    f=al_fopen("./score.txt", "r");
    for(i=1;i<=5;i++){
        al_fgets(f, buf, 50);
        al_draw_text(font,al_map_rgb(255,255,255),200,-100+140*i, ALLEGRO_ALIGN_LEFT,&buf);
        }
     al_fclose(f);
     al_destroy_font(font);

}

bool input_fuc(int keycode,int*input){

    if(keycode>=1 &&keycode<=26){

            *input=keycode+96;
            return true;

    }
    else if(keycode>=27 &&keycode<=36){

            *input=keycode+21;
            return true;

    }
    else{
        return false;
    }
}

void write_save(int score,char *name){

    inf save[5];
    int i,j;
    char c[8];
    time_t t;
    t=time(NULL);

    sprintf(c,"%d",score);    /**�Nint�ন�r��**/
    ALLEGRO_FILE *f=NULL;
    f=al_fopen("./score.txt", "r");
    for(i=0;i<=4;i++){
        al_fgets(f, save[i].buf, 50);    /**�N���e�������s�_�ӡA�H�U�󤧫᧹����g**/
        sscanf(save[i].buf,"%d",&save[i].score);  /**�N�r���ন�Ʀr**/
        }
    al_fclose(f);
    f=al_fopen("./score.txt", "w+");
    for(i=4;i>=0;i--){
        if (score>=save[0].score){
            al_fputs(f,c);
            al_fputs(f," ");
            al_fputs(f,name);                   /**�g�J����������T**/
            al_fputs(f," ");
            al_fputs(f,ctime(&t));            /**��J�ɶ�**/
            for(j=0;j<4;j++){
                al_fputs(f,save[j].buf);        /**�g�J�W��������T**/
            }
            break;
        }
        if(score<save[i].score){
            for(j=0;j<=4;j++){
                al_fputs(f,save[j].buf);
                if(i==j){
            al_fputs(f,c);
            al_fputs(f," ");
            al_fputs(f,name);
            al_fputs(f," ");
            al_fputs(f,ctime(&t));
                }
            }
            break;
        }



    }
    al_fclose(f);           /**�����g�J**/
}

void print_input(char* name,int score){

    ALLEGRO_FONT *font= al_load_font("media/fonts/DFT_TL9.TTC", 50, 0);
    al_draw_textf(font,al_map_rgb(255,255,255),200,710, ALLEGRO_ALIGN_LEFT,"your name is : %s score : %d ",name,score);
    al_destroy_font(font);

}

void delete_save(){

    ALLEGRO_FILE *f=NULL;
    f=al_fopen("./score.txt", "w+");
;
    al_fputs(f," ");
    al_fclose(f);
}
