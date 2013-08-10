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
    std::for_each(get_editor()->get_objects().begin(), get_editor()->get_objects().end(), [pos,this](std::shared_ptr<GameObjBase> obj)
    {
        auto spr = std::dynamic_pointer_cast<SpriteBase>(obj);
        if ( spr && spr->get_editor_proxy()->hit_test( pos ) )
        {
            selected_objects.push_back(spr);
            return;
        }
    });
}

GameSADEditorLevel* get_editor_level()
{
    if ( get_game() == nullptr )
        return nullptr;
    
    return dynamic_cast<GameSADEditorLevel*>(get_game()->get_level());
}
