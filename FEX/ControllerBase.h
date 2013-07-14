//
//  ControllerBase.h
//  FEX
//
//  Created by Fancyzero on 13-6-26.
//
//

#ifndef __FEX__ControllerBase__
#define __FEX__ControllerBase__

#include "FE.h"

FE_NS_BEGIN


class ControllerBase :public cocos2d::CCObject
{
public:
    virtual void plug() = 0;
    virtual void unplug() = 0;
    virtual ~ControllerBase(){};
};


FE_NS_END

#endif /* defined(__FEX__InputDevice__) */
