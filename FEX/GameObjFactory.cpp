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
#include "Python.h"
FE_NS_BEGIN


std::map<std::string,const ClassInfo*> fe_classes;
std::map<std::string,const ClassInfo*>& get_classes_map()
{
    return fe_classes;
}
void register_FEX_classes()
{
    get_classes_map()["GameObjBase"] = CLASS_INFO_OF(GameObjBase);
    get_classes_map()["SpriteBase"] = CLASS_INFO_OF(SpriteBase);
    get_classes_map()["GameScene"] = CLASS_INFO_OF(GameScene);
    get_classes_map()["GameLayer"] = CLASS_INFO_OF(GameLayer);

}

GameObjPtr GameObjFactory::construct_obj( const Name& classname, const SpawnParams& params )
{

    
    auto it = fe_classes.find(classname);
    if ( it != fe_classes.end() )
    {
        GameObjPtr obj((GameObjBase*)it->second->constructor(params));
        if ( get_game() && get_game()->is_editor() )
        {
            obj->set_editor_proxy(new EditorProxy());
            obj->get_editor_proxy()->set_object(obj);
        }
        obj->set_class_info(it->second);
        return obj;
    }
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