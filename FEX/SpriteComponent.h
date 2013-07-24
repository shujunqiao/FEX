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
#include "Box2D/Box2D.h"
#include <memory>


FE_NS_BEGIN
class SpriteBase;
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
};

struct sprite_component_ref
{
    Name    component_name;
    cocos2d::CCPoint offset;
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

/*
可渲染，可具有物理模型的一种SpriteComponent 
*/

class SpriteComponent :public cocos2d::CCSprite
{
public:
    
    //DECLARE_CLASS_INFO(SpriteComponent)
    
    SpriteComponent( const cocos2d::CCPoint& location, const std::shared_ptr<sprite_component_desc> desc );
    virtual ~SpriteComponent();
    
    bool play_anim( const Name& anim );
    virtual void draw();
    
    //overrided
    void update(float delta_time);
    void setPosition(const cocos2d::CCPoint& pos);
    const cocos2d::CCPoint& getPosition();
    bool isDirty();
    cocos2d::CCAffineTransform nodeToParentTransform();
    
    //physics callback
    void begin_contact( class b2Contact* contact );
    void end_contact( class b2Contact* contact );
    //physics methods
    void set_linear_velocity( const cocos2d::CCPoint& v );
    void set_linear_damping( float damping );
    void apply_force( const cocos2d::CCPoint& v, const cocos2d::CCPoint& location );
    void apply_force( const cocos2d::CCPoint& v );
    void apply_torque( float q );
    void set_angular_damping( float damping );
    void apply_linear_impulse( const cocos2d::CCPoint& v );
    void apply_angular_impulse( float i );
    void wakeup();
    void color_mask( const cocos2d::ccColor4F& color, float time );
    void color_tint( const cocos2d::ccColor4F& color, float time );
    void set_shader( const Name& shader_name );
    void set_owner(std::weak_ptr<SpriteBase> s)
    {
        owner = s;
    }
    class std::weak_ptr<SpriteBase> get_owner()
    {
        return owner;
    }
protected:
    std::weak_ptr<SpriteBase>       owner;
    std::vector<sprite_animation>   animations;
    b2Body*                         phy_body;
    
    
    
};

template <typename ...Args>
void proxycall( Args &&... args)
{
        printf("",args...);
}

FE_NS_END
#endif /* defined(__FEX__Sprite__) */
