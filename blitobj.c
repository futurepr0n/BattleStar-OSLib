// blitobj.c: Blitting a player
//
////////////////////////////////////////////////////////////////////////////
#include <oslib/oslib.h>
#include "blitobj.h"

void blitObj(obj object){
    oslDrawImageXY(object.img, object.x, object.y);

}