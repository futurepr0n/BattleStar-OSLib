//movement.c
#include "control.h"

int bullets = 0;
int p = 0;

void moveStuff(){
    scrollBackground();
	scrollStarfield();
    if(battlestar.x > (480-230)){
		battlestar.x = battlestar.x - 5;
	}

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

			for(p = 0; p < MAX_NUM_ENEMY_BULLETS; p++){
			    enemychain[p].isalive = checkCollision(enemychain[p]);
			    if(enemychain[p].isalive == 1){
       			    enemychain[p].x = enemychain[p].x - 5 * 1.5F;      			
				    blitObj(enemychain[p]);					
			    }else{
				    enemychain[p].isalive = 0;
				    enemychain[p].pctr = 0;
			    }			
			    if(enemychain[p].x > 0){
					enemychain[p].isalive = 0;
					enemychain[p].pctr = 0;
			    }
		    }     
    
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

// void shootEnemyChain(int z){
// 	if(bullets < MAX_NUM_ENEMY_BULLETS && enemychain[bullets].isalive == 0){
// 		enemychain[bullets].isalive = 1;
// 		enemychain[bullets].x = enemy[z].x + 42;
// 		enemychain[bullets].y = enemy[z].y + (enemy[z].imgY / 2);
// 	} 
	
// 	bullets++;
// 	if(bullets > MAX_NUM_ENEMY_BULLETS){
// 		bullets = 0;
// 	}

// }

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