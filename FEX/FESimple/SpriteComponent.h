//
//  Sprite.h
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#ifndef __FEX__Sprite__
#define __FEX__Sprite__
#include "FE.h"
#include "cocos2d.h"
#include "box2d.h"
using namespace cocos2d;
FE_NS_BEGIN

struct animation
{
    animation( const Name& name, cocos2d::CCAnimation* anim )
    :ccanimation(anim), name(name)
    {
        ccanimation->retain();
    }
    ~animation()
    {
        if ( ccanimation )
            ccanimation->release();
    }
    Name                   name;
    cocos2d::CCAnimation*  ccanimation;
};

struct b2fixture_def :public b2FixtureDef
{
    b2fixture_def()
    :b2FixtureDef(),identity(0)
    {

    }
    int identity;
};

struct physic_desc
{
    ~physic_desc()
    {
        for( auto i : fixture_defs )
        {
            if ( i.shape )
                delete i.shape;
        }
    }
    b2BodyDef   body_def;
    std::vector<b2fixture_def>   fixture_defs;

};

struct sprite_component_desc
{
    Name                        physic_desc_name;
    std::vector<std::string>    animation_names;//animation name
    cocos2d::CCPoint    offset;
};

struct sprite_component_ref
{
    Name    component_name;
    CCPoint offset;
};

struct sprite_joint_desc
{
    sprite_joint_desc()
    {
    }
    ~sprite_joint_desc()
    {
    }
    
    union
    {
        b2RevoluteJointDef  revolute_joint_def;
        b2MouseJointDef     mouse_joint_def;
    };//for describe not for create joint
    unsigned int    component_a;
    unsigned int    component_b;
    unsigned int    joint_type;//physic joint or other joint
};

struct sprite_desc
{
    std::vector<sprite_component_ref>       components;
    std::vector<sprite_joint_desc>          joints;
};

struct sprite_animation
{
    sprite_animation( cocos2d::CCAction* anim, const Name& name )
    :animation(anim), name(name)
    {
        animation->retain();
    }
    ~sprite_animation()
    {
        if ( animation )
            animation->release();
    }
    sprite_animation( const sprite_animation& other )
    {
        *this = other;
    }
    sprite_animation& operator =(const sprite_animation& other )
    {
        animation = other.animation;
        animation->retain();
        name = other.name;
        return *this;
    }
    cocos2d::CCAction*  animation; // strong ref
    Name                name;
};

struct FixtureUserData
{
    class SpriteComponent*      sprite_component;//weak ref
    int                         identity;
};



class SpriteComponent :public cocos2d::CCSprite
{
public:
    SpriteComponent( const CCPoint& location, const std::shared_ptr<sprite_component_desc> desc );
    ~SpriteComponent();
    
    bool play_anim( const Name& anim );
    virtual void draw();
    
    //overrided
    void setPosition(const CCPoint& pos);
    bool isDirty();
    CCAffineTransform nodeToParentTransform();
    
    //physics methods
    void set_linear_velocity( const CCPoint& v );
    void set_linear_damping( float damping );
    void apply_force( const CCPoint& v, const CCPoint& location );
    void apply_force( const CCPoint& v );
    void apply_torque( float q );
    void set_angular_damping( float damping );
    void apply_linear_impulse( const CCPoint& v );
    void apply_angular_impulse( float i );
protected:
    std::vector<sprite_animation>   animations;
    b2Body*                         phy_body;
    
};



FE_NS_END
#endif /* defined(__FEX__Sprite__) */
