#include "FE.h"
#include "GameBase.h"
#include "GameScene.h"
#include "Box2D.h"
FE_NS_BEGIN

GameBase::GameBase()
:m_scene( new GameScene() )
,m_phy_world( new b2World(b2Vec2(0,0)) )
{
    
}
void GameBase::add_game_object( GameObjPtr obj )
{
    m_objects.push_back( obj );
    obj->added_to_game( this );
}

void GameBase::remove_game_object( GameObjPtr obj )
{
    m_objects.remove( obj );
    obj->removed_from_game( this );
}

FE_NS_END