//
//  LevelBase.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-22.
//
//

#include "LevelBase.h"
#include "pugixml.hpp"
FE_NS_BEGIN

bool LevelData::load( const std::string& filename )
{
    pugi::xml_document doc;
    doc.load_file( filename.c_str() );

    pugi::xml_node level_desc = doc.select_single_node("/xml/level").node();
    pugi::xml_node acting_range = doc.select_single_node("/xml/level/acting_range").node();
    pugi::xml_node actions = doc.select_single_node("/xml/level/actions").node();
    
    if ( level_desc )
    {
        bound.rect << level_desc.attribute("rect").as_string();
    }
    if ( acting_range )
    {
        //for ( auto it : acting_range.children("keyframe") )
        {
//			level_acting_range_keyframe k;
//			CGPoint p;
//			k.act_rect.origin = cgpoint_from_string( it.attribute("pos").as_string(), ccp(0,0));
//			p = cgpoint_from_string( it.attribute("size").as_string(), ccp(0,0));
//			k.act_rect.size.width = p.x;
//			k.act_rect.size.height = p.y;
//			k.progress = it.attribute("progress").as_float();
//            data->m_acting_range_keyframes_.push_back(k);
        }
    }
    if ( actions )
    {
        for ( auto it : actions.children("action") )
        {
			LevelTrigger trigger;
			trigger.progress = it.attribute("progress").as_float();

            for( auto attr : it.attributes() )
            {
                trigger.params[attr.name()] = attr.as_string();
            }
            
            triggers.push_back(trigger);
        }
    }
    return true;
}

void LevelBase::update( float delta_time )
{
    
}

FE_NS_END