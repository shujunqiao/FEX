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
FE_NS_USING
GTS_NS_BEGIN

IOSTouchController::IOSTouchController()
:CCTargetedTouchDelegate(),ControllerBase()
{

}

bool IOSTouchController::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    auto pt = pTouch->getLocation();
    GameTheSoldiers* game = dynamic_cast<GameTheSoldiers*>(get_game());


    game->each_obj([&](GameObjPtr obj)
    {
        if ( std::dynamic_pointer_cast<SpriteBase>(obj) )
        {
            CCPoint dir = ccpNormalize((pt - std::dynamic_pointer_cast<SpriteBase>(obj)->component(0)->getPosition()));
            logger("pos") << std::dynamic_pointer_cast<SpriteBase>(obj)->component(0)->getPosition().x << "," << std::dynamic_pointer_cast<SpriteBase>(obj)->component(0)->getPosition().y << endl;
            logger("touch") << dir.x <<"," << dir.y << endl;
            std::dynamic_pointer_cast<SpriteBase>(obj)->each_component(&SpriteComponent::apply_linear_impulse, ccpMult( dir,5));
        }
    }
                   );
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
GTS_NS_END
