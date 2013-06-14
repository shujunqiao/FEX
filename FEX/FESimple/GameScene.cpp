//
//  GameScene.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#include "GameScene.h"
#include "GameLayer.h"
FE_NS_BEGIN
GameScene::GameScene()
{
    m_scene = new cocos2d::CCScene();
    m_scene->init();
}

GameScene::~GameScene()
{
    m_scene->release();
}

//layers
GameLayer* GameScene::get_layer( std::string name )
{
    for ( auto layer : m_layers )
    {
        if ( layer->name() == name )
            return layer;
    }
    return nullptr;
}

void GameScene::add_layer( GameLayer* layer, std::string name )
{
    if ( get_layer( name ) != nullptr )
    {
        m_layers.insert( m_layers.begin(), layer );
        //added_to_world( this );
    }
    else
    {
        assert(0&&"layer with same name already exists");
    }
}

void GameScene::remove_all_layers()
{
    m_layers.clear();
}


FE_NS_END