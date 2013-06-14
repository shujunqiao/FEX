//
//  GameScene.h
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//

#ifndef __FEX__GameScene__
#define __FEX__GameScene__
#include "FE.h"
#include "cocos2d.h"
#include "GameObjBase.h"
FE_NS_BEGIN
class GameLayer;
class GameScene :public GameObjBase
{
public:
    GameScene();
    ~GameScene();
    
    //layers
    GameLayer* get_layer( std::string name );
    void add_layer( GameLayer* layer, std::string name );
    void remove_all_layers();
    
    operator cocos2d::CCScene*()
    {
        return ccscene();
    }
    cocos2d::CCScene* ccscene()
    {
        return m_scene;
    }
    
    
private:
    cocos2d::CCScene*       m_scene;
    std::list<GameLayer*>   m_layers;
};
FE_NS_END
#endif /* defined(__FEX__GameScene__) */
