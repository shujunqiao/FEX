//
//  IOSTcouchController.h
//  FEXGameTemplate
//
//  Created by Fancyzero on 13-6-28.
//
//

#ifndef __FEXGameTemplate__IOSTcouchController__
#define __FEXGameTemplate__IOSTcouchController__

#include "FE.h"
#include "ControllerBase.h"
using namespace FESimple;
class IOSTouchController : public ControllerBase, cocos2d::CCTargetedTouchDelegate
{
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);    
};

#endif /* defined(__FEXGameTemplate__IOSTcouchController__) */
