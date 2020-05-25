// displayscore.c for displayscore
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

void printScore(){
	/* player score */


    //oslIntraFontSetStyle(pgfFont, 1.0f,WHITE,BLACK,0);
    oslDrawString(340, 10, "Score:");
	sprintf(playerScore,"%d",points);
	oslDrawString(440,10,playerScore);
	/* High Score */
    oslDrawString(200, 10, "High Score:");
	if(hScore > points){
		/* print HighScore */
		sprintf(highScore,"%d",hScore);
		oslDrawString(300,10,highScore);
	}else{
		/* player score is the high score! */
		//Draw Fonts:
		//oslIntraFontSetStyle(pgfFont, 1.0f,GRAY,WHITE,0);
		oslDrawString(300,10,playerScore);
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