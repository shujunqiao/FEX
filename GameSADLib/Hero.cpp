//
//  Hero.cpp
//  GameSADLib
//
//  Created by Fancyzero on 13-7-12.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#include "Hero.h"

IMPLEMENT_CLASS_INFO(Hero, {&SpriteBase::classinfo});

Hero::Hero( const SpawnParams& params )
:SpriteBase( params )
{
}

void Hero::update( float delta_time )
{
    SpriteBase::update(delta_time);
}