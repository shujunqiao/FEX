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
#include <map>
#include <memory>
FE_NS_BEGIN

class GameWorld;
class GameBase;

class GameObjBase : public std::enable_shared_from_this<GameObjBase>
{

public:
    //static ClassInfo  classinfo;
    //virtual ClassInfo* get_class_info(){ return &GameObjBase::classinfo; };
    DECLARE_CLASS_INFO(GameObjBase)

    GameObjBase( const SpawnParams& params );
    GameObjBase();
    ~GameObjBase();
    //triggers
    virtual void added_to_game( GameBase* game, const Name& to_layer ){};
    virtual void removed_from_game(GameBase* game ){};

    virtual void update( float delta_time );
    
    
    const Name& get_name()
    {
        return name;
    }
    bool is_dead()
    {
        return dead;
    }
    void set_dead( bool b)
    {
        dead = b;
    }
protected:
    bool        dead;

    std::string name;
};


FE_NS_END
#endif /* defined(__FEX__GameObjBase__) */
