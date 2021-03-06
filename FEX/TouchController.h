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


FE_NS_BEGIN

class TouchController : public ControllerBase, public cocos2d::CCTargetedTouchDelegate
{
public:
    TouchController();
    virtual ~TouchController();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void plug();
    virtual void unplug();
    
};
FE_NS_END
#endif /* defined(__FEXGameTemplate__IOSTcouchController__) */
