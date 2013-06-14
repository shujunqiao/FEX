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
    void clean();
    
    void add_game_object( GameObjPtr obj );
    void remove_game_object( GameObjPtr obj );
    
    //scene
    GameScene* scene()
    {
        return m_scene.get();
    }
protected:
    std::unique_ptr<GameScene>              m_scene;       // visible world
    std::unique_ptr<b2World>                m_phy_world;
    std::list<GameObjPtr>                   m_objects;
    
};
FE_NS_END

#endif /* defined(__FEX__GameBase__) */
