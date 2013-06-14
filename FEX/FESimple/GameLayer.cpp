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
void GameLayer::added_to_game( GameBase* game )
{
    game->scene()->ccscene()->addChild( m_layer );
}

void GameLayer::removed_from_game( GameBase* game )
{
    game->scene()->ccscene()->removeChild( m_layer );
}

FE_NS_END