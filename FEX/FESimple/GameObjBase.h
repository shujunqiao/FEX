//
//  GameObjBase.h
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#ifndef __FEX__GameObjBase__
#define __FEX__GameObjBase__

#include "FE.h"
#include <string>
FE_NS_BEGIN
class GameWorld;
class GameBase;
class GameObjBase
{
public:
    GameObjBase();
    ~GameObjBase();
    //triggers
    virtual void added_to_game( GameBase* game ){};
    virtual void removed_from_game(GameBase* game ){};
    
    const std::string& name()
    {
        return m_name;
    }
protected:
    std::string m_name;
};
FE_NS_END
#endif /* defined(__FEX__GameObjBase__) */
