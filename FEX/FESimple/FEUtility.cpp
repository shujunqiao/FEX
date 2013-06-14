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

cocos2d::CCPoint str_to_point( const char* str )
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

#define STR2JOINTTYPE(str,jtype) if (strcmp(str, "##jtype##")) return e_##jtype##Joint;

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