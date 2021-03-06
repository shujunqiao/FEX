#include "FE.h"
#include "GameBase.h"
#include "GameScene.h"
#include "Box2D/Box2D.h"
#include "GameLayer.h"
#include "cocos2d.h"
#include "LevelBase.h"
#include "EventDispatcher.h"
FE_NS_BEGIN



GameBase::GameBase()
:scene( new GameScene() )
,phy_world( new b2World(b2Vec2(0,0)) )
,event_dispatcher(new IOSEventDispatcher())
{
    logger("debug")<<"GameBase Created from c++" << endl;
    GameObjPtr layer(new GameLayer());
    layer->set_name( "root" );
    add_object( layer, "");
    cocos2d::CCDirector::sharedDirector()->runWithScene(scene->ccscene());
    CCEGLView::sharedOpenGLView()->setTouchDelegate( get_event_dispatcher() );
}

GameBase::~GameBase()
{
    logger("GameBase") << "GameBase Destroyed" << endl;
    
    //remove scene from director
    cocos2d::CCDirector::sharedDirector()->popScene();

    if (get_game() == this )
        set_game(nullptr);
    
}

void GameBase::update(float delta_time)
{
    set_current_time(current_time()+delta_time);
    if ( phy_world )
    {
        phy_world->Step( delta_time, 4, 8);
    }
    if ( level )
        level->update(delta_time);
    for ( auto c : objects )
    {
        c->update( delta_time );
    }
    //remove all dead sprites
    objects.erase(std::remove_if(objects.begin(), objects.end(), [&](std::shared_ptr<GameObjBase> obj){return obj->is_dead();}), objects.end());
    get_event_dispatcher()->remove_dead_handlers();
}

void GameBase::clear()
{
    for ( auto i: objects )
    {
        logger("memory") << "object: " << i << " refcount: " << i.use_count() << endl;
        i->set_dead(true);
    }
}

void GameBase::add_object( GameObjPtr obj, const Name& to_layer)
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

void GameBase::set_level( LevelBase* lvl )
{
    level.reset( lvl );
}


FE_NS_END