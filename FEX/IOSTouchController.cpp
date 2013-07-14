 //
//  IOSTcouchController.cpp
//  FEXGameTemplate
//
//  Created by Fancyzero on 13-6-28.
//
//

#include "IOSTouchController.h"
#include "FEUtility.h"
#include "SpriteBase.h"
#include "GameBase.h"
#include <memory>
#include "cocos2d.h"
FE_NS_BEGIN

USING_NS_CC;

IOSTouchController::IOSTouchController()
:CCTargetedTouchDelegate(),ControllerBase()
{

}
IOSTouchController::~IOSTouchController()
{
    logger("IOSTouchController") <<"destroyed" << endl;
}
bool IOSTouchController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
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

void IOSTouchController::plug()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}
void IOSTouchController::unplug()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

FE_NS_END
