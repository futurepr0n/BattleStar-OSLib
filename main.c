#include <pspkernel.h>
#include <oslib/oslib.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspaudio.h>
#include <pspaudiolib.h>
#include <psppower.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3player.h"
#include "loadobj.h"
#include "blitobj.h"
#include "init.h"
//#include "audio.h"
#include "control.h"
#include "displayscore.h"
#include "movement.h"
#include <unistd.h>
#include <mikmod.h>
#include <psputility_sysparam.h>


#define MAX_NUM_BULLETS 100
#define MAX_NUM_ENEMIES 100

PSP_MODULE_INFO("BattleStar OSLib", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(12*1024);

char playerName[128];

// EXIT CALLBACK
/* Exit callback */
//int exit_callback(int arg1, int arg2, void *common) {
//    osl_quit = 1;
//    return 0;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    int skip = 0;

    //Get player name
    sceUtilityGetSystemParamString(PSP_SYSTEMPARAM_ID_STRING_NICKNAME, playerName, 127);


    initOSLib();
    pspAudioInit();
    initMusic();
 
    oslIntraFontInit(INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8); // All fonts loaded with oslLoadIntraFontFile will have UTF8 support

    //Loads image:
    OSL_IMAGE *bkg = oslLoadImageFilePNG("bsg_title.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);

    
    loadCharacterData();
    
    //Load font:
    // OSL_FONT *pgfFont = oslLoadFontFile("flash0:/font/ltn8.pgf");
    OSL_FONT *pgfFont = oslLoadFontFile("ltn8.pgf");
    oslIntraFontSetStyle(pgfFont, 1.0, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
    oslSetFont(pgfFont);

    //Starts to play MP3    
    MP3_Play();

/////////////////////////////////
// Splash Screen
/////////////////////////////////

    while(!osl_quit){
        if (!skip){
            oslStartDrawing();

            oslDrawImageXY(bkg, 0, 0);

	    //Draw Fonts:
	    float t = ((float)(clock() % CLOCKS_PER_SEC)) / ((float)CLOCKS_PER_SEC);
            int val = (t < 0.5f) ? t*511 : (1.0f-t)*511;
            oslIntraFontSetStyle(pgfFont, 1.0f,LITEGRAY,(0xFF<<24)+(val<<16)+(val<<8)+(val),0);
            oslDrawString(180, 200, "BattleStar Galactica");
            oslIntraFontSetStyle(pgfFont, 1.0f,WHITE,BLACK,0);
            oslDrawString(150, 250, "Press X to Start");

            oslEndDrawing();
        }
        oslEndFrame();
        skip = oslSyncFrame();

		if(MP3_EndOfStream() == 1)
			MP3_Stop();

        oslReadKeys();
        if (osl_keys->released.cross)
            break; //oslQuit();

    }
	MP3_Stop(1);
   	MP3_FreeTune(1);
    
	setupMikMod();


///////////////////////////////////////
// Main Game Loop
///////////////////////////////////////
    
    while(!osl_quit){
        if (!skip){
            oslStartDrawing();
 	        moveStuff();

            blitEnemies();		

            control();

            if(MP3_EndOfStream() == 1)
		        MP3_Stop();


            blitObj(player);
            blitObj(battlestar);
            blitObj(hs_bar);
            blitObj(status_bar);
            oslIntraFontSetStyle(pgfFont, 0.65f,WHITE,BLACK,0);
            oslDrawString(2,230,playerName);
            printScore();
            oslEndDrawing();      
       
        }
         
        oslEndFrame();
        skip = oslSyncFrame();

	    // if(MP3_EndOfStream() == 1)
		//     MP3_Stop();

       
    }
	//MP3_Stop(1);
   	//MP3_FreeTune(1);
        
    //Quit OSL:
    oslEndGfx();

    // Quit MikMod
    quitMikMod();

    // Kernel Exit
    sceKernelExitGame();
    return 0;

}
