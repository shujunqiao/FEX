//
//  EventDispatcher.cpp
//  FEX
//
//  Created by FancyZero on 13-11-20.
//
//

#include "EventDispatcher.h"
void IOSEventDispatcher::touchesBegan(CCSet* touches, CCEvent* pEvent)
{
    for (auto i : handlers )
    {
        if ( i->get_type() == 0 )
        {
            std::shared_ptr<TouchEventHandler> te = std::static_pointer_cast<TouchEventHandler>(i);
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
