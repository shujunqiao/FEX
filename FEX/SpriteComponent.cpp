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
    assert(desc);
    CCSprite::init();
    init_shader();
    for ( auto anim_name : desc->animation_names )
    {
        auto anim = ResourceManager::instance()->animations.item(anim_name);
        animations.push_back( sprite_animation(CCRepeatForever::create(CCAnimate::create(anim->ccanimation)), anim->name ) );
    }
    play_anim("default");
    //create physics body
    phy_desc = ResourceManager::instance()->physic_descs.item(desc->physic_desc_name);
    setPosition(location);
    if ( phy_desc )
        init_physics(phy_desc);
    //logger("sprite component") << this << " created retaincount:" << retainCount() <<  endl;
    //scheduleUpdate();
}

SpriteComponent::~SpriteComponent()
{
    //logger("sprite component") << this << "destroyed" << endl;
    if (phy_body)
        get_game()->get_phy_world()->DestroyBody(phy_body);
}

bool SpriteComponent::init_shader()
{
    setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey("base"));
    return true;
}

void SpriteComponent::init_physics( const std::shared_ptr<physic_desc> phy )
{
    if ( phy == nullptr )
        return;
    auto location = point_to_b2Vec2( this->getPosition() );
    if ( phy_body != nullptr )
        get_game()->get_phy_world()->DestroyBody(phy_body);
    phy_body = nullptr;
    b2BodyDef bodydef = phy->body_def;
    bodydef.position = location;
    phy_body = get_game()->get_phy_world()->CreateBody( &bodydef );
    for ( auto fixdef_temp : phy->fixture_defs )
    {
        b2FixtureDef fixdef = fixdef_temp;
        b2CircleShape cs;
        b2PolygonShape ps;
        switch (fixdef.shape->GetType())
        {
            case b2Shape::e_circle:
            {
                cs = *(b2CircleShape*)fixdef.shape;
                fixdef.shape = &cs;
                cs.m_radius *= getScaleX();
            }
            break;
                
            case b2Shape::e_polygon:
            {
                ps = *(b2PolygonShape*)fixdef.shape;
                fixdef.shape = &ps;
                for ( int i =0; i < ps.m_vertexCount; i++ )
                {
                    ps.m_vertices[i].x *= getScaleX();
                    ps.m_vertices[i].y *= getScaleY();
                }
            }
                break;
            default:
                break;
        }
        phy_body->CreateFixture( dynamic_cast<b2FixtureDef*>(&fixdef) )->SetUserData(this);
    }
    
}

bool SpriteComponent::play_anim( const Name& anim_name )
{
    for ( auto a : animations )
    {
        if ( a.name == anim_name )
        {
            this->stopAllActions();//todo: only stop last action added by this method
            runAction( a.animation );
            return true;
        }
    }
    return false;
}

void SpriteComponent::draw()
{
    CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
    
    CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");
    
    CC_NODE_DRAW_SETUP();
    
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
    
    if (m_pobTexture != NULL)
    {
        ccGLBindTexture2D( m_pobTexture->getName() );
    }
    else
    {
        ccGLBindTexture2D(0);
    }
    
    //
    // Attributes
    //
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
    
#define kQuadSize sizeof(m_sQuad.bl)
    long offset = (long)&m_sQuad;
    
    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( ccV3F_C4B_T2F, mask_colors);
    glVertexAttribPointer(kCCVertexAttrib_MaskColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CHECK_GL_ERROR_DEBUG();
    
#if CC_SPRITE_DEBUG_DRAW == 1
    // draw bounding box
    CCPoint vertices[4]={
        ccp(m_sQuad.tl.vertices.x,m_sQuad.tl.vertices.y),
        ccp(m_sQuad.bl.vertices.x,m_sQuad.bl.vertices.y),
        ccp(m_sQuad.br.vertices.x,m_sQuad.br.vertices.y),
        ccp(m_sQuad.tr.vertices.x,m_sQuad.tr.vertices.y),
    };
    ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
    // draw texture box
    CCSize s = this->getTextureRect().size;
    CCPoint offsetPix = this->getOffsetPosition();
    CCPoint vertices[4] = {
        ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
        ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
    };
    ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW
    
    CC_INCREMENT_GL_DRAWS(1);
    
    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
    
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
    if ( current_time() > color_mask_expire_time )
        color_mask(ccc4f(0, 0, 0, 0), 0);
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
    if ( phy_body == nullptr )
        return CCSprite::nodeToParentTransform();
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
    owner->begin_contact(contact);
}

void SpriteComponent::end_contact( class b2Contact* contact )
{
    owner->end_contact(contact);
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

void SpriteComponent::set_fixed_rotation( bool fixed )
{
    if ( phy_body )
        phy_body->SetFixedRotation( fixed );
}

float SpriteComponent::get_rotation()
{
    if ( phy_body )
        return (phy_body->GetAngle());
    else
        return CC_DEGREES_TO_RADIANS(getRotation());
}

void SpriteComponent::set_rotation( float angle )
{
    if ( phy_body )
        phy_body->SetTransform( phy_body->GetPosition(), CC_DEGREES_TO_RADIANS(angle) );
}

void SpriteComponent::wakeup()
{
    if ( phy_body )
        phy_body->SetAwake(true);
}

void SpriteComponent::color_mask( const cocos2d::ccColor4F& color, float time )
{
    
    ccColor4B cc4b;
    if ( time > 0 )
        cc4b = ccc4BFromccc4F( color );
    else
        cc4b = ccc4(0, 0, 0, 0);
    m_sQuad.bl.mask_colors = cc4b;
    m_sQuad.br.mask_colors = cc4b;
    m_sQuad.tl.mask_colors = cc4b;
    m_sQuad.tr.mask_colors = cc4b;
    color_mask_expire_time = current_time() + time;
}

void SpriteComponent::color_tint( const cocos2d::ccColor4F& color, float time )
{
    setColor(ccc3(color.r*255, color.g*255, color.b*255));
    
}

void SpriteComponent::set_shader( const Name& shader_name )
{
}

void SpriteComponent::set_scale(float s)
{
    setScale( s );
    init_physics( phy_desc );
}

class qc: public b2QueryCallback
{
public:
    /// Called for each fixture found in the query AABB.
    /// @return false to terminate the query.
    virtual bool ReportFixture(b2Fixture* fixture)
    {
        hited = true;
        return false;
    }
    bool hited;
};


bool SpriteComponent::hit_test( const cocos2d::CCPoint& world_point)
{
    if ( phy_body != nullptr) //use physics model do percesice hit test
    {
        b2Vec2 b2point = point_to_b2Vec2(world_point);
        auto p = phy_body->GetFixtureList();
        while( p )
        {
            if (p->TestPoint(b2point))
                return true;
            p = p->GetNext();
        }
    }
    else
    {
        //world-space aabb box check, simple and rough
        CCRect rect = CCRectMake(0, 0, m_obContentSize.width, m_obContentSize.height);
        CCRectApplyAffineTransform( rect, nodeToWorldTransform() );
        if ( rect.containsPoint(world_point) )
            return true;
    }
    return false;
}

FE_NS_END