//
//  CGScene.cpp
//  Game
//
//  Created by dongli on 2016/10/27.
//
//

#include "CGScene.hpp"
#include <iostream>
#include "cocos2d.h"
#include <pthread.h>
#include "CGRequest.hpp"
#include "CGDataType.h"
#include "CGProtocolManager.hpp"
#include <Box2D/Box2D.h>
#include "CGAnimateManger.hpp"
#include "CGResManager.hpp"
#include "CGPlayer.hpp"
#include "CGUIManager.hpp"
#include "CGButton.hpp"
#include "CGException.hpp"
#include "CGJoyStick.hpp"
#include "CGPowerButton.hpp"
#include "CGBullet.hpp"
#include "CGPlayerManager.hpp"
#include "CGWeaponManager.hpp"
#include "CGMapManager.hpp"
#include "CGMapScene.hpp"
#include "CGDamegeSystem.hpp"
#include "CGPhysicsManager.hpp"
#include "CGStateSystem.hpp"
#include "CGPirateSoldier.hpp"
using namespace cocos2d;

static CGScene * g_pGScene = NULL;

CGScene * GetGScene()
{
    return g_pGScene;
}


ULONG GetTouchOnlyCount()
{
    static ULONG lOnlyCount = 1;
    
    if( lOnlyCount > MAX_COUNT )
    {
        lOnlyCount = 1;
    }
    
    lOnlyCount ++;
    
    return lOnlyCount;
}

CGScene * CGScene::CreateGScene()
{
    CGScene * t_pScene = new CGScene();
    
    if(t_pScene != NULL)
    {
        std::cout<<"CGScene Is Create "<<std::endl;
        g_pGScene = t_pScene;
        if(t_pScene->init())
        {
            t_pScene->autorelease();
            return t_pScene;
        }
    }
    else
    {
        std::cout<<"CGScene create error"<<std::endl;
        return nullptr;
    }
    return t_pScene;
}

cocos2d::Scene * CGScene::GetCocosSecene()
{
    cocos2d::Scene * t_pScene = cocos2d::Scene::create();
    
    if(t_pScene != nullptr)
    {
        auto t_pGScene = CGScene::CreateGScene();
        t_pScene->addChild(t_pGScene);
        return t_pScene;
    }
    else
    {
        return nullptr;
    }
}

bool CGScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    m_iGameState    = GAME_STATE_LOGO;
    m_bFirstLogic   = false;
    m_bCanPhysics   = true;
    m_iTouchCount   = 0;
    m_pFarLayer     = Layer::create();
    m_pNearLayer    = Layer::create();
    
    m_pFarLayer->setLocalZOrder(10);
    m_pNearLayer->setLocalZOrder(15);
    
    addChild(m_pFarLayer);
    addChild(m_pNearLayer);
    
    
    m_pSocket = CGSocket::CreateGSocket(SOCKET_TYPE_TCP);
    
    auto Listenr = EventListenerTouchOneByOne::create();
    
    Listenr->onTouchBegan = CC_CALLBACK_2(CGScene::OnTouchBegan, this);
    Listenr->onTouchEnded = CC_CALLBACK_2(CGScene::OnTouchEnd, this);
    Listenr->onTouchMoved = CC_CALLBACK_2(CGScene::OnTouchMoved, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(Listenr, this);
    
    try
    {
        auto t_pAnimate = CGAnimateManager::sharedAnimateManager();
        auto t_pRes     = CGResManager::sharedResManager();

        t_pAnimate->EnumXMLFolder();
        t_pAnimate->AnalysisXML();
        t_pRes->AutoLoadAnimationPath();
    }
    catch(CGException& exp)
    {
        exp.PrintError();
    }
    
    b2Vec2 Gravity(0.0f, -100.0f);
    m_pWorld = new b2World(Gravity);
    
    
    /*
    b2Vec2 gravity(0.0f, -10.0f);
    b2World world(gravity);
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    b2PolygonShape groundBox; groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody; bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox; dynamicBox.SetAsBox(1.0f, 1.0f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    
    for (int32 i = 0; i < 60; ++i) {
        world.Step(timeStep, velocityIterations, positionIterations); b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    }
    
    b2Vec2 gravity(0.0f, -10.0f);

    b2World word(gravity);
    
    m_GroundDef.position.Set(10.f, -10.f);
    m_GroundShape.SetAsBox(50.f, 50.f);
    m_pGroundBody = word.CreateBody(&m_GroundDef);
    m_pGroundBody->CreateFixture(&m_GroundShape, 0.f);
    
    m_BodyShape.SetAsBox(100.0f, 100.0f);
    m_BodyDef.position.Set(500.0f, 500.0f);
    m_BodyDef.type = b2_dynamicBody;
    m_pBody = word.CreateBody(&m_BodyDef);
    m_FixtureDef.density = 1.0f;
    m_FixtureDef.friction = 0.1f;
    m_FixtureDef.shape = &m_BodyShape;
    m_pBody->CreateFixture(&m_FixtureDef);
    */
    
    schedule(schedule_selector(CGScene::RunGameWithFrame));
    
    
    
    return true;
    
    
}

