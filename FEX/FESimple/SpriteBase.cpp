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

SpriteBase::SpriteBase( const std::shared_ptr<sprite_desc> desc )
{
    for( auto &it : desc->components )
    {
       components.push_back(
        new SpriteComponent( it.offset,
                            ResourceManager::instance()->sprite_components.item(it.component_name)));
    }
}

SpriteBase::~SpriteBase()
{
}

void SpriteBase::added_to_game( GameBase* game, const Name& to_layer )
{
    for( auto comp : components )
    {
        if ( comp != nullptr )
            game->get_scene()->get_layer(to_layer)->cclayer()->addChild( comp );
    }
}

void SpriteBase::removed_from_game( GameBase* game )
{
    for( auto comp : components )
    {
        if ( comp != nullptr )
            comp->removeFromParent();
    }
}

//components management
void SpriteBase::add_component( SpriteComponent* comp )
{
    components.push_back( comp );
}

void SpriteBase::remove_component( SpriteComponent * comp )
{
    components.erase(std::find(components.begin(), components.end(), comp));
}

SpriteComponent* SpriteBase::get_component( unsigned int index )
{
    if ( index < components.size() )
        return components[index];
    else
        return nullptr;
}



//position , rotation, ect..
void SpriteBase::set_position( CCPoint pos )
{
    for( auto c : components )
    {
        c->setPosition( pos );
    }
}

void SpriteBase::set_rotation( float angle )
{
    for( auto c : components )
    {
        c->setRotation( angle );
    }
}

FE_NS_END