//
//  CGInstanceIOS.cpp
//  Game
//
//  Created by dongli on 2016/10/26.
//
//

#include "CGInstanceIOS.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "CGDataType.h"
#include "CGScene.hpp"
using namespace cocos2d;
static cocos2d::Size designResolutionSize = cocos2d::Size(1334, 750);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);


static CGInstanceIOS * g_pGameInstance = NULL;

CGInstanceIOS * CGInstanceIOS::sharedInstanceIOS()
{
    if(g_pGameInstance == NULL)
    {
        g_pGameInstance = new CGInstanceIOS();
        
        if(g_pGameInstance != NULL)
        {
            g_pGameInstance->InitGameInstance();
            return g_pGameInstance;
        }
        else
        {
            std::cout<<"CGInstance Create Is Error"<<std::endl;
            return NULL;
        }
    }
    return g_pGameInstance;
}

bool CGInstanceIOS::InitGameInstance()
{
    m_iGameStateValue = GAME_STATE_LOGO;
    return true;
}

bool CGInstanceIOS::DeleteGameInstance()
{
    delete this;
    return true;
}

bool CGInstanceIOS::InitGameSetting()
{
    
    Director * t_pDirector = Director::getInstance();
    GLView   * t_pView     = t_pDirector->getOpenGLView();
    GLView   * t_pView1;
    if(!t_pView)
    {
        #if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        t_pView = GLViewImpl::createWithRect("Game", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
        #else
        t_pView1 = GLViewImpl::create("Game");
        #endif
        t_pDirector->setOpenGLView(t_pView1);

    }
    
    t_pDirector->setDisplayStats(true);
    t_pDirector->setAnimationInterval(GAME_INTERVAL);
    t_pView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    Size t_FrameSize = t_pView->getFrameSize();
    
    // if the frame's height is larger than the height of medium size.
    if (t_FrameSize.height > mediumResolutionSize.height)
    {
        t_pDirector->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (t_FrameSize.height > smallResolutionSize.height)
    {
        t_pDirector->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {
        t_pDirector->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
    
    
}

bool CGInstanceIOS::StartRunGame()
{
    Director * director = Director::getInstance();
    
    auto scene = CGScene::GetCocosSecene();
    
    // run
    director->runWithScene(scene);

}
