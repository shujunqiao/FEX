#include "GameBase.h"
#include "GameWorld.h"
namespace FESimple
{
    GameBase::GameBase()
    :m_game_world(new GameWorld())
    {
        
    }
}