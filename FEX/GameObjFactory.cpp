//
//  GameObjFactory.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-23.
//
//
#include <functional>
#include "GameObjFactory.h"
#include "SpriteBase.h"
#include "GameScene.h"
#include "GameLayer.h"

FE_NS_BEGIN


std::vector<ClassInfo*> fe_classes=
{
    CLASS_INFO_OF(GameObjBase),
    CLASS_INFO_OF(SpriteBase),
    CLASS_INFO_OF(GameScene),
    CLASS_INFO_OF(GameLayer)
};

GameObjPtr GameObjFactory::construct_obj( const Name& classname, const SpawnParams& params )
{
    auto it = std::find_if(fe_classes.begin(), fe_classes.end(), [&](ClassInfo* i){if (i->name == classname) return true;else return false; });
    if ( it != fe_classes.end() )
        return GameObjPtr((GameObjBase*)(*it)->constructor(params));
    return GameObjPtr(nullptr);
}

FE_NS_END