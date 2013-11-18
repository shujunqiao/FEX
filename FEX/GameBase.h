//
//  GameBase.h
//  FEX
//
//  Created by Fancyzero on 13-6-8.
//
//

#ifndef __FEX__GameBase__
#define __FEX__GameBase__

#include <memory>
#include <list>
#include <algorithm>
class b2World;
FE_NS_BEGIN

class LevelBase;
class GameWorld;
class GameScene;
class GameObjBase;
class GameBase
{
public:
    GameBase();
    virtual ~GameBase();
    
    virtual void update(float delta_time);
    void clear();                       //删除所有对象
    
    void add_object( GameObjPtr obj, const Name& to_layer );
    void remove_game_object( GameObjPtr obj );

    //scene
    GameScene* get_scene()
    {
        return scene.get();
    }
    
    b2World* get_phy_world()
    {
        return phy_world.get();
    }
    
    LevelBase* get_level()
    {
        return level.get();
    }
    
    void set_level( LevelBase* lvl );
    template<class _Predicate>
    GameObjPtr find_obj_if( _Predicate predicate )
    {
        return *std::find_if( objects.begin(), objects.end(), predicate );
    }

    template<class _Predicate>
    std::vector<GameObjPtr> find_all_if( _Predicate predicate )
    {
        std::vector<GameObjPtr> result;
        std::for_each(objects.begin(), objects.end(), [](GameObjPtr i){ if ( predicate(i)) result.push_back(i); } );
        return result;
    }
    
    template<class _Predicate>
    void each_obj( _Predicate predicate )
    {
        std::for_each( objects.begin(), objects.end(), predicate);
    }
    
    virtual bool is_editor()
    {
        return false;
    }
    GameObjPtr get_obj( const Name& name );
    std::list<GameObjPtr>& get_objects()
    {
        return objects;
    }
protected:
    std::unique_ptr<LevelBase>              level;
    std::unique_ptr<GameScene>              scene;       // visible world
    std::unique_ptr<b2World>                phy_world;
    std::list<GameObjPtr>                   objects;
};
FE_NS_END

#endif /* defined(__FEX__GameBase__) */
