//
//  CGPlayer.cpp
//  Game
//
//  Created by dongli on 2016/11/1.
//
//

#include "CGPlayer.hpp"
#include "CGAnimateManger.hpp"
#include "CGResManager.hpp"
#include "CGDataType.h"
#include "CGScene.hpp"
#include "CGException.hpp"
#include "CGUIManager.hpp"
#include "CGProtocolManager.hpp"
#include "CGPlayerDateManager.hpp"
#include "CGMapScene.hpp"
#include "CGRequest.hpp"
#include "CGMapManager.hpp"
#include "CGPhysicsManager.hpp"
#include "CGPhysicsObject.hpp"
extern CGScene * GetGScene();


CGPlayer * CGPlayer::CreatePlayer(const std::string &sPlayer, unsigned int iType, float fx, float fy)
{
    
    auto t_pObject = new CGPlayer(sPlayer, iType,fx,fy);
    
    if( t_pObject == nullptr )
    {
        std::cout<<"CGPlayer Is Create Error, ID: "<<sPlayer<<std::endl;
        throw CGException("CreatePlayer Is Error");
        return nullptr;
    }
    else
    {
        t_pObject->InitGObject();
        return t_pObject;
    }
}

CGPlayer * CGPlayer::CreatePlayer(const std::string &sPlayer, UINT uType)
{
    return 0;
}

void CGPlayer::SetObjectPosition(float x, float y)
{
    m_fLastX = x / 10;
    m_fLastY = y / 10;
    //m_pPhysicsBody->SetTransform(b2Vec2(x / PHYSICS_SCALE,y / PHYSICS_SCALE), 0);
    m_ObjectPosition.x = x;
    m_ObjectPosition.y = y;
}

const Point & CGPlayer::GetObjectPosition()const
{
    return m_ObjectPosition;
}

void CGPlayer::SetObjectPosition(const Point &Postion)
{
    //m_pPhysicsBody->SetTransform(b2Vec2(Postion.x / PHYSICS_SCALE,Postion.y / PHYSICS_SCALE), 0);
    m_ObjectPosition = Postion;
}

