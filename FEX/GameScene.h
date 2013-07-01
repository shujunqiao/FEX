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
#include "FEUtility.h"
#include "GameBase.h"
FE_NS_BEGIN
class GameLayer;

class MyScene : public cocos2d::CCScene
{
public:
    void update( float delta_time )
    {
        get_game()->update(delta_time);
        cocos2d::CCScene::update( delta_time );
    }
};

class GameScene :public GameObjBase
{
public:
    
    DECLARE_CLASS_INFO(GameScene)
    GameScene();
    GameScene( const SpawnParams& param);
    ~GameScene();
    
    //layers
    GameLayer* get_layer( std::string name );
    void add_layer( GameLayer* layer, const Name& name );
    void remove_layer( GameLayer* layer );
    void remove_all_layers();
    
    operator cocos2d::CCScene*()
    {
        return ccscene();
    }
    cocos2d::CCScene* ccscene()
    {
        return scene;
    }
    
private:
    MyScene*                scene;
    std::list<GameLayer*>   layers;
};
FE_NS_END
#endif /* defined(__FEX__GameScene__) */
