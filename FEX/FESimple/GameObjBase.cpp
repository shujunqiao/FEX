//
//  GameObjBase.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//
#include "FE.h"
#include "GameObjBase.h"
FE_NS_BEGIN
GameObjBase::GameObjBase()
{
}

GameObjBase::~GameObjBase()
{
    printf("%p destoryed", this );
}

FE_NS_END