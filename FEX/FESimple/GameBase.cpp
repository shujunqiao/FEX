#include "FE.h"
#include "GameBase.h"
#include "GameScene.h"
#include "Box2D.h"
FE_NS_BEGIN

GameBase::GameBase()
:scene( new GameScene() )
,phy_world( new b2World(b2Vec2(0,0)) )
{
    
}
void GameBase::add_game_object( GameObjPtr obj, const Name& to_layer)
{
    objects.push_back( obj );
    obj->added_to_game( this, to_layer );
}

void GameBase::remove_game_object( GameObjPtr obj )
{
    objects.remove( obj );
    obj->removed_from_game( this );
}

FE_NS_END