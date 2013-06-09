//
//  GameLayer.h
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#ifndef __FEX__GameLayer__
#define __FEX__GameLayer__

#include "cocos2d.h"

namespace FESimple
{
    class GameLayer :public cocos2d::CCLayer
    {
    public:
        const std::string& get_name()
        {
            return m_name;
        }
    protected:
        std::string m_name;
    };
}

#endif /* defined(__FEX__GameLayer__) */
