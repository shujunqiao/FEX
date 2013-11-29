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
#include "EventDispatcher.h"
FE_NS_BEGIN

class Button : public SpriteBase, public TouchEventHandler
{
public:
    Button( SpawnParams const &params, std::function<void(void*)> handler );
    ~Button();
    virtual void touchesBegan(CCSet* touches, CCEvent* pEvent);
    
protected:
    std::function<void(void*)> handler;
};

FE_NS_END

#endif /* defined(__FEX__File__) */
