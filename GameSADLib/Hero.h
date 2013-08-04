//
//  Hero.h
//  GameSADLib
//
//  Created by Fancyzero on 13-7-12.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#ifndef __GameSADLib__Hero__
#define __GameSADLib__Hero__

#include "FE.h"
#include "SpriteBase.h"
FE_NS_USING;
class Hero : public SpriteBase
{
public:
    DECLARE_CLASS_INFO(Hero)
    Hero( const SpawnParams& params );
    void update( float delta_time );
};

#endif /* defined(__GameSADLib__Hero__) */
