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
FE_NS_BEGIN
class EventDispatcher :public cocos2d::EGLTouchDelegate
{
public:
    void remove_handler( std::shared_ptr<GameObjBase> h );
    void add_handler( std::shared_ptr<GameObjBase> h );
    void remove_dead_handlers();
protected:
    std::vector<std::shared_ptr<GameObjBase>> handlers;
    
};

class EventHandler
{
public:
    enum Type
    {
        et_unknown = 1,
        et_touch = 2,
        et_mouse = 4,
        et_keyboard = 8,
    };
    
    unsigned int get_type()
    {
        return type;
    }
    void add_type( Type t)
    {
        type |= t;
    }
    EventHandler()
    :type(0),priority(0)
    {
        
    }
    int get_priority()
    {
        return priority;
    }
protected:
    unsigned int type;
    int priority;
};

class TouchEventHandler:public EventHandler
{
public:
    TouchEventHandler()
    :EventHandler()
    {
        add_type(et_touch);
    }
    virtual void touchesBegan(CCSet* touches, CCEvent* pEvent){};
    virtual void touchesMoved(CCSet* touches, CCEvent* pEvent){};
    virtual void touchesEnded(CCSet* touches, CCEvent* pEvent){};
    virtual void touchesCancelled(CCSet* touches, CCEvent* pEvent){};
    
};

class IOSEventDispatcher :public EventDispatcher
{
public:
    virtual void touchesBegan(CCSet* touches, CCEvent* pEvent);
    virtual void touchesMoved(CCSet* touches, CCEvent* pEvent);
    virtual void touchesEnded(CCSet* touches, CCEvent* pEvent);
    virtual void touchesCancelled(CCSet* touches, CCEvent* pEvent);
    
};
FE_NS_END
#endif /* defined(__FEX__EventDispatcher__) */
