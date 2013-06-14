//
//  FEUtilits.h
//  FEX
//
//  Created by Fancyzero on 13-6-11.
//
//

#ifndef __FEX__FEUtilits__
#define __FEX__FEUtilits__

#include "cocos2d.h"
#include "Box2D.h"
cocos2d::CCPoint str_to_point( const char* str );
std::vector<std::string> split_string( const std::string& str, const std::string& split_by );
b2JointType str_to_joint_type( const char* str );
std::string full_path( const char* filename );
std::string file_name_from_path( const std::string& path );
std::string file_extension_from_path( const std::string& path );
std::string relative_path_to_app( const std::string& path );//get relative path to app directory
//void log( const char* txt, ... );

#endif /* defined(__FEX__FEUtilits__) */
