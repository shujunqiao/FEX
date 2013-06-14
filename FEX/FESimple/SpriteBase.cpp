//
//  SpriteBase.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-9.
//
//
#include "FE.h"
#include "SpriteBase.h"
#include "GameScene.h"
#include "GameBase.h"
#include "GameLayer.h"
#include "SpriteComponent.h"
#include "cocos2d.h"
#include "ResourceManager.h"
FE_NS_BEGIN
SpriteBase::SpriteBase()
{
}

SpriteBase::SpriteBase( const sprite_desc& desc )
{
    //for( auto &it : desc.m_components )
       // m_components.push_back(
       // new SpriteComponent( it.m_offset,
         //   ResourceManager::get_sprite_component_desc(it.m_sprite_component_name))
      //  );
}

SpriteBase::~SpriteBase()
{
}

void SpriteBase::added_to_game( GameBase* game )
{
    for( auto comp : m_components )
    {
        if ( comp != nullptr )
            game->scene()->get_layer("")->cclayer()->addChild( comp );
    }
}

void SpriteBase::removed_from_game( GameBase* game )
{
    for( auto comp : m_components )
    {
        if ( comp != nullptr )
            comp->removeFromParent();
    }
}

//components management
void SpriteBase::add_component( SpriteComponent* comp )
{
    m_components.push_back( comp );
}

void SpriteBase::remove_component( SpriteComponent * comp )
{
    m_components.erase(std::find(m_components.begin(), m_components.end(), comp));
}

SpriteComponent* SpriteBase::get_component( unsigned int index )
{
    if ( index < m_components.size() )
        return m_components[index];
    else
        return nullptr;
}
FE_NS_END