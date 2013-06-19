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

bool AppDelegate::applicationDidFinishLaunching()
{
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
    SpriteBase* hero;
    game->add_game_object( GameObjPtr(hero = new SpriteBase(ResourceManager::instance()->sprite_descs.item("hero"))), "root" );
    hero->set_position(CCPoint(512,512));
    CCPhyDebugNode* dbgnode = new CCPhyDebugNode();
    dbgnode->autorelease();

    game->get_scene()->get_layer("root")->cclayer()->addChild( dbgnode, 1000 );
    //ResourceManager::load_physic_desc(full_path("pdb/main.xml"));
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
