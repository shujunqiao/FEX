//
//  World.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#include "GameWorld.h"
#include "GameLayer.h"
#include <Box2D.h>
#include "GameScene.h"
namespace FESimple
{
    GameWorld::GameWorld()
    :m_phy_world(new b2World(b2Vec2(0,0)))
    {
        m_root_scene = new GameScene();
        m_root_scene->init();
    }
    
    GameWorld::~GameWorld()
    {
        remove_all_game_objects();
        remove_all_layers();
        delete m_root_scene;
    }
    
    //object management
    void GameWorld::add_game_object( GameObjBase* obj, std::string into_layer )
    {
    }
    
    void GameWorld::remove_game_object( GameObjBase* obj )
    {
    }
    
    void GameWorld::remove_all_game_objects()
    {
        for( auto obj : m_game_objects )
        {

        }
        m_game_objects.clear();
    }
    
    //layers
    GameLayer* GameWorld::get_layer( std::string name )
    {
        for ( auto layer : m_game_layers )
        {
            if ( layer->get_name() == name )
                return layer;
        }
        return nullptr;
    }
    
    void GameWorld::add_layer( GameLayer* layer, std::string name )
    {
        if ( get_layer( name ) != nullptr )
        {
            m_game_layers.insert( m_game_layers.begin(), layer );
            m_root_scene->addChild( layer );
        }
        else
        {
            assert(0&&"layer with same name already exists");
        }
    }

    void GameWorld::remove_all_layers()
    {
        for ( auto layer : m_game_layers )
        {
            m_root_scene->removeChild( layer );
        }
        m_game_layers.clear();
    }
}