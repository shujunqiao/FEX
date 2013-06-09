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

namespace FESimple
{
    class GameWorld;
    class GameBase
    {
    public:
        GameBase();
        ~GameBase();
        void update(float delta_time);
        void clean();
    protected:
        std::unique_ptr<GameWorld>           m_game_world;
    };
}

#endif /* defined(__FEX__GameBase__) */
