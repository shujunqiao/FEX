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
#include "SpriteBase.h"

using namespace cocos2d;
FE_NS_BEGIN

//IMPLEMENT_CLASS_INFO(SpriteComponent,{})

SpriteComponent::SpriteComponent(  const CCPoint& location, const std::shared_ptr<sprite_component_desc> desc )
:CCSprite(),phy_body(nullptr)
{

    CCSprite::init();
    logger("sprite component") << this << " created retaincount:" << retainCount() <<  endl;
    for ( auto anim_name : desc->animation_names )
    {
        auto anim = ResourceManager::instance()->animations.item(anim_name);
        animations.push_back( sprite_animation(CCRepeatForever::create(CCAnimate::create(anim->ccanimation)), anim->name ) );
    }
    logger("sprite component") << this << " created retaincount:" << retainCount() <<  endl;
    play_anim("default");
    logger("sprite component") << this << " created retaincount:" << retainCount() <<  endl;    
    //create physics body
    auto phy = ResourceManager::instance()->physic_descs.item(desc->physic_desc_name);
    if ( phy != nullptr )
    {
        b2BodyDef bodydef = phy->body_def;
        bodydef.position = point_to_b2Vec2( location );
        phy_body = get_game()->get_phy_world()->CreateBody( &bodydef );
        for ( auto fixdef_temp : phy->fixture_defs )
        {
            b2FixtureDef fixdef = fixdef_temp;
            phy_body->CreateFixture( dynamic_cast<b2FixtureDef*>(&fixdef) );
        }
    }

    //scheduleUpdate();
}

SpriteComponent::~SpriteComponent()
{
    logger("sprite component") << this << "destroyed" << endl;
    if (phy_body)
        get_game()->get_phy_world()->DestroyBody(phy_body);
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

void SpriteComponent::update(float fDelta)
{
    //sync position and rotation with physics body
//    if ( phy_body )
//    {
//        CCSprite::setPosition(b2Vec2_to_point(phy_body->GetPosition()));
//        CCSprite::setRotation(rad_to_angle(phy_body->GetAngle()));
//    }
    CCSprite::update( fDelta );
}

void SpriteComponent::setPosition(const CCPoint& pos)
{
    if ( phy_body )
        phy_body->SetTransform( point_to_b2Vec2(pos), phy_body->GetAngle() );
    
    CCSprite::setPosition(pos);
}

const CCPoint& SpriteComponent::getPosition()
{
    if ( phy_body )
        return m_obPosition = b2Vec2_to_point( phy_body->GetPosition() );
    else
        return CCSprite::getPosition();
}

// this method will only get called if the sprite is batched.
// return YES if the physic's values (angles, position ) changed.
// If you return NO, then nodeToParentTransform won't be called.
bool SpriteComponent::isDirty()
{
    return true;
}


// returns the transform matrix according the Box2D Body values
CCAffineTransform SpriteComponent::nodeToParentTransform()
{
    b2Vec2 pos  = phy_body->GetPosition();
	
	float x = pos.x * ptm_ratio();
	float y = pos.y * ptm_ratio();
	
	if (m_bIgnoreAnchorPointForPosition)
    {
		x += m_obAnchorPointInPoints.x;
		y += m_obAnchorPointInPoints.y;
	}
	
	// Make matrix
	float radians = phy_body->GetAngle();
	float c = cosf(radians);
	float s = sinf(radians);
	
	// Although scale is not used by physics engines, it is calculated just in case
	// the sprite is animated (scaled up/down) using actions.
	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990
	if (!m_obAnchorPointInPoints.equals(CCPointZero))
    {
		x += ((c * -m_obAnchorPointInPoints.x * m_fScaleX) + (-s * -m_obAnchorPointInPoints.y * m_fScaleY));
		y += ((s * -m_obAnchorPointInPoints.x * m_fScaleX) + (c * -m_obAnchorPointInPoints.y * m_fScaleY));
	}
    
	// Rot, Translate Matrix
	m_sTransform = CCAffineTransformMake( c * m_fScaleX,	s * m_fScaleX,
									     -s * m_fScaleY,	c * m_fScaleY,
									     x,	y );
	
	return m_sTransform;
}

// physics callbacks
void SpriteComponent::begin_contact( class b2Contact* contact )
{
    owner.lock()->begin_contact(contact);
}

void SpriteComponent::end_contact( class b2Contact* contact )
{
    owner.lock()->end_contact(contact);
}

// physics methods
void SpriteComponent::set_linear_velocity( const CCPoint& v )
{
    if ( phy_body )
        phy_body->SetLinearVelocity( point_to_b2Vec2(v) );
}

void SpriteComponent::set_linear_damping( float damping )
{
    if ( phy_body )
        phy_body->SetLinearDamping( damping );
}

void SpriteComponent::apply_force( const CCPoint& v, const CCPoint& location )
{
    if ( phy_body )
        phy_body->ApplyForce( point_to_b2Vec2(v), point_to_b2Vec2(v) );
}

void SpriteComponent::apply_force( const CCPoint& v )
{
    if ( phy_body )
        phy_body->ApplyForceToCenter( point_to_b2Vec2(v) );
}

void SpriteComponent::apply_torque( float q )
{
    if ( phy_body )
        phy_body->ApplyTorque( q );
}

void SpriteComponent::set_angular_damping( float damping )
{
    if ( phy_body )
        phy_body->SetAngularDamping( damping );
}
void SpriteComponent::apply_linear_impulse( const CCPoint& v )
{
    if ( phy_body )
        phy_body->ApplyLinearImpulse(point_to_b2Vec2(v), phy_body->GetPosition());
}

void SpriteComponent::apply_angular_impulse( float i )
{
    if ( phy_body )
        phy_body->ApplyAngularImpulse( i );
}

void SpriteComponent::wakeup()
{
    if ( phy_body )
        phy_body->SetAwake(true);
}

FE_NS_END