void CGScene::OnTouchEnd(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    auto t_TouchPoint = pTouch->getLocation();
    auto t_pUIManager = CGUIManager::sharedUIManager();
    
    auto t_iTouchID   = pTouch->getID();
    
    t_pUIManager->SetEndPointByID(t_iTouchID, t_TouchPoint);
    
    //CG_DEBUG_PRINT_1("End ID: ", pTouch->getID());

}

bool CGScene::OnTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    STRUCT_TOUCH_INFO TouchInfo;
    
    auto t_pUIManager     = CGUIManager::sharedUIManager();
    auto t_Touch          = pTouch->getLocation();
    
    TouchInfo.uTouchID    = pTouch->getID();
    TouchInfo.uOnlyCount  = GetTouchOnlyCount();
    TouchInfo.BeganPoint  = t_Touch;
    TouchInfo.MovePoint   = Point(0,0);
    TouchInfo.EndPoint    = Point(0,0);
    TouchInfo.bIsEnd      = false;

    t_pUIManager->PushTouchInfo(TouchInfo);
    
    //CG_DEBUG_PRINT_1("Began ID: ", pTouch->getID());
    
    return true;
}

void CGScene::OnTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    auto t_pUIManager = CGUIManager::sharedUIManager();
    auto t_Touch      = pTouch->getLocation();

    auto t_iID        = pTouch->getID();
    
    t_pUIManager->SetMovePointByID(t_iID, t_Touch);
    
    
    //CG_DEBUG_PRINT_1("Move ID: ", pTouch->getID());

}

void * CGScene::SendProtocolThread(void *)
{
    std::cout<<"SendThread is began"<<std::endl;
    
    auto t_pProtocol = CGProtocolManager::sharedProtocolManager();
    
    t_pProtocol->SendProtocolThread();
    
    return 0;
}




void CGScene::RunGameWithFrame(float f)
{
    
    switch(m_iGameState)
    {
        case GAME_STATE_LOGO:
            OnGameLogo();
            break;
        case GAME_STATE_MAIN:
            OnGameMain();
            break;
        case GAME_STATE_LOGIC:
            OnGameLogic();
            break;
        default:
            break;
    }
}

void CGScene::OnGameLogo()
{
    m_iGameState = GAME_STATE_MAIN;
}

void CGScene::OnGameMain()
{
    m_iGameState = GAME_STATE_LOGIC;
    
    //CGUIManager::sharedUIManager()->ProcessUITask();

    
}

b2Body * CGScene::CreateStaticBody(float fWidth, float fHeight, const Point &Position)
{
    b2BodyDef       t_BodyDef;
    b2PolygonShape  t_BodyShape;
    b2FixtureDef    t_BodyFixture;

    t_BodyDef.position.Set(Position.x / PHYSICS_SCALE, Position.y / PHYSICS_SCALE);
    t_BodyShape.SetAsBox(fWidth / PHYSICS_SCALE, fHeight / PHYSICS_SCALE);

    t_BodyDef.type            = b2_staticBody;
    t_BodyFixture.density     = 0;
    t_BodyFixture.friction    = 0;
    t_BodyFixture.restitution = 0.1f;

    t_BodyFixture.shape       = & t_BodyShape;
    
    b2Body * t_pBody          = m_pWorld->CreateBody(&t_BodyDef);
    
    t_pBody->CreateFixture(&t_BodyFixture);
    
    return t_pBody;
}

b2Body * CGScene::CreatePhysicsBody(float iWidth, float iHeight, const Point &Position,float fDensity,float fFriction)
{
    b2BodyDef       t_BodyDef;
    b2PolygonShape  t_BodyShape;
    b2FixtureDef    t_BodyFixture;
    
    t_BodyShape.SetAsBox(iWidth / PHYSICS_SCALE, iHeight / PHYSICS_SCALE);
    t_BodyDef.position.Set(Position.x / PHYSICS_SCALE, Position.y / PHYSICS_SCALE);

    t_BodyDef.type            = b2_dynamicBody;
    t_BodyFixture.density     = fDensity;
    t_BodyFixture.friction    = fFriction;
    t_BodyFixture.shape       = & t_BodyShape;
    t_BodyFixture.restitution = 0.1f;
    b2Body * t_pBody       = m_pWorld->CreateBody(&t_BodyDef);
    
    t_pBody->CreateFixture(&t_BodyFixture);
    
    return t_pBody;
    
}
ProgressTimer * timer;
CGPirateSoldier * soldier;

