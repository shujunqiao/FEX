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
#include "Box2D/Box2D.h"
#include "FE.h"
#include "logger.h"
#include <iostream>

FE_NS_BEGIN
extern float Pi;
cocos2d::CCPoint string_to_point( const char* str );
cocos2d::CCRect string_to_rect( const char* str );
std::vector<std::string> split_string( const std::string& str, const std::string& split_by );
b2JointType str_to_joint_type( const char* str );
std::string full_path( const char* filename );
std::string file_name_from_path( const std::string& path );
std::string file_extension_from_path( const std::string& path );
std::string relative_path_to_app( const std::string& path );//get relative path to app directory
std::vector<float>  string_to_floats( const std::string& str );
b2Vec2 string_to_b2Vec( const std::string& str );
b2BodyType string_to_b2BodyType( const std::string& str );
void set_game( class GameBase* game );
class GameBase* get_game();
//class ControllerBase get_controller( int id );
float ptm_ratio();
b2Vec2 point_to_b2Vec2( const cocos2d::CCPoint& pt );
cocos2d::CCPoint b2Vec2_to_point( const b2Vec2& vec );

cocos2d::CCPoint& operator << (cocos2d::CCPoint& pt, const std::string& str);
bool& operator << (bool& b, const std::string& str);
cocos2d::CCRect& operator << (cocos2d::CCRect& rc, const std::string& str );
cocos2d::CCPoint operator + ( const cocos2d::CCPoint& pt1, const cocos2d::CCPoint pt2 );
cocos2d::CCPoint operator - ( const cocos2d::CCPoint& pt1, const cocos2d::CCPoint pt2 );

float angle_to_rad( float angle );
float rad_to_angle( float rad );
float random( float from = 0.0f, float to = 1.0f);
cocos2d::CCPoint random_dir( float from_rad = 0, float to_rad = Pi*2 );

class ControllerBase;
struct GameInfo
{
    class GameBase*                         game;
    std::vector<ControllerBase*>      controllers;    
};
extern GameInfo    g_game_info;
GameInfo* get_game_info();


FE_NS_END



#endif /* defined(__FEX__FEUtilits__) */
