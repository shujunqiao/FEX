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

SpriteBase::SpriteBase( const CCPoint& location, const std::shared_ptr<sprite_desc> desc )
{
    assert(desc);
    for( auto &it : desc->components )
    {
        add_component(
                      new SpriteComponent( it.offset + location,
                            ResourceManager::instance()->
                            sprite_components.item(it.component_name))
                      );
    }
}

SpriteBase::SpriteBase( const SpawnParams& params )
:SpriteBase( string_to_point(params.find("init_location")->second.c_str()),
            ResourceManager::instance()->sprite_descs.item( params.find("sprite_desc")->second) )
{
    
}

SpriteBase::SpriteBase( const CCPoint& location, const SpawnParams& params )
:SpriteBase( location,
            ResourceManager::instance()->sprite_descs.item( params.find("sprite_desc")->second) )
{
    
}

SpriteBase::~SpriteBase()
{
    removed_from_game( nullptr );
    remove_all_component();
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
        {
            logger("tmp") << comp->retainCount() << endl;
            comp->removeFromParent();
            comp->release();
        }
    }
}

//components management
void SpriteBase::remove_all_component()
{
    for (auto c: components )
    {
        c->set_owner(std::shared_ptr<SpriteBase>(nullptr));
    }
    components.clear();
}

void SpriteBase::add_component( SpriteComponent* comp )
{
    components.push_back( comp );
    //comp->set_owner( std::dynamic_pointer_cast<SpriteBase>(shared_from_this()) );
}

void SpriteBase::remove_component( SpriteComponent * comp )
{
    comp->set_owner(std::shared_ptr<SpriteBase>(nullptr));
    //components.erase(std::find(components.begin(), components.end(), comp));
}

SpriteComponent* SpriteBase::component( unsigned int index )
{
    if ( index < components.size() )
        return components[index];
    else
        return nullptr;
}

//std::vector< SpriteComponent* > SpriteBase::all_components()
//{
//    return components;
//}

void SpriteBase::begin_contact( b2Contact* contact )
{
}

void SpriteBase::end_contact( b2Contact* contact )
{
}


void SpriteBase::update( float delta_time )
{
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