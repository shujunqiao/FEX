//
//  File.h
//  FEX
//
//  Created by FancyZero on 13-11-16.
//
//

#ifndef __FEX__Button__
#define __FEX__Button__

#include "FE.h"
#include "SpriteBase.h"
#include <functional>
FE_NS_BEGIN

class Button : public SpriteBase, public cocos2d::CCTargetedTouchDelegate//, public cocos2d::CCObject
{
public:
    Button( SpawnParams const &params, std::function<void(void*)> handler );
    ~Button();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
protected:
    std::function<void(void*)> handler;
};

FE_NS_END

#endif /* defined(__FEX__File__) */
