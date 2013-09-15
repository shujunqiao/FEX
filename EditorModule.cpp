//
//  EditorModule.cpp
//  FEXMac
//
//  Created by Fancyzero on 13-9-8.
//
//

#include "EditorModule.h"
#include "SpriteBase.h"
FE_NS_BEGIN

bool AddController::ccTouchBegan(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent)
{
    cocos2d::CCPoint pt = pTouch->getLocation();
    std::string strpt = point_to_string(pt);
    
    
    LevelTrigger lt = EditorModule::get_instance()->get_template_trigger();
    lt.params["init_location"] = strpt;
    logger("editor") << "add "<<lt.params["class"]<<" at: "<< strpt << endl;
    auto obj = FESimple::GameObjFactory::construct_obj( lt.params["class"], lt.params );
    if (obj)
        get_game()->add_game_object(obj, "root");
    return true;
}
void AddController::ccTouchMoved(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent)
{
}
void AddController::ccTouchEnded(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent)
{
}
void AddController::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

bool EditController::ccTouchBegan(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent)
{
    //todo: pick sprite
    EditorModule::get_instance()->pick_object(pTouch->getLocation());
    return true;
}
void EditController::ccTouchMoved(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent)
{
}
void EditController::ccTouchEnded(cocos2d::CCTouch *pTouch,     cocos2d::CCEvent *pEvent)
{
}
void EditController::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

EditorModule::EditorModule()
{
    AddController* ac = new AddController();
    ac->set_name("_add_controller_");
    get_game_info()->add_controller( ac );
    EditController* ec = new EditController();
    ac->set_name("_edit_controller_");
    get_game_info()->add_controller( ec );
    
}

void EditorModule::pick_object( const cocos2d::CCPoint& pos )
{
    auto last_selection = selected_objects;
    selected_objects.clear();
    std::for_each(get_game()->get_objects().begin(), get_game()->get_objects().end(), [pos,this](std::shared_ptr<GameObjBase> obj)
                  {
                      auto spr = std::dynamic_pointer_cast<SpriteBase>(obj);
                      if ( spr && spr->get_editor_proxy()->hit_test( pos ) )
                      {
                          selected_objects.push_back(spr);
                          spr->get_editor_proxy()->set_selected(true);
                      }
                  });
    
    //only one selected
    if ( selected_objects.size() > 0 )
        selected_objects.erase(selected_objects.begin()+1, selected_objects.end());
    //unselect old selections
    for( auto i : last_selection )
    {
        if ( std::find(selected_objects.begin(), selected_objects.end(), i) == selected_objects.end() )
        {
            i->get_editor_proxy()->set_selected(false);
        }
    }
    
}

void EditorModule::select_object( GameObjPtr obj )
{
    obj->get_editor_proxy()->set_selected(true);
}

void EditorModule::unselect_object( GameObjPtr obj )
{
    obj->get_editor_proxy()->set_selected(false);
}

EditorModule* EditorModule::get_instance()
{
    static EditorModule* editor = nullptr;
    if ( editor == nullptr )
        editor = new EditorModule();

    return editor;
}
FE_NS_END