bool CGPlayer::InitGObject()
{
    m_pGameScene                        = GetGScene();
    m_pPhysicsManager                   = CGPhysicsManager::sharedPhysicsManager();
    m_pDate                             = CGPlayerDateManager::sharedPlayerDateManager();
    m_pAnimateManaget                   = CGAnimateManager::sharedAnimateManager();
    m_pUI                               = CGUIManager::sharedUIManager();
    m_pRes                              = CGResManager::sharedResManager();
    m_pFrameCache                       = SpriteFrameCache::getInstance();
    m_pPlayerSprite                     = Sprite::create("RedAir_Move_0.png");
    
    m_iPlayerOrientation                = PLAYER_ORIENTATION_LEFT;
    m_iLastState                        = ANIMATION_STATE_MOVE;
    m_iAnimationState                   = ANIMATION_STATE_STAND;
    m_bStateSwitch                      = false;
    m_bCallDie                          = false;
    m_bPlayerDead                       = false;
    m_bPlayerHide                       = false;
    m_bOpenPhysics                      = false;
    
    m_iMoveSpeed                        = 5;
    m_fLastX                            = 0;
    m_fLastY                            = 0;
    m_iBuoyancy                         = 0;
    
    m_iScreenHeight                     = m_pRes->GetUISizeByName(UI_SIZE_SCREEN_HEIGHT);
    m_iScreenWidth                      = m_pRes->GetUISizeByName(UI_SIZE_SCREEN_WIDTH);
    m_CenterPoint                       = Point(m_iScreenWidth / 2, m_iScreenHeight / 2);
    m_ScreenPoint                       = Point(m_iScreenWidth / 2, m_iScreenHeight / 2);
    m_iBodyWidth                        = m_pRes->GetShipWidth(m_sTextureID);
    m_iBodyHeight                       = m_pRes->GetShipHeight(m_sTextureID);
    m_pPhysicsObject                    = CGPhysicsObject::CreatePhysicsObject(PHYSICS_TYPE_DYNAMIC, 100, 100, m_ObjectPosition.x, m_ObjectPosition.y);
    
    m_pPhysicsManager->AddPhysicsObjectToList(m_pPhysicsObject);
    
    if( m_uPlayerType == PLAYER_TYPE_LOCAL )
    {
        

    }
    
    if( m_uPlayerType == PLAYER_TYPE_NET )
    {
        
    }
    
    if( m_uPlayerType == PLAYER_TYPE_AI )
    {
        
    }
    
    m_pPlayerSprite->setPosition(m_ObjectPosition);

    auto FlagVec        = m_pAnimateManaget->GetFlagStructVecByID(m_sTextureID);
    auto Animate        = m_pAnimateManaget->GetAnimateStructByID(m_sTextureID);
    bool t_bIsLoadPlist = m_pFrameCache->isSpriteFramesWithFileLoaded("AnimationRes/" + Animate.sPlistName);
    
    if( t_bIsLoadPlist == false)
    {
        std::cout<<"Plist Is Not Load"<<std::endl;
        
        auto pRes            = CGResManager::sharedResManager();
        std::string sPath    = pRes->GetAnimationPath();
        std::string t_sPlist = sPath + Animate.sPlistName;
        
        m_pFrameCache->addSpriteFramesWithFile(t_sPlist);
    }
    else
    {
        m_iAnimateNumber = FlagVec.size();
        for(int i = 0; i != m_iAnimateNumber; i++)
        {
            std::string t_sFlag     = FlagVec[i].m_sFlagsName;
            std::string t_sFront    = Animate.sObjectName;
            int t_iFrameCount       = FlagVec[i].m_iFrameCount;
            
            Vector<SpriteFrame *> t_pArray;
            
            for(int i = 0; i != t_iFrameCount; i++)
            {
                char t_sNumer[10];
                
                sprintf(t_sNumer, "%d", i);
                
                std::string t_sFrame;
                
                if(t_iFrameCount < 10)
                {
                    t_sFrame  = t_sFront + "_" + t_sFlag + "-0" + t_sNumer + ".png";
                }
                else
                {
                    t_sFrame  = t_sFront + "_" + t_sFlag + "-" + t_sNumer + ".png";
                }
                
                auto t_pFrame = m_pFrameCache->getSpriteFrameByName(t_sFrame);
                
                t_pArray.pushBack(t_pFrame);
                
                std::cout<<"FrameName: "<<t_sFrame<<std::endl;
                
            }
            if( t_sFlag == "Move" )
            {
                auto t_pAnimation = Animation::createWithSpriteFrames(t_pArray);
                
                t_pAnimation->setLoops(ANIMATION_LOOP_INFINTE);
                t_pAnimation->setDelayPerUnit(ANIMATION_DELAY_DEFAULT);
                
                m_pMoveAnimate = Animate::create(t_pAnimation);
                
                m_pMoveAnimate->retain();
                
            }
            if( t_sFlag == "Die" )
            {
                auto t_pAnimation = Animation::createWithSpriteFrames(t_pArray);
                
                t_pAnimation->setLoops(ANIMATION_LOOP_ONECE);
                t_pAnimation->setDelayPerUnit(ANIMATION_DELAY_DEFAULT);
                
                m_pDieAnimate = Animate::create(t_pAnimation);
                m_pDieAnimate->retain();
                
                auto t_pCall    = CallFunc::create(CC_CALLBACK_0(CGPlayer::DieCallBack, this));
                m_pDieSequnce   = Sequence::create(m_pDieAnimate, t_pCall, NULL);
                m_pDieSequnce->retain();
                
            }
            if( t_sFlag == "Stand" )
            {
                auto t_pAnimation = Animation::createWithSpriteFrames(t_pArray);
                
                t_pAnimation->setLoops(ANIMATION_LOOP_INFINTE);
                t_pAnimation->setDelayPerUnit(ANIMATION_DELAY_DEFAULT);
                
                m_pStandAnimate = Animate::create(t_pAnimation);
                m_pStandAnimate->retain();
                
            }
            if( t_sFlag == "Hit" )
            {
                auto t_pAnimation = Animation::createWithSpriteFrames(t_pArray);
                
                t_pAnimation->setLoops(ANIMATION_LOOP_ONECE);
                t_pAnimation->setDelayPerUnit(ANIMATION_DELAY_DEFAULT);
                
                m_pHitAnimate = Animate::create(t_pAnimation);
                m_pHitAnimate->retain();
                
            }
            if( t_sFlag == "Attack" )
            {
                auto t_pAnimation = Animation::createWithSpriteFrames(t_pArray);
                
                t_pAnimation->setLoops(ANIMATION_LOOP_ONECE);
                t_pAnimation->setDelayPerUnit(ANIMATION_DELAY_DEFAULT);
                
                m_pAttackAnimate = Animate::create(t_pAnimation);
                m_pAttackAnimate->retain();
            }
        }
    }

    auto t_pMap               = CGMapManager::sharedMapManager();
    
    m_RightUp_RightDownPoint  = t_pMap->GetFarRectZeroPoint(RECT_ID_RIGHT_UP__RIGHT_DOWN);
    m_LeftDownZeroPoint       = t_pMap->GetFarRectZeroPoint(RECT_ID_LEFT_DOWN__LEFT_DOWN);
    m_LeftUpZeroPoint         = t_pMap->GetFarRectZeroPoint(RECT_ID_LEFT_UP__LEFT_UP);
    m_RightUpZeroPoint        = t_pMap->GetFarRectZeroPoint(RECT_ID_RIGHT_UP__RIGHT_UP);
    m_UpPoint                 = t_pMap->GetFarRectZeroPoint(RECT_ID_UP);
    m_RightPoint              = t_pMap->GetFarRectZeroPoint(RECT_ID_RIGHT);
    m_RightDownZeroPoint      = t_pMap->GetFarRectZeroPoint(RECT_ID_RIGHT_DOWN__RIGHT_DOWN);
    m_RightUp_LeftUpPoint     = t_pMap->GetFarRectZeroPoint(RECT_ID_RIGHT_UP__LEFT_UP);
    m_LeftUp_RightUpPoint     = t_pMap->GetFarRectZeroPoint(RECT_ID_LEFT_UP__RIGHT_UP);
    m_LeftUp_LeftDownPoint    = t_pMap->GetFarRectZeroPoint(RECT_ID_LEFT_UP__LEFT_DOWN);
    m_RightDown_RightUpPoint  = t_pMap->GetFarRectZeroPoint(RECT_ID_RIGHT_DOWN__RIGHT_UP);
    m_RightDown_LeftDownPoint = t_pMap->GetFarRectZeroPoint(RECT_ID_RIGHT_DOWN__LEFT_DOWN);
    
    int t_iWidth  = t_pMap->GetMapScene()->GetMapWidth();
    int t_iHeight = t_pMap->GetMapScene()->GetMapHeight();
    
    m_SceneRect.setRect(0, 0, t_iWidth, t_iHeight);
    
    return true;
}

