//
//  GameSADEditor.cpp
//  GameSADLib
//
//  Created by Fancyzero on 13-7-23.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#include "GameSADEditor.h"
#include "GameSADEditorLevel.h"
#include "DesktopInput.h"
GameSADEditor::GameSADEditor()
{
    EditorController* tc = new EditorController();
    tc->plug();
    get_game_info()->add_controller(tc);
}