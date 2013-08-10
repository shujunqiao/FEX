//
//  GameSADCommon.cpp
//  GameSADLib
//
//  Created by Fancyzero on 13-8-4.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#include "GameSADCommon.h"
#include "FE.h"
#include "Hero.h"

void register_GameSAD_classes()
{
    FESimple::GameObjFactory::add_class_info( CLASS_INFO_OF(Hero) );
}

