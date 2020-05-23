#include <oslib/oslib.h>
//#include "loadobj.h"
#include "control.h"

int bullets = 0;

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
