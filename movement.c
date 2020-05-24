//movement.c
#include "control.h"

int bullets = 0;

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

void scrollStarfield(){
	starfield.x = starfield.x-10; 
    blitObj(starfield); 
 
    if(starfield.x < 0){
         	blitBg(starfield);
    	if(starfield.x<-480){
      		starfield.x = 0;
       	} 
	}
	if(starfield.x > 1){
    	starfield.x = -480 ;
	   	blitBg(starfield);
	   	if(starfield.x > 480){
	   		starfield.x = 0;
	    }	     	
	}
}