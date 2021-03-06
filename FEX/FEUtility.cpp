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
#include <random>
#include "FE.h"
#include "GameBase.h"
#include "SpriteBase.h"

using namespace FESimple;


FE_NS_BEGIN

std::random_device rd;
std::mt19937    mt_random_engine(rd());
/*
 template<int n>
 struct Pi
 {
 public:
 constexpr const static float value = 4 *pow(-1, n+1)/(2*n-1) + Pi<n-1>::value;
 };
 
 
 template<>
 struct Pi<1>
 {
 public:
 constexpr const static float value = 4.0f;
 };
 
 float Pi2 = Pi<100>::value;
 */
float Pi = 3.14159265359f;
float curtime = 0;
float current_time()
{
    return curtime;
}
void set_current_time(float time)
{
    curtime = time;
}

cocos2d::CCPoint string_to_point( const char* str )
{
    cocos2d::CCPoint pt;
    auto floats = split_string( str, "," );
    if ( floats.size() < 2 )
        return pt;
    pt.x = atof(floats[0].c_str());
    pt.y = atof(floats[1].c_str());
    return pt;
}

std::string point_to_string( const cocos2d::CCPoint pt )
{
    char ret[1024];
    sprintf(ret, "%f,%f", pt.x, pt.y);
    return ret;
}

cocos2d::CCRect string_to_rect( const char* str )
{
    cocos2d::CCRect rc;
    auto floats = split_string( str, "," );
    if ( floats.size() < 4 )
        return rc;
    rc.origin.x = atof(floats[0].c_str());
    rc.origin.y = atof(floats[1].c_str());
    rc.size.width = atof(floats[2].c_str());
    rc.size.height = atof(floats[3].c_str());
    
    return rc;
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
        logger("") << first->str() << "  :   " << *first << endl;
        result.push_back( stof(*first) );
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
class GameBase;

void set_game(GameBase* g)
{
    get_game_info()->game = g;
}
class GameBase* get_game()
{
    return get_game_info()->game;
}

float phy_data_scale()
{
    return 1;
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

cocos2d::CCPoint& operator << (cocos2d::CCPoint& pt, const std::string& str)
{
    pt = string_to_point( str.c_str() );
    return pt;
}

bool& operator << (bool& b, const std::string& str)
{
    b = (strcasecmp("true", str.c_str() ) == 0 );
    return b;
}

cocos2d::CCRect& operator << (cocos2d::CCRect& rc, const std::string& str )
{
    rc = string_to_rect(str.c_str());
    return rc;
}

cocos2d::CCPoint operator + ( const cocos2d::CCPoint& pt1, const cocos2d::CCPoint& pt2 )
{
    return cocos2d::CCPoint( pt1.x + pt2.x, pt1.y + pt2.y );
}

cocos2d::CCPoint operator - ( const cocos2d::CCPoint& pt1, const cocos2d::CCPoint& pt2 )
{
    return cocos2d::CCPoint( pt1.x - pt2.x, pt1.y - pt2.y );
}

float angle_to_rad( float angle )
{
    return angle  * (Pi / 180.0f);
}

float rad_to_angle( float rad )
{
    return rad * (180.0f / Pi);
}

float random( float from, float to )
{
    std::uniform_int_distribution<float> float_uniform_dist(from,to);
    return float_uniform_dist(mt_random_engine);
}

cocos2d::CCPoint random_dir( float from_rad, float to_rad )
{
    float rad = random(from_rad, to_rad);
    return cocos2d::CCPoint( cos(rad), sin(rad) );
}


GameInfo    g_game_info;

GameInfo* get_game_info()
{
    return &g_game_info;
}

GameObjPtr make_gameobj_ptr( GameObjBase* p )
{
    return GameObjPtr(p);
}

bool init_python(const std::string& python_home)
{
//    char path[1024];
//    strcpy(path,python_home.c_str());
//    Py_SetPythonHome(path);
//    Py_Initialize();
//    
//    init_FEX();
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString("print sys.path");
    return true;
}

bool ends_with( const std::string& bigger_str, const std::string& smaller_str )
{
    std::string::size_type pos = bigger_str.find_last_of(smaller_str);
    return pos+1 == bigger_str.length();
}

cocos2d::CCSize get_screen_size()
{
    return cocos2d::CCDirector::sharedDirector()->getWinSize();
}

class pick_sprite_cb :public b2QueryCallback
{
public:
    /// Called for each fixture found in the query AABB.
    /// @return false to terminate the query.
    SpriteComponent* picked = nullptr;//weak ref
    virtual bool ReportFixture(b2Fixture* fixture)
    {
        if ( fixture->GetUserData() == nullptr )
            return true;
        
        SpriteComponent* cmp = static_cast<SpriteComponent*>(fixture->GetUserData());
        
        if ( picked == nullptr )
            picked = cmp;
        else if ( picked->getZOrder() < cmp->getZOrder() )
            picked = cmp;
        return true;
    }
};

SpriteComponent* pick_sprite( const cocos2d::CCPoint world_point )
{
    b2AABB aabb;
    aabb.lowerBound = aabb.upperBound = point_to_b2Vec2( world_point );
    pick_sprite_cb cb;
    get_game()->get_phy_world()->QueryAABB( &cb, aabb );
    return cb.picked;
}
GameObjBase* get_raw_ptr( std::shared_ptr<GameObjBase>& ptr )
{
    return ptr.get();
    
}
SpriteBase* get_raw_ptr( std::shared_ptr<SpriteBase>& ptr )
{
    return ptr.get();
    
}
SpriteBase* get_raw_ptr( std::weak_ptr<SpriteBase>& ptr )
{
    return ptr.lock().get();
}

cocos2d::CCPoint radians_to_vector( float rad )
{
    return cocos2d::CCPoint( cosf(rad), sinf(rad) );
}

FE_NS_END

