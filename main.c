#include <pspkernel.h>
#include <oslib/oslib.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspaudio.h>
#include <pspaudiolib.h>
#include <psppower.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include "mp3player.h"
#include "loadobj.h"
#include "blitobj.h"
#include "init.h"

#define MAX_NUM_BULLETS 100
#define MAX_NUM_ENEMIES 100

PSP_MODULE_INFO("BattleStar OSLib", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_KB(12*1024);

int bullets = 0;
int points = 0;
int hScore = 200;
char playerScore[5];
char highScore[5];

// Colors
enum colors {
    RED =	0xFF0000FF,
    GREEN =	0xFF00FF00,
    BLUE =	0xFFFF0000,
    WHITE =	0xFFFFFFFF,
    LITEGRAY = 0xFFBFBFBF,
    GRAY =  0xFF7F7F7F,
    DARKGRAY = 0xFF3F3F3F,
    BLACK = 0xFF000000
};

// typedef struct{
// 	int x;
// 	int y;
// 	int imgX;
// 	int imgY;
// 	//int dir;
// 	OSL_IMAGE *img;
// 	int isalive;	
// 	int pctr;
// }obj;

// obj background;
// obj player;
// obj sprite;
// obj enemy[MAX_NUM_ENEMIES];
// obj chain[MAX_NUM_BULLETS];



// EXIT CALLBACK
/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
    osl_quit = 1;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init OSLib:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int initOSLib(){
//     oslInit(0);
//     oslInitGfx(OSL_PF_8888, 1);
//     oslInitAudio();
//     oslSetQuitOnLoadFailure(1);
//     oslSetKeyAutorepeatInit(40);
//     oslSetKeyAutorepeatInterval(10);
//     return 0;
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init Music:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// void initMusic(){
// 	MP3_Init(1);
// 	MP3_Load("theme_battlestar_galactica.mp3");
// }

// Init Scrolling Background
//void initBackground();
void scrollBackground();
void blitBg(obj object);
void blitEnemies();
void shootChain();
int checkCollision(obj blt);
void control();
void printScore();





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
//    OSL_FONT *pgfFont = oslLoadFontFile("flash0:/font/ltn8.pgf");
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
            oslDrawString(150, 250, "Press X to quit");

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
    
    int p = 0;
    
    
///////////////////////////////////////
// Main Game Loop
///////////////////////////////////////
    
    while(!osl_quit){
        if (!skip){
            oslStartDrawing();
            scrollBackground();
            blitEnemies();		
            
            
            control();
            for(p = 0; p < MAX_NUM_BULLETS; p++){
			    chain[p].isalive = checkCollision(chain[p]);
			    if(chain[p].isalive == 1){
       			    chain[p].x = chain[p].x + 10  * 1.5F;      			
				    blitObj(chain[p]);					
			    }else{
				    chain[p].isalive = 0;
				    chain[p].pctr = 0;
			    }			
			    if(chain[p].x > 485){
					chain[p].isalive = 0;
					chain[p].pctr = 0;
			    }
		    }       
            blitObj(player);
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

    sceKernelExitGame();
    return 0;

}

void shootChain(){
	if(bullets < MAX_NUM_BULLETS && chain[bullets].isalive == 0){
		chain[bullets].isalive = 1;
		chain[bullets].x = player.x + 42;
		chain[bullets].y = player.y + (player.imgY / 2);
	} 
	
	bullets++;
	if(bullets > MAX_NUM_BULLETS){
		bullets = 0;
	}
}

void scrollBackground(){

	background.x = background.x-5; 
    //oslDrawImageXY(background.img, background.x, background.y); 
    blitObj(background);
    if(background.x < 0){
         	blitBg(background); 
    	if(background.x<-480){
      		background.x = 0;
       	} 
	}
	if(background.x > 1){
    	background.x = -480 ;
	   	blitBg(background); 
	   	if(background.x > 480){
	   	background.x = 0;
	    }	     	
	}
}

// void initBackground(){
	
// 	background.x = 0;
// 	background.y = 0;
// 	background.imgX = 480;
// 	background.imgY = 272;
//     background.img = oslLoadImageFilePNG("space_bg.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
    
// 	if(!background.img){
// 		printf("Background image failed to load...");
// 	}
// 	background.isalive = 1;
// }


void blitBg(obj object){
	object.x = object.x + 480;
    oslDrawImageXY(object.img, object.x, object.y);
	//blitAlphaImageToScreen(0, 0, object.imgX, object.imgY, object.img, object.x, object.y);
}


int checkCollision(obj blt){
	int c_ctr;
	if(blt.isalive == 1){
		//blt.x = blt.x + (8 * 1.5F);
		for(c_ctr = 0; c_ctr < MAX_NUM_ENEMIES; c_ctr++){	
			if((blt.x >= enemy[c_ctr].x && blt.y < enemy[c_ctr].y + 20) && (blt.x < enemy[c_ctr].x + 42 && blt.y >= enemy[c_ctr].y)){
				enemy[c_ctr].isalive = 0;
				points = points + 10;
				blt.isalive = 0;
			}
		}
	}
	return(blt.isalive);
}


void blitEnemies(){
	int enemy_ctr;		
	for(enemy_ctr = 0; enemy_ctr < MAX_NUM_ENEMIES; enemy_ctr++)
		{
			if(enemy[enemy_ctr].isalive == 1){
				float mtpl = ((int)rand()%7) * 2.1;
				
	     		enemy[enemy_ctr].x = enemy[enemy_ctr].x - mtpl;
				if(enemy[enemy_ctr].x < 0){
					enemy[enemy_ctr].isalive = 0;
				}
	     		blitObj(enemy[enemy_ctr]);
	     	} else {
	     		//free up memory.. do not blit to screen
	     		enemy[enemy_ctr].x = 500;
	     	}
		}
}

void control()
{
     oslReadKeys();
        if (osl_keys->pressed.circle){
            shootChain();
            //    oslQuit();
        }   
        if((osl_keys->held.right)&&player.x <= 150){player.x = player.x + 1;}      
        if((osl_keys->held.left)&&player.x > 60){player.x = player.x - 1;} 
        if((osl_keys->held.up)&&player.y > -10){player.y = player.y - 5;}  
        if((osl_keys->held.down)&&player.y < 262){player.y = player.y + 5;}
}

void printScore(){
	/* player score */
    //oslIntraFontSetStyle(pgfFont, 1.0f,WHITE,BLACK,0);
    oslDrawString(340, 10, "Score:");
	sprintf(playerScore,"%d",points);
	oslDrawString(440,10,playerScore);
	/* High Score */
    oslDrawString(200, 10, "High Score:");
	//printTextScreen(200,0,"High Score:",RGB_WHITE);
	if(hScore > points){
		/* print HighScore */
		sprintf(highScore,"%d",hScore);
		oslDrawString(300,10,highScore);
		//printTextScreen(300,0,highScore,RGB_RED);
	}else{
		/* player score is the high score! */
		oslDrawString(300,10,playerScore);
		//printTextScreen(300,0,playerScore,RGB_YELLOW);
	}
}
