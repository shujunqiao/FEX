//
//  File.cpp
//  FEX
//
//  Created by FancyZero on 13-11-16.
//
//

#include "Button.h"
FE_NS_BEGIN
Button::Button( SpawnParams const &params, std::function<void(void*)> handler)
:handler(handler),SpriteBase(params)
{
    //retain();retain();//can be deleted only by shared_ptr, work around for "double refcount management"
    
    cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, false);
    
}

Button::~Button()
{
    cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    logger("ui") <<"Button destroyed" << endl;
}

bool Button::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    auto loc = pTouch->getLocation();
    
    cocos2d::CCRect rect;
    rect.size = component(0)->getContentSize();
    rect.origin = component(0)->getPosition() - component(0)->getAnchorPointInPoints();
    if ( rect.containsPoint(loc))
    {
        if (handler)
            handler(this);
        return true;
    }
    return false;
}
FE_NS_END