void CGScene::OnGameLogic()
{
   
    if( m_bFirstLogic == false )
    {
        m_bFirstLogic  = true;
        
        m_pPlayer      = CGPlayerManager::sharedPlayerManager();
        m_pWeapon      = CGWeaponManager::sharedWeaponManager();
        m_pRes         = CGResManager::sharedResManager();
        m_pUI          = CGUIManager::sharedUIManager();
        m_pProtocol    = CGProtocolManager::sharedProtocolManager();
        m_pMap         = CGMapManager::sharedMapManager();
        m_pDamege      = CGDamegeSystem::sharedDamegeSystem();
        m_pPhysics     = CGPhysicsManager::sharedPhysicsManager();
        
        auto * button  = CGPowerButton::CreatePowerButton(BUTTON_TYPE_POWER);
        auto * button1 = CGPowerButton::CreatePowerButton(BUTTON_TYPE_POWER);

        int iWidth     = m_pRes->GetUISizeByName(UI_SIZE_POWER_WIDTH);
        int iHeight    = m_pRes->GetUISizeByName(UI_SIZE_POWER_HEIGHT);
        int iScreenW   = m_pRes->GetUISizeByName(UI_SIZE_SCREEN_WIDTH);
        int iScreenH   = m_pRes->GetUISizeByName(UI_SIZE_SCREEN_HEIGHT);
        
        button->SetObjectPosition(iScreenW - iWidth, iHeight);
        button1->SetObjectPosition(1000, 100);
        button1->SetUIName(UI_ONLY_ID_BULLET);
    
        m_pUI->AddUIToList(button1);
        m_pUI->AddUIToList(button);
        
        
        auto map = CGMapScene::CreateMapScene("Map1");
        
        m_pMap->AddMapSceneToList(map);

        
        CGPlayer * player  = CGPlayer::CreatePlayer("RedAir", PLAYER_TYPE_LOCAL,iScreenW / 2,iScreenH / 2);
        
        m_pPlayer->AddLocalPlayerToList(player);

        
        CGJoyStick * joystick = CGJoyStick::CreateJoyStick(JOYSTICK_TYPE_NORMAL);
        
        m_pUI->AddUIToList(joystick);
        
        CGStateSystem * state = CGStateSystem::CreateStateSystem();
        m_pUI->AddUIToList(state);
        
        auto lift = Sprite::create("UIRes/ShengMing_Normal.png");
        auto temp = Sprite::create("UIRes/WenDu_Normal.png");
        auto arm  = Sprite::create("UIRes/ZhuangJia_Normal.png");
        
        //lift->setPosition(167,iScreenH - 30);
        arm->setPosition(170,iScreenH - 73);
        temp->setPosition(170,iScreenH - 113);
        
        auto to   = ProgressTo::create(0.25, 10);
        auto to1  = ProgressFromTo::create(0.5, 50, 30);
        timer = ProgressTimer::create(lift);
        
        timer->setPosition(167,iScreenH - 30);
        timer->setPercentage(0);
        timer->setType(ProgressTimer::Type::BAR);
        timer->setMidpoint(Point(0,0));
        timer->setBarChangeRate(Point(1,0));
        //timer->runAction(to);
        //time->runAction(to1);
        //addChild(timer,DEEP_UI_NUMBER);
        //addChild(lift,DEEP_UI_NUMBER);
        //addChild(temp,DEEP_UI_NUMBER);
        //addChild(arm,DEEP_UI_NUMBER);

        soldier = CGPirateSoldier::CreatePirateSoldier("XiaoBing");
        soldier->SetObjectPosition(1000, 600);
    }

    
    
    
    static ULONG t_iTime     = GetMilliSecond();
    static bool  t_bCanTouch = true;
    
    if( m_pUI->GetLunchButtonIsTouch() )
    {
        
        if( GetMilliSecond() - t_iTime > 500)
        {
            t_bCanTouch = true;
        }

        if( t_bCanTouch )
        {
            CGPlayerDateManager::sharedPlayerDateManager()->ReducePlayerLife(5);
            CGPlayerDateManager::sharedPlayerDateManager()->ReducePlayerArmor(5);
            int t_iRandX = rand() % 300;
            
            if( t_iRandX < 150 )
            {
                CGDamegeSystem::sharedDamegeSystem()->ShowDamegeNumber(999, NUMBER_TYPE_NORMAL_DAMEGE, ccp(500+t_iRandX,500));
            }
            
            else
            {
                CGDamegeSystem::sharedDamegeSystem()->ShowDamegeNumber(999, NUMBER_TYPE_CRUSH_DAMEGE, ccp(500+t_iRandX,500));
            }
            t_bCanTouch = false;
            
            t_iTime     = GetMilliSecond();
            

        }
    }
    
    
    soldier->DrawGObject();

    m_pUI->ProcessUITask();
    m_pPlayer->ProcessPlayerTask();
    m_pWeapon->ProcessWeaponTask();
    m_pProtocol->ProcessProtocolPakcet();
    m_pMap->ProcessMapScene();
    CGDamegeSystem::sharedDamegeSystem()->ProcessDamegeTask();
    CGPhysicsManager::sharedPhysicsManager()->ProcessPhysicsTask();
}



