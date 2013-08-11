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
#include "ClassInfo.h"
FE_NS_BEGIN

class GameWorld;
class GameBase;
class GameObjBase;
class EditorProxy
{
public:
    EditorProxy()
    :selected(false)
    {
        
    }
public:
    bool hit_test( const cocos2d::CCPoint& pt );
    void set_selected(bool selected);
    void set_object( std::weak_ptr<GameObjBase> obj )
    {
        object = obj;
    }
protected:
    std::weak_ptr<GameObjBase> object;
    bool selected;
};
class GameObjBase : public std::enable_shared_from_this<GameObjBase>
{

public:
    //static ClassInfo  classinfo;
    //virtual ClassInfo* get_class_info(){ return &GameObjBase::classinfo; };
    DECLARE_CLASS_INFO(GameObjBase)

    GameObjBase( const SpawnParams& params );
    GameObjBase();
    virtual ~GameObjBase() throw();
    //triggers
    virtual void added_to_game( GameBase* game, const Name& to_layer ){};
    virtual void removed_from_game(GameBase* game ){};

    virtual void update( float delta_time );
    
    
    const Name& get_name()
    {
        return name;
    }
    void set_name( const Name& n)
    {
        name = n;
    }
    bool is_dead()
    {
        return dead;
    }
    void set_dead( bool b)
    {
        dead = b;
    }
    EditorProxy* get_editor_proxy()
    {
        return editor_proxy.get();
    }
    void set_editor_proxy( EditorProxy* proxy )
    {
        editor_proxy.reset(proxy);
    }
    int get_trigger_id()
    {
        return trigger_id;
    }
    void set_trigger_id( int id )
    {
        trigger_id = id;
    }
    
    void set_class_info( const ClassInfo* info )
    {
        class_info = info;
    }
protected:
    const ClassInfo* class_info;
    int         trigger_id;//the trigger that spawned this sprite    
    bool        dead;
    std::unique_ptr<EditorProxy> editor_proxy;
    std::string name;
};


FE_NS_END
#endif /* defined(__FEX__GameObjBase__) */
