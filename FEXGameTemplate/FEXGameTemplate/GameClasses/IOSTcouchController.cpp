 //
//  IOSTcouchController.cpp
//  FEXGameTemplate
//
//  Created by Fancyzero on 13-6-28.
//
//

#include "IOSTcouchController.h"
#include "FEUtility.h"
#include "GameBase.h"
bool IOSTouchController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    auto pt = pTouch->getLocation();
    get_game();
    return true;
}
void IOSTouchController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void IOSTouchController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void IOSTouchController::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

