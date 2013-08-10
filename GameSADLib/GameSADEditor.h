//
//  GameSADEditor.h
//  GameSADLib
//
//  Created by Fancyzero on 13-7-23.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#ifndef __GameSADLib__GameSADEditor__
#define __GameSADLib__GameSADEditor__

#include "FE.h"
#include "GameBase.h"
#include "GameSAD.h"
FE_NS_USING;


class GameSADEditor :public GameSAD
{
public:
    GameSADEditor();
    
    enum EditMode
    {
        edit,
        add
    };
    
    void set_editmode( EditMode mode );
    EditMode get_editmode();
    virtual bool is_editor()
    {
        return true;
    }
    
protected:
    EditMode edit_mode;
    std::shared_ptr<ControllerBase> editing_controller;
    std::shared_ptr<ControllerBase> add_controller;
};

GameSADEditor* get_editor();

#endif /* defined(__GameSADLib__GameSADEditor__) */
