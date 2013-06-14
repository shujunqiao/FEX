//
//  ResourceManager.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-10.
//
//

#include "ResourceManager.h"
#include "pugixml.hpp"
#include "FEUtility.h"
#include <algorithm>
FE_NS_BEGIN

SharedReourceMap<sprite_desc>              ResourceManager::m_sprite_descs;
SharedReourceMap<physic_desc>              ResourceManager::m_physic_descs;
SharedReourceMap<sprite_component_desc>    ResourceManager::m_sprite_components;
SharedReourceMap<animation>                ResourceManager::m_animations;

void ResourceManager::load_sprite_desc( const std::string& filename )
{
    pugi::xml_document doc;
    doc.load_file( filename.c_str() );
    

    for ( auto it : doc.child("sprites").children("sprite") )//<sprites><sprites>...
    {
        sprite_desc desc;
        std::string name = it.attribute("name").as_string();
        
        for ( auto cmpit : it.child("components").children("component") )//<sprite><components><component>...
        {
            sprite_component_ref sc_ref;
            
            sc_ref.m_component_name = cmpit.attribute("desc").as_string();
            sc_ref.m_offset = str_to_point(cmpit.attribute("offset").as_string());
            desc.m_components.push_back(sc_ref);
        }
        for ( auto jointit : it.child("joints").children("joint") )
        {
            sprite_joint_desc jdesc;
            jdesc.m_component_a = jointit.attribute("component_a").as_int();
            jdesc.m_component_b = jointit.attribute("component_b").as_int();
            //create b2jointdef
            switch( str_to_joint_type(jointit.attribute("type").as_string() ))
            {
                case e_revoluteJoint:
                    //nothing to do
                    break;
                default:
                    break;
            }
        }
    }

    
}

void ResourceManager::load_physic_desc( const std::string& filename )
{
}

void ResourceManager::load_sprite_component_desc( const std::string& filename )
{
    pugi::xml_document doc;
    doc.load_file( filename.c_str() );

    for ( auto it : doc.child("sprite_components").children("component") )
    {
        sprite_component_desc desc;
        std::string name = it.attribute("name").as_string();
        cout << "sprite component" << name << endl;
        for ( auto animit : it.child("animations").children("sequence") )
        {
            //create animations by definition and store in another map

            std::string anim_name;
            anim_name = animit.attribute("name").as_string();
            //if already exists , skip
            std::string unique_anim_name = relative_path_to_app( filename ) + ":" + name + ":" + anim_name;
            if ( m_animations.item(unique_anim_name) != nullptr )
                continue;
            
            std::vector<std::string> frame_names = split_string(animit.attribute("frames").as_string(), ",");
            cout << "read frames:" << animit.attribute("frames").as_string() << endl;
            //add all frames in plistfile
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(animit.attribute("texture").as_string());
            CCArray* array_frames = CCArray::create();//array to create ccanimation
            float frame_speed = animit.attribute("frame_speed").as_float();
            //unsigned int loop = animit.attribute("loop_count").as_uint();
            
            for( auto frame_name : frame_names )
            {
                CCSpriteFrame* frame = nullptr;
                frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame_name.c_str());
                if ( frame == nullptr )
                {
                    cout << frame_name << " not found" << endl;
                    continue;
                }
                array_frames->addObject(frame);
            }
            if ( array_frames->count() <= 0 )
                continue;

            //array_frame will be autoreleased, and CCAnimation will make a copy inside
            CCAnimation* ccanim;
            if ( frame_speed > 0 )
                ccanim = CCAnimation::createWithSpriteFrames(array_frames, 1.0f/frame_speed);
            else
                ccanim = CCAnimation::createWithSpriteFrames(array_frames);
            ccanim->retain();
            //as a resource , animation should be cached as well
            cout << "add animation " << unique_anim_name << endl;
            m_animations[unique_anim_name] = std::shared_ptr<animation>( new animation({anim_name,ccanim}));
        }
 
    }
}
FE_NS_END