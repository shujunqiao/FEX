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
USING_NS_CC;
FE_NS_BEGIN


class ControllerBase
{
    
};


class FunGameIOSController :public ControllerBase , CCTargetedTouchDelegate
{
public:
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void set_player( GameObjPtr p )
    {
        player = p;
    }
    GameObjPtr get_player()
    {
        return player;
    }
protected:
    GameObjPtr player;
};

FE_NS_END

#endif /* defined(__FEX__InputDevice__) */
