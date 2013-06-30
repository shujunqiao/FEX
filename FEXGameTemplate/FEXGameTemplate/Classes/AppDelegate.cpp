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
#include "FEUtility.h"
#include "GameBase.h"
#include "GameScene.h"
#include "FEUtility.h"
#include "ResourceManager.h"
#include "SpriteBase.h"
#include "GameLayer.h"
#include "cocos-ext.h"
#include "GLES-Render.h"
#include "CCPhyDebugNode.h"
#include "GameTheSoldiers.h"
#include "Python.h"


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

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    GameTheSoldiers* game = new GameTheSoldiers();
    set_game( game );
    GLESDebugDraw* phydbg = new GLESDebugDraw( ptm_ratio() );
    phydbg->SetFlags(0);
    
   // game->get_phy_world()->SetDebugDraw( phydbg );
    pDirector->runWithScene( game->get_scene()->ccscene() );

    //std::vector<std::string> paths = {CCFileUtils::sharedFileUtils()->getWritablePath().c_str()};

    //CCFileUtils::sharedFileUtils()->setSearchPaths(paths);
    
    ResourceManager::instance()->load_sprite_component_desc(full_path("sprite_components/base.xml"));
    ResourceManager::instance()->load_sprite_desc(full_path("sprites/base.xml"));
    ResourceManager::instance()->load_physic_desc(full_path("pdb/main.xml"));
    //game->add_game_object( GameObjPtr(new GameLayer()), "root");

    char pypath[1024];
    strcpy(pypath, full_path("python").c_str());

 
    Py_SetPythonHome(pypath);

    Py_Initialize();
    PyRun_SimpleString("print 'nimei'");
    Py_Finalize();
    
    int i = 50;
    while(i-->0)
    {
    game->add_game_object( GameObjFactory::construct_obj("SpriteBase", SpawnParams({{"init_location","500,500"},{"sprite_desc","pickup_s_gun"}})), "root" );
    }

    //CCPhyDebugNode* dbgnode = new CCPhyDebugNode();
    //dbgnode->autorelease();
    
    //hero->each_component( &SpriteComponent::set_linear_velocity, CCPoint(50,0) );
    
    //game->get_scene()->get_layer("root")->cclayer()->addChild( dbgnode, 1000 );
    
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
