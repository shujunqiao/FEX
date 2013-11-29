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
:TouchEventHandler(),handler(handler),SpriteBase(params)
{
}

Button::~Button()
{
    logger("ui") <<"Button destroyed" << endl;
}

void Button::touchesBegan(CCSet* touches, CCEvent* pEvent)
{
    for ( auto t = touches->begin(); t != touches->end(); ++t )
    {
        CCTouch* pTouch = (CCTouch*)(*t);
        auto loc = pTouch->getLocation();
        
        cocos2d::CCRect rect;
        rect.size = component(0)->getContentSize();
        rect.origin = component(0)->getPosition() - component(0)->getAnchorPointInPoints();
        if ( rect.containsPoint(loc))
        {
            if (handler)
                handler(this);
            break;
        }
    }
}
FE_NS_END