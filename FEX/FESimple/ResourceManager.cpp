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
#include <memory>
#include <FE.h>


FE_NS_BEGIN


ResourceManager* ResourceManager::instance()
{
    static ResourceManager* mgr = nullptr;
    if ( mgr == nullptr )
        mgr = new ResourceManager();
    return mgr;
}

void ResourceManager::load_sprite_desc( const std::string& filename )
{
    pugi::xml_document doc;
    doc.load_file( filename.c_str() );
    

    for ( auto it : doc.child("sprites").children("sprite") )//<sprites><sprites>...
    {
        sprite_desc* desc = new sprite_desc;
        std::string name = it.attribute("name").as_string();
        
        for ( auto cmpit : it.child("components").children("component") )//<sprite><components><component>...
        {
            sprite_component_ref sc_ref;
            
            sc_ref.component_name = cmpit.attribute("desc").as_string();
            sc_ref.offset = string_to_point(cmpit.attribute("offset").as_string());
            desc->components.push_back(sc_ref);
        }
        for ( auto jointit : it.child("joints").children("joint") )
        {
            sprite_joint_desc jdesc;
            jdesc.component_a = jointit.attribute("component_a").as_int();
            jdesc.component_b = jointit.attribute("component_b").as_int();
            //create b2jointdef
            switch( str_to_joint_type(jointit.attribute("type").as_string() ))
            {
                case e_revoluteJoint:
                    //nothing to do
                    break;
                default:
                    break;
            }
            desc->joints.push_back(jdesc);
        }
        sprite_descs[name] = std::shared_ptr<sprite_desc>(desc);

    }
    
    
    for ( auto it = sprite_descs.begin(); it != sprite_descs.end(); ++it )
    {

        logger("ResMgrDbg") << it->first << endl;
    }
    
}

void ResourceManager::load_physic_desc( const std::string& filename )
{
    pugi::xml_document doc;
    doc.load_file( filename.c_str() );
    
    for ( auto body_node: doc.child("bodies").children("body") )
    {
        physic_desc* desc = new physic_desc();
        for( auto fixture_node: body_node.children() )
        {
            b2fixture_def fixdef;
            b2Shape* shape;
            if ( std::string("circle") == fixture_node.name()  )
            {
                shape = new b2CircleShape();
                shape->m_radius = fixture_node.attribute("radius").as_float() / ptm_ratio();
                ((b2CircleShape*)shape)->m_p = string_to_b2Vec(fixture_node.attribute("center").as_string());
                ((b2CircleShape*)shape)->m_p.x /= ptm_ratio();
                ((b2CircleShape*)shape)->m_p.y /= ptm_ratio();
            }
            if ( std::string("polygon") == fixture_node.name() )
            {
                shape = new b2PolygonShape();

                auto floats = string_to_floats( fixture_node.attribute("vertices").as_string() );
                std::vector<b2Vec2> tmpvecs(floats.size()/2);
                for ( int i = 0; i < floats.size(); i+=2 )
                {
                    tmpvecs[i/2].x = floats[i] / ptm_ratio();
                    tmpvecs[i/2].y = floats[i+1] / ptm_ratio();
                }
                ((b2PolygonShape*)shape)->Set(&tmpvecs[0], floats.size()/2);
            }
            fixdef.shape = shape;
            fixdef.isSensor = fixture_node.attribute("is_sensor").as_bool();
            fixdef.identity = fixture_node.attribute("identity").as_int();
            desc->fixture_defs.push_back(fixdef);
        }
        desc->body_def.type = string_to_b2BodyType( body_node.attribute("type").as_string() );
        physic_descs[body_node.attribute("name").as_string()] = std::shared_ptr<physic_desc>(desc);
    }

    for ( auto it = physic_descs.begin(); it != physic_descs.end(); ++it )
    {
        logger("ResMgrDbg") << "PhysicDesc: " << it->first << endl;
    }
}

void ResourceManager::load_sprite_component_desc( const std::string& filename )
{
    pugi::xml_document doc;
    doc.load_file( filename.c_str() );

    for ( auto it : doc.child("sprite_components").children("component") )
    {
        sprite_component_desc* desc = new sprite_component_desc();
        std::string name = it.attribute("name").as_string();
        for ( auto animit : it.child("animations").children("sequence") )
        {
            //create animations by definition and store in another map

            std::string anim_name;
            anim_name = animit.attribute("name").as_string();
            //if already exists , skip
            std::string unique_anim_name = name + ":" + anim_name;
            if ( animations.item(unique_anim_name) != nullptr )
                continue;
            
            std::vector<std::string> frame_names = split_string(animit.attribute("frames").as_string(), ",");
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
                ccanim = CCAnimation::createWithSpriteFrames(array_frames, frame_speed);
            else
                ccanim = CCAnimation::createWithSpriteFrames(array_frames);

            //as a resource , animation should be cached as well
            animations[unique_anim_name] = std::shared_ptr<animation>( new animation({anim_name,ccanim}));
            desc->animation_names.push_back(unique_anim_name);
        }
        pugi::xml_node body_node = it.child("physics_def").child("body");
        if ( body_node )
        {
            desc->physic_desc_name = body_node.attribute("url").as_string();
        }
        sprite_components[name] = std::shared_ptr<sprite_component_desc>(desc);
 
    }

    //logout("Dbg.ResourceMan") << "sprite components loaded:" << endl;
    for ( auto it = sprite_components.begin(); it != sprite_components.end(); ++it )
    {
        //logout("Dbg.ResourceMan") << it->first << endl;
    }

   // logout("Dbg.ResourceMan") << "sprite animations loaded:" << endl;
    for ( auto it = animations.begin(); it != animations.end(); ++it )
    {
        //logout("Dbg.ResourceMan") << it->first << endl;
    }
    
}
FE_NS_END