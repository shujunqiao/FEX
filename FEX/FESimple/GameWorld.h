//
//  World.h
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#ifndef __FEX__World__
#define __FEX__World__
#include <list>
#include <memory>
class b2World;

namespace FESimple
{
    class GameLayer;
    class GameObjBase;
    class GameScene;
    class GameWorld
    {
    public:
        GameWorld();
        ~GameWorld();
        
        //object management
        void add_game_object( GameObjBase* obj, std::string into_layer );
        void remove_game_object( GameObjBase* obj );
        void remove_all_game_objects();
        //layers
        GameLayer* get_layer( std::string name );
        void add_layer( GameLayer* layer, std::string name );
        void remove_all_layers();
    protected:

        std::unique_ptr<b2World>        m_phy_world;
        std::list<GameObjBase*>         m_game_objects;
        std::list<GameLayer*>           m_game_layers;
        GameScene*                      m_root_scene;
    };
}
#endif /* defined(__FEX__World__) */
