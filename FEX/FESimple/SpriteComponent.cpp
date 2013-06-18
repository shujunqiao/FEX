//
//  Sprite.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "FEUtility.h"
#include "FE.h"
#include "GameBase.h"

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
    //create physics body
    auto phy = ResourceManager::instance()->physic_descs.item(desc->physic_desc);
    b2BodyDef bodydef = phy->body_def;
    bodydef.position = point_to_b2Vec2( location );
    b2Body* body = get_game()->get_phy_world()->CreateBody( &bodydef );
    for ( auto fixdef_temp : phy->fixture_defs )
    {
        b2FixtureDef fixdef = fixdef_temp;
        fixdef.userData = this;
        body->CreateFixture( &fixdef );
    }
    

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