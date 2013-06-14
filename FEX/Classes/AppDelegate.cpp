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
USING_NS_CC;
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

    
    GameBase* game = new GameBase();
    pDirector->runWithScene( game->scene()->ccscene() );

    //std::vector<std::string> paths = {CCFileUtils::sharedFileUtils()->getWritablePath().c_str()};

    //CCFileUtils::sharedFileUtils()->setSearchPaths(paths);
    

    
    ResourceManager::load_sprite_component_desc(full_path("sprite_components/base.xml"));
    //ResourceManager::load_sprite_desc(full_path("sprites/base.xml"));
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
