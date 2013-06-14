//
//  GameLayer.h
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#ifndef __FEX__GameLayer__
#define __FEX__GameLayer__
#include "FE.h"
#include "cocos2d.h"
#include "GameObjBase.h"
FE_NS_BEGIN
class GameWorld;
class GameBase;
class GameLayer :public GameObjBase
{
public:
    

    //triggers
    virtual void added_to_game( GameBase* game );
    virtual void removed_from_game( GameBase* game );
    
    cocos2d::CCLayer* cclayer()
    {
        return m_layer;
    }
private:
    cocos2d::CCLayer*       m_layer;
};
FE_NS_END

#endif /* defined(__FEX__GameLayer__) */
