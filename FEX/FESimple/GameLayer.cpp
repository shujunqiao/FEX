//
//  GameLayer.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#include "GameLayer.h"
#include "GameBase.h"
#include "GameScene.h"

FE_NS_BEGIN

GameLayer::GameLayer()
:layer(cocos2d::CCLayer::create())
{
    layer->retain();
}

GameLayer::~GameLayer()
{
    if ( layer )
        layer->release();
}

void GameLayer::added_to_game( GameBase* game, const Name& to_layer )
{
    game->get_scene()->add_layer( this, "" );
    game->get_scene()->ccscene()->addChild( layer );
}

void GameLayer::removed_from_game( GameBase* game )
{
    game->get_scene()->ccscene()->removeChild( layer );
    game->get_scene()->remove_layer( this );
}

FE_NS_END