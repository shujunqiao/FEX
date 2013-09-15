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
    Name get_name()
    {
        return name;
    }
    void set_name(const Name& name_)
    {
        name = name_;
    }
    virtual void plug() = 0;
    virtual void unplug() = 0;
    virtual ~ControllerBase(){};
protected:
    Name name;
};


FE_NS_END

#endif /* defined(__FEX__InputDevice__) */
