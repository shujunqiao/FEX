//
//  GameSADEditorLevel.cpp
//  GameSADLib
//
//  Created by Fancyzero on 13-7-23.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#include "GameSADEditorLevel.h"
#include "SpriteBase.h"

void EditorModule::pick_object( const cocos2d::CCPoint& pos )
{
    auto last_selection = selected_objects;
    selected_objects.clear();
    std::for_each(get_editor()->get_objects().begin(), get_editor()->get_objects().end(), [pos,this](std::shared_ptr<GameObjBase> obj)
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

void select_object( GameObjPtr obj )
{    
    obj->get_editor_proxy()->set_selected(true);
}

void unselect_object( GameObjPtr obj )
{
    obj->get_editor_proxy()->set_selected(false);
}

GameSADEditorLevel* get_editor_level()
{
    if ( get_game() == nullptr )
        return nullptr;
    
    return dynamic_cast<GameSADEditorLevel*>(get_game()->get_level());
}
