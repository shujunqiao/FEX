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
class b2World;
FE_NS_BEGIN
class GameWorld;
class GameScene;
class GameObjBase;
class GameBase
{
public:
    GameBase();
    ~GameBase();
    
    void update(float delta_time);
    void clean();                       //删除所有对象，关卡
    
    void add_game_object( GameObjPtr obj, const Name& to_layer );
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
    
protected:
    std::unique_ptr<GameScene>              scene;       // visible world
    std::unique_ptr<b2World>                phy_world;
    std::list<GameObjPtr>                   objects;

};
FE_NS_END

#endif /* defined(__FEX__GameBase__) */