void CGPlayer::ProcessScreenPoint()
{
    CGMapScene * t_pMapScene           = CGMapManager::sharedMapManager()->GetMapScene();
    
    std::list<STRUCT_FARRECT> RectList = t_pMapScene->GetFarRectList();
    
    int t_iInAnyRect                   = t_pMapScene->GetPlayerInAnyRect(m_ObjectPosition);
    
    switch(t_iInAnyRect)
    {
        case RECT_ID_LEFT_DOWN__LEFT_DOWN:
        {
            m_ScreenPoint = m_ObjectPosition;
            break;
        }
            
        case RECT_ID_LEFT_DOWN__LEFT_UP:
        {
            m_ScreenPoint.x = m_ObjectPosition.x;
            m_ScreenPoint.y = m_CenterPoint.y;
            break;
        }
            
        case RECT_ID_LEFT_DOWN__RIGHT_DOWN:
        {
            m_ScreenPoint.x = m_CenterPoint.x;
            m_ScreenPoint.y = m_ObjectPosition.y;
            break;
        }
        
        case RECT_ID_UP:
        {
            m_ScreenPoint.x = m_CenterPoint.x;
            m_ScreenPoint.y = m_CenterPoint.y + (m_ObjectPosition.y - m_UpPoint.y);
            break;
        }
        case RECT_ID_LEFT:
        {
            m_ScreenPoint.x = m_ObjectPosition.x;
            m_ScreenPoint.y = m_CenterPoint.y;
            break;
        }
        
        case RECT_ID_RIGHT:
        {
            m_ScreenPoint.x = m_CenterPoint.x + ( m_ObjectPosition.x - m_RightPoint.x);
            m_ScreenPoint.y = m_CenterPoint.y;
            break;
        }
        
        case RECT_ID_DOWN:
        {
            m_ScreenPoint.x = m_CenterPoint.x;
            m_ScreenPoint.y = m_ObjectPosition.y;
            break;
        }
            
        case RECT_ID_CENTER:
        {
            m_ScreenPoint= m_CenterPoint;
            
            break;
        }
        case RECT_ID_LEFT_UP__LEFT_DOWN:
        {
            m_ScreenPoint.x = m_ObjectPosition.x;
            m_ScreenPoint.y = m_CenterPoint.y;
            break;
        }
            
        case RECT_ID_LEFT_UP__LEFT_UP:
        {
            m_ScreenPoint.x = m_ObjectPosition.x;
            m_ScreenPoint.y = m_CenterPoint.y + (m_ObjectPosition.y - m_LeftUpZeroPoint.y);
            break;
        }
            
        case RECT_ID_LEFT_UP__RIGHT_UP:
        {
            m_ScreenPoint.x = m_CenterPoint.x;
            m_ScreenPoint.y = m_CenterPoint.y + (m_ObjectPosition.y - m_LeftUp_RightUpPoint.y);
            break;
        }
            
        case RECT_ID_RIGHT_UP__RIGHT_DOWN:
        {
            m_ScreenPoint.x = m_CenterPoint.x + (m_ObjectPosition.x - m_RightUp_RightDownPoint.x);
            m_ScreenPoint.y = m_CenterPoint.y;
            break;
        }
    
        case RECT_ID_RIGHT_UP__RIGHT_UP:
        {
            m_ScreenPoint.x = m_CenterPoint.x + (m_ObjectPosition.x - m_RightUpZeroPoint.x);
            m_ScreenPoint.y = m_CenterPoint.y + (m_ObjectPosition.y - m_RightUpZeroPoint.y);
            break;
        }
            
        case RECT_ID_RIGHT_UP__LEFT_UP:
        {
            m_ScreenPoint.x = m_CenterPoint.x;
            m_ScreenPoint.y = m_CenterPoint.y + (m_ObjectPosition.y - m_RightUp_LeftUpPoint.y);
            break;
        }
            
        case RECT_ID_RIGHT_DOWN__LEFT_DOWN:
        {
            m_ScreenPoint.x = m_CenterPoint.x;
            m_ScreenPoint.y = m_ObjectPosition.y;
            break;
        }
        
        case RECT_ID_RIGHT_DOWN__RIGHT_UP:
        {
            m_ScreenPoint.x = m_CenterPoint.x + (m_ObjectPosition.x - m_RightDown_RightUpPoint.x);
            m_ScreenPoint.y = m_CenterPoint.y;
            break;
        }
        
        case RECT_ID_RIGHT_DOWN__RIGHT_DOWN:
        {
            m_ScreenPoint.x = m_CenterPoint.x + (m_ObjectPosition.x - m_RightDownZeroPoint.x);
            m_ScreenPoint.y = m_ObjectPosition.y;
            break;
        }
    }
}


