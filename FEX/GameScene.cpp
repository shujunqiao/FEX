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

IMPLEMENT_CLASS_INFO(GameScene, {&GameObjBase::classinfo})

GameScene::GameScene()
{
    scene = new MyScene();
    scene->init();
    scene->autorelease();
    scene->scheduleUpdate();
}

GameScene::GameScene( const SpawnParams& param)
:GameScene()
{

}

GameScene::~GameScene()
{
    scene->release();
}

//layers
GameLayer* GameScene::get_layer( std::string name )
{
    for ( auto layer : layers )
    {
        if ( layer->get_name() == name )
            return layer;
        logger("test") << layer->get_name() << endl;
    }
    logger("warning") << "layer: \"" << name << "\" not found" << endl;
    return *layers.begin();//return first layer
}

void GameScene::add_layer( GameLayer* layer, const Name& name )
{
    layers.insert( layers.begin(), layer );
    
}

void GameScene::remove_layer( GameLayer* layer )
{
    layers.remove( layer );
}

void GameScene::remove_all_layers()
{
    layers.clear();
}

FE_NS_END