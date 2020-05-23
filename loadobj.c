// loadobj.c: Blitting a player
//
////////////////////////////////////////////////////////////////////////////
#include <oslib/oslib.h>
#include "loadobj.h"

void loadCharacterData(){
	loadPlayer();
	loadEnemies();
	loadChain();
}

void loadPlayer(){
	
	player.x = 10;
	player.y = 80;
	player.imgX = 46;
	player.imgY = 24 ;
	player.img = oslLoadImageFilePNG("viper.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
      
	if(!player.img){
		printf("Player image failed to load...");
	}
	player.isalive = 1;
}

void loadChain(){
	int i;	
	for(i = 0; i < MAX_NUM_BULLETS; i++){
		chain[i].x = 0;
		chain[i].y = 0;
		chain[i].imgX = 8;
		chain[i].imgY = 6;
		chain[i].img  = oslLoadImageFilePNG("chain.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
		if(!chain[i].img){
			printf("chain image failed to load...");
		}
		chain[i].isalive = 0;
		chain[i].pctr = 0;
	}
}

void loadEnemies(){
	int i;	
	for(i = 0; i < MAX_NUM_ENEMIES; i++){
		enemy[i].x = 480 + ((int)rand()%10000);
		enemy[i].y = 1 + ((int)rand()%272 - 34);
		enemy[i].imgX = 42;
		enemy[i].imgY = 20;
		enemy[i].img = oslLoadImageFilePNG("raidersm.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
		if(!enemy[i].img){
			printf("Enemy image failed to load...");
		}
		enemy[i].isalive = 1;
		enemy[i].pctr = 0;
		
	}
	
}