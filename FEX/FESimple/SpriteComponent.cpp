//
//  Sprite.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#include "SpriteComponent.h"
#include "ResourceManager.h"
using namespace cocos2d;
FE_NS_BEGIN
SpriteComponent::SpriteComponent(  const CCPoint& location, const std::shared_ptr<sprite_component_desc> desc )
:CCSprite()
{
    CCSprite::init();

    for ( auto anim_name : desc->animation_names )
    {
        auto anim = ResourceManager::instance()->animations.item(anim_name);
        animations.push_back( sprite_animation(CCRepeatForever::create(CCAnimate::create(anim->ccanimation)), anim->name ) );
    }
    play_anim("default");
}


bool SpriteComponent::play_anim( const Name& anim_name )
{
    for ( auto a : animations )
    {
        if ( a.name == anim_name )
        {
            runAction( a.animation );
            return true;
        }
    }
    return false;
}

void SpriteComponent::draw()
{
    CCSprite::draw();
}

FE_NS_END