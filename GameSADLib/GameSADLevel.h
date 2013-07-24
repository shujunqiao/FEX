//
//  GameSADLevel.h
//  GameSADLib
//
//  Created by Fancyzero on 13-7-23.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#ifndef __GameSADLib__GameSADLevel__
#define __GameSADLib__GameSADLevel__

#include "FE.h"
#include "LevelBase.h"

FE_NS_USING;

class GameSADLevel : public LevelBase
{
    virtual bool load( const std::string& filename );
    virtual bool save( const std::string& filename );
};


#endif /* defined(__GameSADLib__GameSADLevel__) */
