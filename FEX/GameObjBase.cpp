//
//  GameObjBase.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//
#include "FE.h"
#include "GameObjBase.h"
#include "SpriteBase.h"

FE_NS_BEGIN

bool EditorProxy::hit_test( const cocos2d::CCPoint& pt )
{
    std::shared_ptr<SpriteBase> sprite = std::dynamic_pointer_cast<SpriteBase>(object.lock());
    
    if ( sprite )
    {
        for ( auto& i : sprite->get_components() )
        {
            if ( i->boundingBox().containsPoint(pt) )
                return true;
        }
    }
    return false;
}

void EditorProxy::set_selected( bool _selected )
{
    selected = _selected;
    std::shared_ptr<SpriteBase> sprite = std::dynamic_pointer_cast<SpriteBase>(object.lock());
    
    if ( sprite )
    {
        if ( selected )
            sprite->each_component( &SpriteComponent::color_mask, cocos2d::ccc4f(0.0,1.0,0.0,0.5 ), 1000000.0f);
        else
            sprite->each_component( &SpriteComponent::color_mask, cocos2d::ccc4f(0.0,0.5,0.0,1.0 ), 0.0f);
    }
    
}


IMPLEMENT_CLASS_INFO(GameObjBase,{})

GameObjBase::GameObjBase( const SpawnParams& params )
{

}

GameObjBase::GameObjBase()
{

}

GameObjBase::~GameObjBase() throw()
{

    logger("obj lifetime") << "object: " << name << "( " << this << " ) destoryed" << endl;
}

void GameObjBase::update( float delta_time )
{
}

FE_NS_END