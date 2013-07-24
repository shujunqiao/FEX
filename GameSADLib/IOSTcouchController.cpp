 //
//  IOSTcouchController.cpp
//  FEXGameTemplate
//
//  Created by Fancyzero on 13-6-28.
//
//

#include "IOSTcouchController.h"
#include "FEUtility.h"
#include "SpriteBase.h"
#include "GameBase.h"

#include <memory>
#include "cocos2d.h"

using namespace cocos2d;
FE_NS_USING


IOSTouchController::IOSTouchController()
:CCTargetedTouchDelegate(),ControllerBase()
{

}

bool IOSTouchController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    auto pt = pTouch->getLocation();

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
