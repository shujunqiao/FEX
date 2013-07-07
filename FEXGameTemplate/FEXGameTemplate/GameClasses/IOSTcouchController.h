//
//  IOSTcouchController.h
//  FEXGameTemplate
//
//  Created by Fancyzero on 13-6-28.
//
//

#ifndef __FEXGameTemplate__IOSTcouchController__
#define __FEXGameTemplate__IOSTcouchController__

#include "GameTheSoldiersCommon.h"
#include "ControllerBase.h"

FE_NS_USING
GTS_NS_BEGIN
class IOSTouchController : public ControllerBase, public cocos2d::CCTargetedTouchDelegate
{
public:
    IOSTouchController();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};
GTS_NS_END
#endif /* defined(__FEXGameTemplate__IOSTcouchController__) */
