//
//  DesktopInput.h
//  GameSADLib
//
//  Created by Fancyzero on 13-8-4.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#ifndef __GameSADLib__DesktopInput__
#define __GameSADLib__DesktopInput__

#include "cocos2d.h"
#include "ControllerBase.h"

FE_NS_USING;

class EditorController : public ControllerBase, public cocos2d::CCTargetedTouchDelegate
{
public:
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void plug();
    virtual void unplug();    
};

#endif /* defined(__GameSADLib__DesktopInput__) */
