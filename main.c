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
//#include "control.h"
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

//int bullets = 0;

/*mikmod specific*/
extern int _mm_errno;
extern BOOL _mm_critical;
extern char *_mm_errmsg[];
int mikModThreadID = -1;
int done = 0;


extern UWORD md_mode;
extern UBYTE md_reverb;
extern UBYTE md_pansep;

static int AudioChannelThread(int args, void *argp)
{
  while (!done)
  {
    MikMod_Update();
    // We have to sleep here to allow other threads a chance to process.
    // with no sleep this thread will take over when the output is disabled via MikMod_DisableOutput()
    // co-operative threading sucks bigtime...
    sceKernelDelayThread(1);
  }
  return (0);
}

void my_error_handler(void)
{
	printf("_mm_critical %d\n", MikMod_critical);
	printf("_mm_errno %d\n", MikMod_errno);
	printf("%s\n", MikMod_strerror(MikMod_errno));
	return;
}

BOOL outputEnabled;
int maxchan = 128;
MODULE *mf = NULL; // for mod
SAMPLE *sf = NULL; // for wav
int voice = 0; 	   // for wav
int pan = 127;
int vol = 127;
int freq = 22000;



// /*****************/


// EXIT CALLBACK
/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
    osl_quit = 1;
    return 0;
}

// Init Scrolling Background
//void scrollBackground();
void control();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    int skip = 0;

    initOSLib();
	pspAudioInit();
	initMusic();
    //oslIntraFontInit(INTRAFONT_CACHE_MED);
	oslIntraFontInit(INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8); // All fonts loaded with oslLoadIntraFontFile will have UTF8 support

    //Loads image:
    OSL_IMAGE *bkg = oslLoadImageFilePNG("bsg_title.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
    //background.img = oslLoadImageFilePNG("space_bg.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
    
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
    
    // int p = 0;
    
///////////////////////////////////////
// Set up Mikmod stuff
///////////////////////////////////////
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(1);

    if (!MikMod_InitThreads()){
        printf("MikMod thread init failed\n");
 	}
     
    MikMod_RegisterErrorHandler(my_error_handler);
  	/* register all the drivers */
  	MikMod_RegisterAllDrivers();
  	/* register all the module loaders */
  	MikMod_RegisterAllLoaders();

    /* initialize the library */
	md_mode = DMODE_16BITS|DMODE_STEREO|DMODE_SOFT_SNDFX|DMODE_SOFT_MUSIC; 
	md_reverb = 0;
	md_pansep = 128;
  	if (MikMod_Init("")){
   		printf("Could not initialize sound, reason: %s\n", MikMod_strerror(MikMod_errno));
    	sceKernelExitGame();
    	return 0;
    }
  
  	MikMod_SetNumVoices(-1, 8);
	/* get ready to play */
    //int v1;
	sf = Sample_Load("ViperFiring.wav");
    //MikMod_SetNumVoices(-1, 2);
    outputEnabled = 1;


	mf = Player_Load("mrdeath_-_12th_moon_rising.xm", maxchan, 0);
    	if (NULL != mf){
    		mf->wrap = 1;
			Player_Start(mf);
    	}
	MikMod_EnableOutput();
  	//BOOL outputEnabled = true;
  	if ((mikModThreadID = sceKernelCreateThread("MikMod" ,(void*)&AudioChannelThread,0x12,0x10000,0,NULL)) > 0){
    	sceKernelStartThread(mikModThreadID, 0 , NULL);
	}
  	else{
    	printf("Play thread create failed!\n");
  	}    




///////////////////////////////////////
// Main Game Loop
///////////////////////////////////////
    
    while(!osl_quit){
        if (!skip){
            oslStartDrawing();
			moveStuff();
            // scrollBackground();
			// scrollStarfield();
            blitEnemies();		
            
            

            //  /* play first sample */
            // v1 = Sample_Play(sf, 0, 0);
            // for(int i = 0; i < 5; i++) {
            //     MikMod_Update();
            //     sleep(100000);
            // }
            control();




            // if(battlestar.x > (480-230)){
			//     battlestar.x = battlestar.x - 5;
		    // }

            // for(p = 0; p < MAX_NUM_BULLETS; p++){
			//     chain[p].isalive = checkCollision(chain[p]);
			//     if(chain[p].isalive == 1){
       		// 	    chain[p].x = chain[p].x + 10  * 1.5F;      			
			// 	    blitObj(chain[p]);					
			//     }else{
			// 	    chain[p].isalive = 0;
			// 	    chain[p].pctr = 0;
			//     }			
			//     if(chain[p].x > 485){
			// 		chain[p].isalive = 0;
			// 		chain[p].pctr = 0;
			//     }
		    // }       

            if(MP3_EndOfStream() == 1)
			    MP3_Stop();


            blitObj(player);
            blitObj(battlestar);
            printScore();
       
            oslEndDrawing();      
       
        }
         
        oslEndFrame();
        skip = oslSyncFrame();

		if(MP3_EndOfStream() == 1)
			MP3_Stop();

       
    }
	MP3_Stop(1);
   	MP3_FreeTune(1);
        
    //Quit OSL:
    oslEndGfx();

    // Quit MikMod

   	
   	if (mikModThreadID > 0){
    	SceUInt timeout = 100000;
   		sceKernelWaitThreadEnd(mikModThreadID, &timeout);
    	// not 100% sure if this is necessary after a clean exit, but just to make sure any resources are freed:
    	sceKernelDeleteThread(mikModThreadID);
  	}
  	Player_Stop();
	Player_Free(mf);
	MikMod_Exit();

    // Kernel Exit
    sceKernelExitGame();
    return 0;

}


void control()
{
     oslReadKeys();
        if (osl_keys->held.circle){
            shootChain();
            voice = Sample_Play(sf,0,0);
			Voice_SetPanning(voice, pan);
            //    oslQuit();
        }   
        if((osl_keys->held.right)&&player.x <= 150){player.x = player.x + 1;}      
        if((osl_keys->held.left)&&player.x > 60){player.x = player.x - 1;} 
        if((osl_keys->held.up)&&player.y > -10){player.y = player.y - 5;}  
        if((osl_keys->held.down)&&player.y < 262){player.y = player.y + 5;}
}
