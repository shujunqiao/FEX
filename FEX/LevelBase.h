//
//  LevelBase.h
//  FEX
//
//  Created by Fancyzero on 13-6-22.
//
//

#ifndef __FEX__LevelBase__
#define __FEX__LevelBase__

#include "FE.h"
#include "FEUtility.h"
#include <map>
#include <vector>
/*
 LevelBase
 定义游戏地图大小、关卡逻辑、等等
 */
//USING_NS_CC;

FE_NS_BEGIN
struct LevelTrigger
{
    float progress;//when to activate
    std::map<Name,std::string> params;
    
    template<typename T>
    T param(const Name& name)
    {
        T t;
        t << params[name];
        return t;
    }
    
};

struct LevelBound
{
    cocos2d::CCRect rect;
};

struct LevelData
{
    LevelData(){}
    LevelData( const std::string& filename );
    bool load( const std::string& filename );
    void clear();
    
    LevelBound                  bound;
    std::vector<LevelTrigger>   triggers;
};

class LevelBase
{
public:
    virtual bool attach( const LevelData* data );  //附加关卡，不删除现有内容
    virtual void reset();   //重置关卡，删除所有游戏对象
    virtual void triggering_trigger( LevelTrigger& trigger );
    void update( float delta_time );

    LevelBound& get_bound()
    {
        return level_data.bound;
    }
protected:
    unsigned int current_trigger;
    float       start_time;
    LevelData   level_data;
    
};
FE_NS_END
#endif /* defined(__FEX__LevelBase__) */
