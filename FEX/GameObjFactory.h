//
//  GameObjFactory.h
//  FEX
//
//  Created by Fancyzero on 13-6-23.
//
//

#ifndef __FEX__GameObjFactory__
#define __FEX__GameObjFactory__

#include "FE.h"

FE_NS_BEGIN



class GameObjFactory
{
public:
    static GameObjPtr construct_obj( const Name& classname, const SpawnParams& params );
};
FE_NS_END
#endif /* defined(__FEX__GameObjFactory__) */
