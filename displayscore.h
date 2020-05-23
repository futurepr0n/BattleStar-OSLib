// displayscore.h: headers for displayscore
//
// 
//
//////////////////////////////////////////////////////////////////////
#ifndef _DISPLAYSCORE_H_
#define _DISPLAYSCORE_H_

#include "loadobj.h"
#include <oslib/oslib.h>

#ifdef __cplusplus
extern "C" {
#endif

//private functions
    void printScore();
    int checkCollision(obj blt);
#ifdef __cplusplus
}
#endif
#endif