void CGPlayer::DrawGObject()
{
    if( m_bIsAddScene == false )
    {
        m_bIsAddScene = true;
        m_pGameScene->addChild(m_pPlayerSprite,DEEP_PLAYER_DEFAULT);
        
    }
    
    if( m_iLastState != m_iAnimationState )
    {
        m_iLastState    = m_iAnimationState;
        m_bStateSwitch  = true;
    }
    
    
    m_pPlayerSprite->setScale(1.5, 1.5);
    
    
    
    ProcessScreenPoint();
    
    
    
    
    m_ObjectPosition = m_pPhysicsObject->GetPhysicsPosition();
    
    //m_pPlayerSprite->setPosition(m_ObjectPosition);
    m_pPlayerSprite->setPosition(m_ScreenPoint);
    m_pPlayerSprite->setVisible(m_bObjectVisible);
    
    
    switch( m_iAnimationState )
    {
        case ANIMATION_STATE_MOVE:
        {
            PlayMoveAnimation();
            break;
        }
        case ANIMATION_STATE_STAND:
        {
            PlayStandAnimation();
            break;
        }
        case ANIMATION_STATE_DIE:
        {
            PlayDieAnimation();
            break;
        }
        case ANIMATION_STATE_HIT:
        {
            PlayHitAnimation();
            break;
        }
        case ANIMATION_STATE_ATTACK:
        {
            PlayAttackAnimation();
            break;
        }
        default:
            break;
    }
    
    if( m_iPlayerOrientation == PLAYER_ORIENTATION_LEFT )
    {
        m_pPlayerSprite->setFlippedX(false);
    }
    
    if( m_iPlayerOrientation == PLAYER_ORIENTATION_RIGHT )
    {
        m_pPlayerSprite->setFlippedX(true);
    }
    
    if( m_bCallDie )
    {
        m_bPlayerDead = true;
    }
    
    m_iJoyStickValue = m_pUI->GetJoyStickValue();
    m_bPowerButton   = m_pUI->GetPowerButtonIsTouch();
    
    
        
    if( m_iJoyStickValue == JOYSTICK_ORIENTATION_LEFT_1 )
    {
        if( m_bPowerButton == true )
        {
            m_iPhysicsState  = PLAYER_PHYSICS_LEFT;
        }
        m_iPlayerOrientation = PLAYER_ORIENTATION_LEFT;

    }
    
    if( m_iJoyStickValue == JOYSTICK_ORIENTATION_LEFT_2 )
    {
        if( m_bPowerButton == true )
        {
            m_iPhysicsState  = PLAYER_PHYSICS_LEFT;
        }
        m_iPlayerOrientation = PLAYER_ORIENTATION_LEFT;

    }
    
    if( m_iJoyStickValue == JOYSTICK_ORIENTATION_RIGHT_1 )
    {
        if( m_bPowerButton == true )
        {
            m_iPhysicsState  = PLAYER_PHYSICS_RIGHT;
        }
        m_iPlayerOrientation = PLAYER_ORIENTATION_RIGHT;

    }
    
    if( m_iJoyStickValue == JOYSTICK_ORIENTATION_RIGHT_2 )
    {
        if( m_bPowerButton == true )
        {
            m_iPhysicsState  = PLAYER_PHYSICS_RIGHT;
        }
        m_iPlayerOrientation = PLAYER_ORIENTATION_RIGHT;

    }
    
    if( m_iJoyStickValue == JOYSTICK_ORIENTATION_LEFT_UP )
    {
        if( m_bPowerButton == true )
        {
            m_iPhysicsState  = PLAYER_PHYSICS_LEFT_UP;
        }
        m_iPlayerOrientation = PLAYER_ORIENTATION_LEFT;

    }
    
    if( m_iJoyStickValue == JOYSTICK_ORIENTATION_RIGHT_UP )
    {
        if( m_bPowerButton == true )
        {
            m_iPhysicsState  = PLAYER_PHYSICS_RIGHT_UP;
        }
        m_iPlayerOrientation = PLAYER_ORIENTATION_RIGHT;

    }
    
    if( m_bPowerButton == false )
    {
        m_iPhysicsState = PLAYER_PHYSICS_DOWN;
    }
    
    if( m_iJoyStickValue == 0 )
    {
        if( m_bPowerButton == true )
        {
            m_iPhysicsState = PLAYER_PHYSICS_UP;
        }
    }
    
    if( m_iJoyStickValue == JOYSTICK_ORIENTATION_LEFT_DOWN )
    {
        if( m_bPowerButton )
        {
            m_iPhysicsState      = PLAYER_PHYSICS_LEFT_DOWN;
        }
        m_iPlayerOrientation     = PLAYER_ORIENTATION_LEFT;

    }
    
    if( m_iJoyStickValue == JOYSTICK_ORIENTATION_RIGHT_DOWN )
    {
        if( m_bPowerButton )
        {
            m_iPhysicsState      = PLAYER_PHYSICS_RIGHT_DOWN;
        }
        m_iPlayerOrientation     = PLAYER_ORIENTATION_RIGHT;

    }
    
    m_iObliqueForceX      = m_pDate->GetPlayerObliqueForceX();
    m_iObliqueForceY      = m_pDate->GetPlayerObliqueForceY();
    m_iVerticalForceX     = m_pDate->GetPlayerVerticalForceX();
    m_iVerticalForceY     = m_pDate->GetPlayerVerticalForceY();
    m_iHorizontalForceX   = m_pDate->GetPlayerHorizontalForceX();
    m_iHorizontalForceY   = m_pDate->GetPlayerHorizontalForceY();
    m_iObliqueDownForceX  = m_pDate->GetPlayerObliqueDownForceX();
    m_iObliqueDownForceY  = m_pDate->GetPlayerObliqueDownForceY();
    m_iVerticalDownFroce  = m_pDate->GetPlayerVerticalDownForce();
    m_fHorizontalSpeed    = m_pPhysicsObject->GetPhysicsXSpeed();
    m_fVerticalSpeed      = m_pPhysicsObject->GetPhysicsYSpeed();
    m_fHorizontalMaxSpeed = m_pDate->GetPlayerHorizontalMaxSpeed();
    m_fVerticalMaxSpeed   = m_pDate->GetPlayerVerticalMaxSpeed();
    
    
    if( m_fHorizontalSpeed > m_fHorizontalMaxSpeed )
    {
        m_pPhysicsObject->SetHorizontalSpeed(m_fHorizontalMaxSpeed);
    }
    
    if( m_fHorizontalSpeed < m_fHorizontalMaxSpeed * -1 )
    {
        m_pPhysicsObject->SetHorizontalSpeed(m_fHorizontalMaxSpeed * -1);
    }
    
    if( m_fVerticalSpeed > m_fVerticalMaxSpeed)
    {
        m_pPhysicsObject->SetVerticalSpeed(m_fVerticalMaxSpeed);
    }
    
    CG_DEBUG_PRINT_1("SpeedX: ",m_fHorizontalSpeed);
    CG_DEBUG_PRINT_1("SpeedY: ", m_fVerticalSpeed);

    m_bOpenPhysics = true;
    
    int t_iCurrentTemp = m_pDate->GetPlayerTemp();
    int t_iMaxTemp     = m_pDate->GetPlayerMaxTemp();
    
    if( m_bOpenPhysics )
    {
        if( t_iCurrentTemp < t_iMaxTemp )
        {
            switch(m_iPhysicsState)
            {
                case PLAYER_PHYSICS_DOWN:
                {
                    m_pPhysicsObject->ApplyForce(0, m_iVerticalDownFroce);
                    CG_DEBUG_PRINT("DOWN");
                    break;
                }
                    
                case PLAYER_PHYSICS_UP:
                {
                    m_pPhysicsObject->ApplyForce(0, m_iVerticalForceY);
                    CG_DEBUG_PRINT("UP")
                    break;
                }
                    
                case PLAYER_PHYSICS_LEFT:
                {
                    m_pPhysicsObject->ApplyForce(0 - m_iHorizontalForceX, m_iHorizontalForceY);
                    CG_DEBUG_PRINT("LEFT")
                    break;
                }
                    
                case PLAYER_PHYSICS_RIGHT:
                {
                    m_pPhysicsObject->ApplyForce(m_iHorizontalForceX, m_iHorizontalForceY);
                    CG_DEBUG_PRINT("RIGHT")
                    break;
                }
                case PLAYER_PHYSICS_LEFT_UP:
                {
                    m_pPhysicsObject->ApplyForce(0 - m_iObliqueForceX, m_iObliqueForceY);
                    CG_DEBUG_PRINT("LEFT_UP")
                    break;
                }
                    
                case PLAYER_PHYSICS_RIGHT_UP:
                {
                    m_pPhysicsObject->ApplyForce(m_iObliqueForceX, m_iObliqueForceY);
                    CG_DEBUG_PRINT("RIGHT_UP")
                    break;
                }
                case PLAYER_PHYSICS_RIGHT_DOWN:
                {
                    m_pPhysicsObject->ApplyForce(m_iObliqueDownForceX, m_iObliqueDownForceY);
                    CG_DEBUG_PRINT("RIGHT_DOWN")
                    break;
                }
                    
                case PLAYER_PHYSICS_LEFT_DOWN:
                {
                    m_pPhysicsObject->ApplyForce(0 - m_iObliqueDownForceX, m_iObliqueDownForceY);
                    CG_DEBUG_PRINT("LEFT_DOWN")
                    break;
                }
            }

        }

    }
    else
    {
        bool t_IsInRect = false;
        
        if( m_SceneRect.containsPoint(m_ObjectPosition) )
        {
            t_IsInRect = true;
        }
        
        
        int t_iSpeed = 10;
        switch(m_iJoyStickValue)
        {
            case JOYSTICK_ORIENTATION_RIGHT_DOWN:
            {
                if( m_ObjectPosition.x + t_iSpeed < m_SceneRect.size.width )
                {
                    m_ObjectPosition.x += t_iSpeed;
                }
                if( m_ObjectPosition.y - t_iSpeed > m_SceneRect.origin.y )
                {
                    m_ObjectPosition.y -= t_iSpeed;
                }
                break;
            }
            case JOYSTICK_ORIENTATION_RIGHT_UP:
            {
                if( m_ObjectPosition.x + t_iSpeed < m_SceneRect.size.width )
                {
                    m_ObjectPosition.x += t_iSpeed;
                }
                if( m_ObjectPosition.y + t_iSpeed < m_SceneRect.size.height )
                {
                    m_ObjectPosition.y += t_iSpeed;
                }
                break;
            }
            case JOYSTICK_ORIENTATION_UP:
            {
                if( m_ObjectPosition.y + t_iSpeed < m_SceneRect.size.height )
                {
                    m_ObjectPosition.y += t_iSpeed;

                }
                break;
            }
            case JOYSTICK_ORIENTATION_LEFT_2:
            {
                if( m_ObjectPosition.x - t_iSpeed > m_SceneRect.origin.x)
                {
                    m_ObjectPosition.x -= t_iSpeed;
                }
                break;
            }
            case JOYSTICK_ORIENTATION_LEFT_1:
            {
                if( m_ObjectPosition.x - t_iSpeed > m_SceneRect.origin.x)
                {
                    m_ObjectPosition.x -= t_iSpeed;
                }
                break;
            }
            case JOYSTICK_ORIENTATION_RIGHT_1:
            {
                if( m_ObjectPosition.x + t_iSpeed < m_SceneRect.size.width )
                {
                    m_ObjectPosition.x += t_iSpeed;
                }
                break;
            }
            case JOYSTICK_ORIENTATION_RIGHT_2:
            {
                if( m_ObjectPosition.x + t_iSpeed < m_SceneRect.size.width )
                {
                    m_ObjectPosition.x += t_iSpeed;
                }
                break;
            }
            case JOYSTICK_ORIENTATION_LEFT_UP:
            {
                if( m_ObjectPosition.x - t_iSpeed > m_SceneRect.origin.x )
                {
                    m_ObjectPosition.x -= t_iSpeed;
                }
                if( m_ObjectPosition.y + t_iSpeed < m_SceneRect.size.height )
                {
                    m_ObjectPosition.y += t_iSpeed;
                }
                break;
            }
            case JOYSTICK_ORIENTATION_LEFT_DOWN:
            {
                if( m_ObjectPosition.x - t_iSpeed > m_SceneRect.origin.x )
                {
                    m_ObjectPosition.x -= t_iSpeed;
                }
                if( m_ObjectPosition.y - t_iSpeed > m_SceneRect.origin.y )
                {
                    m_ObjectPosition.y -= t_iSpeed;
                }
                break;
            }
            case JOYSTICK_ORIENTATION_DOWN:
            {
                if( m_ObjectPosition.y - t_iSpeed > m_SceneRect.origin.y )
                {
                    m_ObjectPosition.y -= t_iSpeed;
                }
                break;
            }
        }

    }
    
    
    
}
void CGPlayer::DieCallBack()
{
    m_bCallDie = true;
}

