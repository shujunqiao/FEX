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
    Name                   m_name;    
    cocos2d::CCAnimation*  m_animation;
};

struct physic_desc
{
    b2BodyDef   m_body_def;
    std::vector<b2FixtureDef>   m_fixture_def;

};

struct sprite_component_desc
{
    Name                        m_physic_desc;
    std::vector<std::string>    m_animation_names;//animation name
    cocos2d::CCPoint    m_offset;
};

struct sprite_component_ref
{
    Name    m_component_name;
    CCPoint m_offset;
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
        b2RevoluteJointDef  m_revolute_joint_def;
        b2MouseJointDef     m_mouse_joint_def;
    };//for describe not for create joint
    unsigned int    m_component_a;
    unsigned int    m_component_b;
    unsigned int    m_joint_type;//physic joint or other joint
};

struct sprite_desc
{
    std::vector<sprite_component_ref>       m_components;
    std::vector<sprite_joint_desc>          m_joints;
};

struct sprite_animation
{
    sprite_animation( cocos2d::CCAction* anim, const Name& name )
    :m_animation(anim),m_name(name)
    {
    }
    cocos2d::CCAction*  m_animation;
    Name                m_name;
};

class SpriteComponent :public cocos2d::CCSprite
{
public:
    SpriteComponent( const CCPoint& location, const sprite_component_desc& desc );
protected:
    std::vector<sprite_animation>  m_animations;
};

FE_NS_END
#endif /* defined(__FEX__Sprite__) */
