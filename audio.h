//audio.h
//
// 
//
//////////////////////////////////////////////////////////////////////
#ifndef _AUDIO_H_
#define _AUDIO_H_

#include <pspaudio.h>
#include <pspaudiolib.h>
#include <oslib/oslib.h>
#include <mikmod.h>
//#include "control.h"

#ifdef __cplusplus
extern "C" {
#endif

    

    void my_error_handler(void);
    void setupMikMod();
    void quitMikMod();
    void playBullet();
    


#ifdef __cplusplus
}
#endif
#endif