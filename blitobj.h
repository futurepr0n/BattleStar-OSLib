// blitobj.h: headers for blitobj
//
// 
//
//////////////////////////////////////////////////////////////////////
#ifndef _BLITOBJ_H_
#define _BLITOBJ_H_

#include "loadobj.h"
#include <oslib/oslib.h>

#ifdef __cplusplus
extern "C" {
#endif

//private functions
    void blitObj(obj object);
    void blitBg(obj object);
    void blitEnemies();
    void shootEnemyChain(int z);
#ifdef __cplusplus
}
#endif
#endif
