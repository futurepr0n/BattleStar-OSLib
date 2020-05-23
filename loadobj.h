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
	int isalive;	
	int pctr;
}obj;

obj background;
obj player;
obj sprite;
obj enemy[MAX_NUM_ENEMIES];
obj chain[MAX_NUM_BULLETS];


//  Function prototypes for public functions
//    

//private functions
    void loadPlayer();
    void loadEnemies();
    void loadChain();
    void loadCharacterData();
	void loadBackground();

#ifdef __cplusplus
}
#endif
#endif