 //
//  IOSTcouchController.cpp
//  FEXGameTemplate
//
//  Created by Fancyzero on 13-6-28.
//
//

#include "IOSTcouchController.h"
#include "FEUtility.h"
#include "SpriteBase.h"
#include "GameBase.h"
#include "GameTheSoldiers.h"
#include <memory>
using namespace FESimple;
bool IOSTouchController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    auto pt = pTouch->getLocation();
    GameTheSoldiers* game = dynamic_cast<GameTheSoldiers*>(get_game());
    game->each_obj([](GameObjPtr obj){ if ( std::dynamic_pointer_cast<SpriteBase>(obj) ) std::dynamic_pointer_cast<SpriteBase>(obj)->each_component(&SpriteComponent::apply_linear_impulse, CCPoint(10,10)); });
    return true;
}
void IOSTouchController::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
void IOSTouchController::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}
void IOSTouchController::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}

