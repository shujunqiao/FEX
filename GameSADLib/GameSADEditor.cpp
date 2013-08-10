//
//  GameSADEditor.cpp
//  GameSADLib
//
//  Created by Fancyzero on 13-7-23.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#include "GameSADEditor.h"
#include "GameSADEditorLevel.h"
#include "EditorControllers.h"
GameSADEditor::GameSADEditor()
{
    editing_controller.reset( new EditingController() );
    add_controller.reset( new AddController() );
    set_editmode(edit);
    level.reset( new GameSADEditorLevel() );
}

void GameSADEditor::set_editmode( EditMode mode )
{
    edit_mode = mode;
    switch (edit_mode)
    {
        case edit:
            editing_controller->plug();
            add_controller->unplug();
            break;
        case add:
            editing_controller->unplug();
            add_controller->plug();
    }
}

GameSADEditor::EditMode GameSADEditor::get_editmode()
{
    return edit_mode;
}

GameSADEditor* get_editor()
{
    return dynamic_cast<GameSADEditor*>(get_game());
}