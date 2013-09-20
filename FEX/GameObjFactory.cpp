//
//  GameObjFactory.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-23.
//
//
#include <functional>
#include "GameObjFactory.h"
#include "SpriteBase.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "python.h"
FE_NS_BEGIN


std::map<std::string,const ClassInfo*> fe_classes;

void register_FEX_classes()
{
    fe_classes["GameObjBase"] = CLASS_INFO_OF(GameObjBase);
    fe_classes["SpriteBase"] = CLASS_INFO_OF(SpriteBase);
    fe_classes["GameScene"] = CLASS_INFO_OF(GameScene);
    fe_classes["GameLayer"] = CLASS_INFO_OF(GameLayer);

}

GameObjPtr GameObjFactory::construct_obj( const Name& classname, const SpawnParams& params )
{
    GameObjPtr obj;
    
    auto it = fe_classes.find(classname);
    if ( it != fe_classes.end() )
    {
        obj.reset(((GameObjBase*)it->second->constructor(params)));
        if ( get_game() && get_game()->is_editor() )
        {
            obj->set_editor_proxy(new EditorProxy());
            obj->get_editor_proxy()->set_object(obj);
        }
        obj->set_class_info(it->second);
        return obj;
    }
    //try construct object by script
    auto obj_from_script = get_game()->construct_obj( classname, params );
    if ( obj_from_script )
        return obj_from_script;
    logger("GameObjFactory") << "constructor of class:<" << classname <<"> not found." << endl;
    return GameObjPtr(nullptr);
}
const std::map<std::string, const ClassInfo*>& GameObjFactory::get_all_classes()
{
    return fe_classes;
}

void GameObjFactory::add_class_info(const ClassInfo* info)
{
    fe_classes[info->name] = info;
}
FE_NS_END