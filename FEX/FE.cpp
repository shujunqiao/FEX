//
//  FECommon.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-8.
//
//

#include "FE.h"
FE_NS_BEGIN
GameInfo    g_game_info;

GameInfo* get_game_info()
{
    return &g_game_info;
}

FE_NS_END