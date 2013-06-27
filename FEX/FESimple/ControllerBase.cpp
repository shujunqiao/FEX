//
//  ControllerBase.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-26.
//
//

#include "ControllerBase.h"

FE_NS_BEGIN
bool FunGameIOSController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    GameObjPtr player = get_game()->find_obj_if([](GameObjPtr i){return ( i->get_name() == "player" ); } );
    return true;
}

FE_NS_END