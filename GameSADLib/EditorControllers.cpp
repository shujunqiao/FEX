//
//  DesktopInput.cpp
//  GameSADLib
//
//  Created by Fancyzero on 13-8-4.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#include "EditorControllers.h"
#include "FEUtility.h"
#include "SpriteBase.h"
#include "GameBase.h"
#include <memory>
#include "cocos2d.h"
#include "GameSADEditor.h"
#include "GameSADEditorLevel.h"
USING_NS_CC;
FE_NS_USING;

bool EditingController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //pick object
    get_editor_level()->pick_object(pTouch->getLocation());
    return true;
}
void EditingController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void EditingController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void EditingController::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void EditingController::plug()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}
void EditingController::unplug()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


bool AddController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint pt = pTouch->getLocation();
    std::string strpt = point_to_string(pt);

    if ( get_editor_level() == nullptr )
        return true;

    LevelTrigger lt = get_editor_level()->get_template_trigger();
    lt.params["init_location"] = strpt;
    logger("editor") << "add "<<lt.params["class"]<<" at: "<< strpt << endl;
    auto obj = FESimple::GameObjFactory::construct_obj( lt.params["class"], lt.params );
    if (obj)
        get_game()->add_game_object(obj, "root");
    return true;
}
void AddController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void AddController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void AddController::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}
void AddController::plug()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}
void AddController::unplug()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}