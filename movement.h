//movement.h
#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include "loadobj.h"
#include "blitobj.h"
#include "displayscore.h"
#include "audio.h"

#ifdef __cplusplus
extern "C" {
#endif


//private functions
void shootChain();
void scrollBackground();
void scrollStarfield();
void moveStuff();
//void shootEnemyChain(int z);

#ifdef __cplusplus
}
#endif
#endif