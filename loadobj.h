// loadobj.h: headers for loadobj
//
// 
//
//////////////////////////////////////////////////////////////////////
#ifndef _LOADOBJ_H_
#define _LOADOBJ_H_

#include <oslib/oslib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_NUM_BULLETS 100
#define MAX_NUM_ENEMIES 100

//int bullets = 0;
// int points = 0;
// int hScore = 200;
// char playerScore[5];
// char highScore[5];


typedef struct{
	int x;
	int y;
	int imgX;
	int imgY;
	OSL_IMAGE *img;
	OSL_IMAGE *img2;
	int isalive;	
	int pctr;
}obj;

obj background;
obj starfield;
obj player;
obj sprite;
obj enemy[MAX_NUM_ENEMIES];
obj chain[MAX_NUM_BULLETS];
obj battlestar;
obj hs_bar;
obj status_bar;


//  Function prototypes for public functions
//    

//private functions
    void loadPlayer();
    void loadEnemies();
    void loadChain();
    void loadCharacterData();
	void loadBackground();
	void loadEnemyBattlestar();
	void loadStarfield();
	void loadStatusBar();
	void loadHsBar();

#ifdef __cplusplus
}
#endif
#endif