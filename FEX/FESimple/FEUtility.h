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
#include "FE.h"
#include "logger.h"
#include <iostream>

FE_NS_BEGIN
cocos2d::CCPoint string_to_point( const char* str );
std::vector<std::string> split_string( const std::string& str, const std::string& split_by );
b2JointType str_to_joint_type( const char* str );
std::string full_path( const char* filename );
std::string file_name_from_path( const std::string& path );
std::string file_extension_from_path( const std::string& path );
std::string relative_path_to_app( const std::string& path );//get relative path to app directory
std::vector<float>  string_to_floats( const std::string& str );
b2Vec2 string_to_b2Vec( const std::string& str );
b2BodyType string_to_b2BodyType( const std::string& str );
class GameBase* get_game();
float ptm_ratio();
b2Vec2 point_to_b2Vec2( const cocos2d::CCPoint& pt );
cocos2d::CCPoint b2Vec2_to_point( const b2Vec2& vec );

FE_NS_END
#endif /* defined(__FEX__FEUtilits__) */
