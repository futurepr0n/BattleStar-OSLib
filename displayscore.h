// displayscore.h: headers for displayscore
//
// 
//
//////////////////////////////////////////////////////////////////////
#ifndef _DISPLAYSCORE_H_
#define _DISPLAYSCORE_H_

#include <oslib/oslib.h>

#include "loadobj.h"
#include "init.h"


#ifdef __cplusplus
extern "C" {
#endif

enum colors {
    RED =	0xFF0000FF,
    GREEN =	0xFF00FF00,
    BLUE =	0xFFFF0000,
    WHITE =	0xFFFFFFFF,
    LITEGRAY = 0xFFBFBFBF,
    GRAY =  0xFF7F7F7F,
    DARKGRAY = 0xFF3F3F3F,
    BLACK = 0xFF000000
};

OSL_FONT *pgfFont;
OSL_FONT *pgfFont2;
//&pgfFont = oslLoadFontFile("ltn8.pgf");



//private functions
    void printScore();
    int checkCollision(obj blt);
    void fontInit();
    void splashScreenFontSetup();
    void gameScreenFontSetup();
    void drawSplashText();
#ifdef __cplusplus
}
#endif
#endif
