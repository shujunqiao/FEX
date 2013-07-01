//
//  GameSoliders.h
//  FEXGameTemplate
//
//  Created by Fancyzero on 13-6-29.
//
//

#ifndef __FEXGameTemplate__GameSoliders__
#define __FEXGameTemplate__GameSoliders__
#include "GameTheSoldiersCommon.h"
#include "GameBase.h"

FE_NS_USING

GTS_NS_BEGIN

class GameTheSoldiers : public GameBase
{
public:
    GameTheSoldiers();
    
protected:
    std::unique_ptr<GameBase> level;
};
GTS_NS_END
#endif /* defined(__FEXGameTemplate__GameSoliders__) */
