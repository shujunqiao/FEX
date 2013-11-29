//
//  EventDispatcher.cpp
//  FEX
//
//  Created by FancyZero on 13-11-20.
//
//

#include "EventDispatcher.h"
FE_NS_BEGIN
void IOSEventDispatcher::touchesBegan(CCSet* touches, CCEvent* pEvent)
{
    for (auto i : handlers )
    {
        if ( i->is_dead() )
            continue;
        EventHandler* eh = dynamic_cast<EventHandler*>(i.get());
        if ( eh && eh->get_type() & EventHandler::et_touch )
        {
            TouchEventHandler* te = static_cast<TouchEventHandler*>(eh);
            if ( te )
            {
                te->touchesBegan(touches, pEvent);
            }
        }
    }
}

void IOSEventDispatcher::touchesMoved(CCSet* touches, CCEvent* pEvent)
{
    
}

void IOSEventDispatcher::touchesEnded(CCSet* touches, CCEvent* pEvent)
{
    
}

void IOSEventDispatcher::touchesCancelled(CCSet* touches, CCEvent* pEvent)
{
    
}


void EventDispatcher::remove_handler( std::shared_ptr<GameObjBase> h )
{
    auto i = std::find( handlers.begin(), handlers.end(), h );
    handlers.erase(i);
}

void EventDispatcher::add_handler( std::shared_ptr<GameObjBase> h )
{
    auto i = std::find( handlers.begin(), handlers.end(), h );
    if ( i != handlers.end() )
        return;
    handlers.push_back(h);
    std::sort(handlers.begin(), handlers.end(), [&](std::shared_ptr<GameObjBase> a,std::shared_ptr<GameObjBase> b){
        if (dynamic_cast<EventHandler*>(a.get()) && dynamic_cast<EventHandler*>(b.get()))
        {
            return dynamic_cast<EventHandler*>(a.get())->get_priority() < dynamic_cast<EventHandler*>(b.get())->get_priority();
        }
        else
        {
            assert(false);
            return false;
        }
    }
              );
}

void EventDispatcher::remove_dead_handlers()
{
    handlers.erase(std::remove_if(handlers.begin(), handlers.end(), [&](std::shared_ptr<GameObjBase> h){return h->is_dead();}),handlers.end());
}
FE_NS_END