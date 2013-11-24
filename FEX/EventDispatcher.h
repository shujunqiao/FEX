//
//  EventDispatcher.h
//  FEX
//
//  Created by FancyZero on 13-11-20.
//
//

#ifndef __FEX__EventDispatcher__
#define __FEX__EventDispatcher__

#include "FE.h"
#include "cocos2d.h"

using namespace cocos2d;
FE_NS_USING;

class EventDispatcher
{
    
};

class EventHandler
{
public:
    enum Type
    {
        et_unknown,
        et_touch,
        et_mouse,
        et_keyboard,
    };
    
    virtual Type get_type()
    {
        return et_unknown;
    }
protected:
    int prority;
};

class TouchEventHandler:public EventHandler
{
public:
    EventHandler::Type get_type()
    {
        return EventHandler::Type::et_touch;
    }
    virtual void touchesBegan(CCSet* touches, CCEvent* pEvent){};
    virtual void touchesMoved(CCSet* touches, CCEvent* pEvent){};
    virtual void touchesEnded(CCSet* touches, CCEvent* pEvent){};
    virtual void touchesCancelled(CCSet* touches, CCEvent* pEvent){};
    
};

class IOSEventDispatcher :public EventDispatcher, public cocos2d::EGLTouchDelegate
{
public:
    virtual void touchesBegan(CCSet* touches, CCEvent* pEvent);
    virtual void touchesMoved(CCSet* touches, CCEvent* pEvent);
    virtual void touchesEnded(CCSet* touches, CCEvent* pEvent);
    virtual void touchesCancelled(CCSet* touches, CCEvent* pEvent);
protected:
    std::vector<std::shared_ptr<EventHandler>> handlers;
    
};

#endif /* defined(__FEX__EventDispatcher__) */