bool CGPlayer::CleareGObject()
{
    if( m_pAttackAnimate != nullptr )
    {
        m_pAttackAnimate->release();
    }
    
    if( m_pMoveAnimate != nullptr )
    {
        m_pMoveAnimate->release();
    }
    
    if( m_pStandAnimate != nullptr )
    {
        m_pStandAnimate->release();
    }
    
    if( m_pHitAnimate != nullptr )
    {
        m_pHitAnimate->release();
    }
    
    if( m_pDieAnimate != nullptr )
    {
        m_pDieAnimate->release();
    }
    
    if( m_pPlayerSprite != nullptr )
    {
        m_pPlayerSprite->release();
        
        m_pGameScene->removeChild(m_pPlayerSprite);
    }
    
    return true;
}

bool CGPlayer::DeleteGObject()
{
    delete this;
    return true;
}

void CGPlayer::PlayDieAnimation()
{
    
    if( m_bStateSwitch == true )
    {
        m_bStateSwitch = false;
        m_pPlayerSprite->stopAllActions();
        m_pPlayerSprite->runAction(m_pDieSequnce);
    }
}

void CGPlayer::PlayStandAnimation()
{
    if( m_bStateSwitch == true )
    {
        m_bStateSwitch = false;
        m_pPlayerSprite->stopAllActions();
        m_pPlayerSprite->runAction(m_pStandAnimate);
    }
}

void CGPlayer::PlayMoveAnimation()
{
    if( m_bStateSwitch == true )
    {
        m_bStateSwitch = false;
        m_pPlayerSprite->stopAllActions();
        m_pPlayerSprite->runAction(m_pMoveAnimate);
    }
}

void CGPlayer::PlayHitAnimation()
{
    if( m_bStateSwitch == true )
    {
        m_bStateSwitch = false;
        m_pPlayerSprite->stopAllActions();
        m_pPlayerSprite->runAction(m_pHitAnimate);
    }
}

void CGPlayer::PlayAttackAnimation()
{
    if( m_bStateSwitch == true )
    {
        m_bStateSwitch = false;
        m_pPlayerSprite->stopAllActions();
        m_pPlayerSprite->runAction(m_pAttackAnimate);
    }
}



