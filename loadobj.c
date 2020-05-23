// loadobj.c: Blitting a player
//
////////////////////////////////////////////////////////////////////////////
#include <oslib/oslib.h>
#include "loadobj.h"

void loadCharacterData(){
	loadPlayer();
	loadEnemies();
	loadEnemyBattlestar();
	loadChain();
	loadBackground();
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

void loadEnemyBattlestar(){
	battlestar.x = 10050;
	battlestar.y = (272/2) + 17;
	battlestar.imgX = 220;
	battlestar.imgY = 76;
	//battlestar.health = 1000;
	battlestar.img = oslLoadImageFilePNG("battlestar.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
		if(!battlestar.img){
			printf("battlestar.img failed to load..");
		}
	battlestar.isalive = 1;
}

void loadBackground(){
	
	background.x = 0;
	background.y = 0;
	background.imgX = 480;
	background.imgY = 272;
    background.img = oslLoadImageFilePNG("space_bg.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
    
	if(!background.img){
		printf("Background image failed to load...");
	}
	background.isalive = 1;
}