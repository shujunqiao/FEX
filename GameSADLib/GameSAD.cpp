//
//  GameSAD.cpp
//  GameSADLib
//
//  Created by Fancyzero on 13-7-12.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#include "GameSAD.h"
#include "GameSADLevel.h"
GameSAD::GameSAD()
{
    level.reset(new GameSADLevel());
}