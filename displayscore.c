// displayscore.c for displayscore
#include <psppower.h>
#include <pspdisplay.h>
#include <pspkernel.h>
#include <pspgu.h>
#include <pspgum.h>
#include <pspdisplay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <oslib/oslib.h>
#include "loadobj.h"
#include "displayscore.h"


int points = 0;
int hScore = 200;
char playerScore[5];
char highScore[5];


//oslIntraFontInit(INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8); // All fonts loaded with oslLoadIntraFontFile will have UTF8 support

//OSL_FONT *pgfFont = oslLoadFontFile("ltn8.pgf");
//oslIntraFontSetStyle(pgfFont, 1.0, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
//oslSetFont(pgfFont);


void printScore(){
	/* player score */


    //oslIntraFontSetStyle(pgfFont, 1.0f,WHITE,BLACK,0);
    oslDrawString(340, 0, "Score:");
	sprintf(playerScore,"%d",points);
	oslDrawString(440,0,playerScore);
	/* High Score */
    oslDrawString(200, 0, "High Score:");
	if(hScore > points){
		/* print HighScore */
		sprintf(highScore,"%d",hScore);
		oslDrawString(300,0,highScore);
	}else{
		/* player score is the high score! */
		//Draw Fonts:
		//oslIntraFontSetStyle(pgfFont, 1.0f,GRAY,WHITE,0);
		oslDrawString(300,0,playerScore);
		//printTextScreen(300,0,playerScore,RGB_YELLOW);
	}
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

void fontInit(){
	//initOSLib();
	oslIntraFontInit(INTRAFONT_CACHE_ALL | INTRAFONT_STRING_UTF8); // All fonts loaded with oslLoadIntraFontFile will have UTF8 support

	// OSL_FONT *pgfFont = oslLoadFontFile("ltn8.pgf");
    // oslIntraFontSetStyle(pgfFont, 1.0, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
    // oslSetFont(pgfFont);
}


void drawSplashText(){
			//fontInit();
			OSL_FONT *pgfFont = oslLoadFontFile("ltn8.pgf");
    		oslIntraFontSetStyle(pgfFont, 1.0, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
    		oslSetFont(pgfFont);
			float t = ((float)(clock() % CLOCKS_PER_SEC)) / ((float)CLOCKS_PER_SEC);
            int val = (t < 0.5f) ? t*511 : (1.0f-t)*511;
            oslIntraFontSetStyle(pgfFont, 1.0f,LITEGRAY,(0xFF<<24)+(val<<16)+(val<<8)+(val),0);
            oslDrawString(180, 200, "BattleStar Galactica");
            oslIntraFontSetStyle(pgfFont, 1.0f,WHITE,BLACK,0);
            oslDrawString(150, 250, "Press X to Start");
}

void gameScreenFontSetup(){
	//fontInit();
	OSL_FONT *pgfFont = oslLoadFontFile("ltn8.pgf");
    //oslIntraFontSetStyle(pgfFont, 1.0, RGBA(255,255,255,255), RGBA(0,0,0,0), INTRAFONT_ALIGN_LEFT);
    oslSetFont(pgfFont);
	//OSL_FONT *pgfFont = oslLoadFontFile("ltn8.pgf");
	oslIntraFontSetStyle(pgfFont, 0.65f,WHITE,BLACK,0);

}