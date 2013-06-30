//
//  GameObjFactory.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-23.
//
//

#include "GameObjFactory.h"
#include "SpriteBase.h"

FE_NS_BEGIN
#define TRY_CONSTRUCT_CLASS( class ) if ( classname == #class ) return GameObjPtr( new class( params ) );

GameObjPtr GameObjFactory::construct_obj( const Name& classname, const SpawnParams& params )
{
    TRY_CONSTRUCT_CLASS( GameObjBase );
    TRY_CONSTRUCT_CLASS( SpriteBase );
    return GameObjPtr(nullptr);
}

FE_NS_END