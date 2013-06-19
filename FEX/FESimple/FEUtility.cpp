//
//  FEUtilits.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-11.
//
//

#include "FEUtility.h"
#include "cocos2d.h"
#include <regex>
#include <iostream>
#include "FE.h"
#include "GameBase.h"

FE_NS_BEGIN
cocos2d::CCPoint string_to_point( const char* str )
{
    return cocos2d::CCPointFromString(str);
}


std::vector<std::string> split_string( const std::string& s, const std::string& separator )
{
    std::regex sep(separator);
    std::sregex_token_iterator first(s.begin(), s.end(), sep, -1);
    std::sregex_token_iterator last;
    return {first, last};
}

#define STR2JOINTTYPE(str,jtype) if (strcmp(str, "##jtype##") == 0) return e_##jtype##Joint;
#define STR2BODYTYPE(str,btype)  if (strcmp(str, "##btype##") == 0) return b2_##btype##Body;

b2JointType str_to_joint_type( const char* str )
{
    STR2JOINTTYPE(str, revolute);
    STR2JOINTTYPE(str, prismatic);
    STR2JOINTTYPE(str, distance);
    STR2JOINTTYPE(str, pulley);
    STR2JOINTTYPE(str, mouse);
    STR2JOINTTYPE(str, gear);
    STR2JOINTTYPE(str, wheel);
    STR2JOINTTYPE(str, weld);
    STR2JOINTTYPE(str, friction);
    STR2JOINTTYPE(str, rope);
    return e_unknownJoint;
}

std::string full_path( const char* filename )
{
    return cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename( filename );
}

std::string file_name_from_path( const std::string& path )
{
    return path.substr(path.find_last_of('/')+1);
}

std::string file_extension_from_path( const std::string& path )
{
    return path.substr(path.find_last_of('.')+1);
}

std::string relative_path_to_app( const std::string& path )
{
    std::string base_path = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename("");
    while ( path.find(base_path) == std::string::npos )
    {
        base_path = base_path.substr(0,base_path.find_last_of('/'));
    }
    return path.substr(base_path.size()+1);
}

std::vector<float> string_to_floats( const std::string& s )
{
    std::vector<float> result;
    std::regex sep(",");
    std::sregex_token_iterator first(s.begin(), s.end(), sep, -1);
    std::sregex_token_iterator last;
    while( first != last )
    {
        result.push_back( atof(first->str().c_str()));
        first++;
    }
    return result;
}

b2Vec2 string_to_b2Vec( const std::string& str )
{
    cocos2d::CCPoint pt = string_to_point( str.c_str() );
    return b2Vec2( pt.x, pt.y );
}

b2BodyType string_to_b2BodyType( const std::string& str )
{
    STR2BODYTYPE(str.c_str(), dynamic);
    STR2BODYTYPE(str.c_str(), static);
    STR2BODYTYPE(str.c_str(), kinematic);
    return b2_dynamicBody;
}


class GameBase* get_game()
{
    static GameBase* g = nullptr;
    if ( g == nullptr )
        g = new GameBase();
    return g;
}

float ptm_ratio()
{
    return 32.0f;
}

b2Vec2 point_to_b2Vec2( const cocos2d::CCPoint& pt )
{
    return b2Vec2( pt.x / ptm_ratio(), pt.y / ptm_ratio() );
}

cocos2d::CCPoint b2Vec2_to_point( const b2Vec2& vec )
{
    return cocos2d::CCPoint( vec.x * ptm_ratio(), vec.y * ptm_ratio() );
}



FE_NS_END

