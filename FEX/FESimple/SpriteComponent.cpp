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
SpriteComponent::SpriteComponent(  const CCPoint& location, const sprite_component_desc& desc )
:CCSprite()
{
    CCSprite::init();
//    const sprite_component_desc& sc_desc = ResourceManager::get_sprite_component_desc(desc.m_sprite_component_name);
    for ( auto anim_def : desc.m_animation_names )
    {
       // m_animations.push_back( sprite_animation(CCRepeatForever::create(CCAnimate::create(anim_def.m_animation)), anim_def.m_name));
    }
}
FE_NS_END