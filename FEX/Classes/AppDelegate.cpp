//
//  FEXAppDelegate.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "FE.h"
#include "GameBase.h"
#include "GameScene.h"
#include "FEUtility.h"
#include "ResourceManager.h"
#include "SpriteBase.h"
#include "GameLayer.h"
#include "cocos-ext.h"
#include "GLES-Render.h"
#include "CCPhyDebugNode.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace FESimple;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}


template <typename T> class Proxy
{
public:
    Proxy(T &o): o_(o) {}
    
    template <typename A, typename B,
    typename std::enable_if<std::is_convertible<B, A>::value>::type* = nullptr>
    void call(void (T::*f)(A), B&& a)
    {
        (o_.*f)(std::forward<B>(a));
    }

private:
    T &o_;
};

class hello
{
public:
    void f( const CCPoint& a)
    {
        cout <<"f";
    };
};


template <typename T, typename R, typename ...Args>
R proxycall(T & obj, R (T::*mf)(Args...), Args &&... args)
{
    return (obj.*mf)(std::forward<Args>(args)...);
}

template <typename T, typename R, typename A, typename B>
//typename std::enable_if<std::is_convertible<B, A>::value>::type* = nullptr>
R call(T & obj, R (T::*mf)(A),B&& a)
{
    return (obj.*mf)((A)a );
}

bool AppDelegate::applicationDidFinishLaunching()
{
    hello h;
    Proxy<hello> p(h);
    p.call(&hello::f, CCPoint(0,0));
    call( h, &hello::f, CCPoint(0,0));
    
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    GameBase* game = get_game();
    
    GLESDebugDraw* phydbg = new GLESDebugDraw( ptm_ratio() );
    phydbg->SetFlags(0xffffffff);
    
    game->get_phy_world()->SetDebugDraw( phydbg );
    pDirector->runWithScene( game->get_scene()->ccscene() );

    //std::vector<std::string> paths = {CCFileUtils::sharedFileUtils()->getWritablePath().c_str()};

    //CCFileUtils::sharedFileUtils()->setSearchPaths(paths);
    

    
    ResourceManager::instance()->load_sprite_component_desc(full_path("sprite_components/base.xml"));
    ResourceManager::instance()->load_sprite_desc(full_path("sprites/base.xml"));
    ResourceManager::instance()->load_physic_desc(full_path("pdb/main.xml"));
    game->add_game_object( GameObjPtr(new GameLayer()), "root");
    
//

    int i = 50;
    while(i-- > 0)
    {
    game->add_game_object( GameObjFactory::construct_obj("SpriteBase", SpawnParams({{"init_location","500,500"},{"sprite_desc","hero"}})), "root" );
    }

    CCPhyDebugNode* dbgnode = new CCPhyDebugNode();
    dbgnode->autorelease();
    
    //hero->each_component( &SpriteComponent::set_linear_velocity, CCPoint(50,0) );
    
    game->get_scene()->get_layer("root")->cclayer()->addChild( dbgnode, 1000 );
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
