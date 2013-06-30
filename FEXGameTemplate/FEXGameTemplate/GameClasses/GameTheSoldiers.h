//
//  GameSoliders.h
//  FEXGameTemplate
//
//  Created by Fancyzero on 13-6-29.
//
//

#ifndef __FEXGameTemplate__GameSoliders__
#define __FEXGameTemplate__GameSoliders__
#include "FE.h"
#include "GameBase.h"
using namespace FESimple;

class GameTheSoldiers : public GameBase
{
    std::unique_ptr<GameTheSoldiers> instance();
};

#endif /* defined(__FEXGameTemplate__GameSoliders__) */
