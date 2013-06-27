#include "FE.h"
#include "GameBase.h"
#include "GameScene.h"
#include "Box2D/Box2D.h"
FE_NS_BEGIN



GameBase::GameBase()
:scene( new GameScene() )
,phy_world( new b2World(b2Vec2(0,0)) )
{
    
}

GameBase::~GameBase()
{
}

void GameBase::update(float delta_time)
{
    if ( phy_world )
    {
        phy_world->Step( delta_time, 4, 8);
    }
    
    for ( auto c : objects )
    {
        c->update( delta_time );
    }
}

void GameBase::clean()
{
    objects.clear();
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

GameObjPtr GameBase::get_obj( const Name& name )
{
    return find_obj_if([&](GameObjPtr i){return i->get_name() == name; } );
}

FE_NS_END