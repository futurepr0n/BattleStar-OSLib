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
	loadEnemyChain();
	loadBackground();
	loadStarfield();
	loadHsBar();
	loadStatusBar();
	
}

void loadPlayer(){
	
	player.x = 10;
	player.y = 80;
	player.imgX = 46;
	player.imgY = 24 ;
	player.img = oslLoadImageFilePNG("vipersm.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
    player.health = 1000;

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
		enemy[i].health = 50;
		enemy[i].img = oslLoadImageFilePNG("raidersm.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
		if(!enemy[i].img){
			printf("Enemy image failed to load...");
		}
		enemy[i].isalive = 1;
		enemy[i].pctr = 0;
		
	}
	
}

void loadEnemyChain(){
	int i;	
	for(i = 0; i < MAX_NUM_ENEMY_BULLETS; i++){
		enemychain[i].x = 0;
		enemychain[i].y = 0;
		enemychain[i].imgX = 8;
		enemychain[i].imgY = 6;
		enemychain[i].img  = oslLoadImageFilePNG("enemychain.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
		if(!enemychain[i].img){
			printf("enemychain image failed to load...");
		}
		enemychain[i].isalive = 0;
		enemychain[i].pctr = 0;
	}
}


void loadEnemyBattlestar(){
	battlestar.x = 10050;
	battlestar.y = (272/2) + 17;
	battlestar.imgX = 220;
	battlestar.imgY = 76;
	battlestar.health = 1000;
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

void loadStarfield(){
	starfield.x = 0;
	starfield.y = 0;
	starfield.imgX = 500;
	starfield.imgY = 300;
	starfield.img = oslLoadImageFilePNG("starfield_one.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	if(!starfield.img){
		printf("Starfield image failed to load...");
	}
	starfield.isalive = 1;
}

void loadStatusBar(){
	status_bar.x = -60;
	status_bar.y = 224;
	status_bar.imgX = 160;
	status_bar.imgY = 90;
	status_bar.img = oslLoadImageFilePNG("status_bar_new.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	if(!status_bar.img){
		printf("status_bar image load faild");
	}
	status_bar.isalive = 1;
}

void loadHsBar(){
	hs_bar.x = 0;
	hs_bar.y = 0;
	hs_bar.imgX = 480;
	hs_bar.imgY = 10;
	hs_bar.img2 = oslLoadImageFilePNG("hs_bar_clear.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	hs_bar.img = oslLoadImageFilePNG("hs_bar.png", OSL_IN_RAM | OSL_SWIZZLED, OSL_PF_8888);
	if(!hs_bar.img){
		printf("hs_bar image failed to load...");
	}
	hs_bar.isalive = 1;
}