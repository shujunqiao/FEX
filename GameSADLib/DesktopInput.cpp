//
//  DesktopInput.cpp
//  GameSADLib
//
//  Created by Fancyzero on 13-8-4.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#include "DesktopInput.h"
#include "FEUtility.h"
#include "SpriteBase.h"
#include "GameBase.h"
#include <memory>
#include "cocos2d.h"

USING_NS_CC;
FE_NS_USING;

bool EditorController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint pt = pTouch->getLocationInView();
    std::string strpt = point_to_string(pt);
    auto obj = FESimple::GameObjFactory::construct_obj("Hero", {{"init_location",strpt},{"sprite_desc","hero"}});
    get_game()->add_game_object(obj, "root");
    return true;
}
void EditorController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void EditorController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void EditorController::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

void EditorController::plug()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}
void EditorController::unplug()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
