//
//  GameSADEditorLevel.h
//  GameSADLib
//
//  Created by Fancyzero on 13-7-23.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#ifndef __GameSADLib__GameSADEditorLevel__
#define __GameSADLib__GameSADEditorLevel__

#include "FE.h"
#include "GameSADLevel.h"
#include "GameSADEditor.h"

FE_NS_USING;

class EditorModule
{
public:
    LevelTrigger& get_template_trigger()
    {
        return template_trigger;
    }
    LevelTrigger& get_current_trigger()
    {
        switch (get_editor()->get_editmode() )
        {
            case GameSADEditor::EditMode::edit:
                return dummy_trigger;
                break;
            case GameSADEditor::EditMode::add:
                return get_template_trigger();
                break;
        }
    }
    void pick_object( const cocos2d::CCPoint& pos );
    void select_object( GameObjPtr obj );
    void unselect_object( GameObjPtr obj );
protected:
    LevelTrigger dummy_trigger;
    LevelTrigger template_trigger;//trigger use to add new object
    std::vector<std::shared_ptr<GameObjBase> > selected_objects;
    
};

class GameSADEditorLevel : public GameSADLevel, public EditorModule
{
};

GameSADEditorLevel* get_editor_level();

#endif /* defined(__GameSADLib__GameSADEditorLevel__) */
