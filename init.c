// init.c
#include <oslib/oslib.h>
#include "mp3player.h"

int initOSLib(){
    oslInit(0);
    oslInitGfx(OSL_PF_8888, 1);
    oslInitAudio();
    oslSetQuitOnLoadFailure(1);
    oslSetKeyAutorepeatInit(40);
    oslSetKeyAutorepeatInterval(10);
    return 0;
}

void initMusic(){
	MP3_Init(1);
	MP3_Load("theme_battlestar_galactica.mp3");
}

