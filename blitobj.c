// blitobj.c: Blitting a player
//
////////////////////////////////////////////////////////////////////////////
#include <oslib/oslib.h>
#include "blitobj.h"

void blitObj(obj object){
    oslDrawImageXY(object.img, object.x, object.y);

}

void blitBg(obj object){
	object.x = object.x + 480;
    oslDrawImageXY(object.img, object.x, object.y);
	//blitAlphaImageToScreen(0, 0, object.imgX, object.imgY, object.img, object.x, object.y);
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
