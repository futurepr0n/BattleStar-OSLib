#include <oslib/oslib.h>
//#include "loadobj.h"
#include "control.h"
//#include "audio.h"

void control()
{
     oslReadKeys();
        if (osl_keys->held.circle){shootChain();playBullet();}   
        if((osl_keys->held.right)&&player.x <= 150){player.x = player.x + 1;}      
        if((osl_keys->held.left)&&player.x > 60){player.x = player.x - 1;} 
        if((osl_keys->held.up)&&player.y > -10){player.y = player.y - 5;}  
        if((osl_keys->held.down)&&player.y < 262){player.y = player.y + 5;}
}