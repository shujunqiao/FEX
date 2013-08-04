//
//  GameSAD.h
//  GameSADLib
//
//  Created by Fancyzero on 13-7-12.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#ifndef __GameSADLib__GameSAD__
#define __GameSADLib__GameSAD__
#include "FE.h"
#include "GameBase.h"
FE_NS_USING;

class GameSAD : public GameBase
{
public:
    GameSAD();

    bool init_shaders();
};


#endif /* defined(__GameSADLib__GameSAD__) */
