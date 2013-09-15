 //
//  IOSTcouchController.cpp
//  FEXGameTemplate
//
//  Created by Fancyzero on 13-6-28.
//
//

#include "TouchController.h"
#include "FEUtility.h"
#include "SpriteBase.h"
#include "GameBase.h"
#include <memory>
#include "cocos2d.h"
FE_NS_BEGIN

USING_NS_CC;

TouchController::TouchController()
:CCTargetedTouchDelegate(),ControllerBase()
{

}
TouchController::~TouchController()
{
    logger("TouchController") <<"destroyed" << endl;
    unplug();
}
bool TouchController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}
void TouchController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void TouchController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void TouchController::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void TouchController::plug()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}
void TouchController::unplug()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}



FE_NS_END
