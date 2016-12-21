//
//  CGJoyStick.cpp
//  Game
//
//  Created by dongli on 2016/11/13.
//
//

#include "CGJoyStick.hpp"
#include <cocos2d.h>
#include <CGScene.hpp>
#include <iostream>
#include <CGException.hpp>
#include "CGDataType.h"
#include "CGUIManager.hpp"
#include "CGResManager.hpp"
using namespace cocos2d;

extern CGScene * GetGScene();

CGJoyStick * CGJoyStick::CreateJoyStick(int iType)
{
    auto t_pJoyStick = new CGJoyStick(iType);
    
    if( t_pJoyStick == nullptr )
    {
        throw CGException("CreateJoyStick Is Error");
    }
    else
    {
        t_pJoyStick->InitGObject();
        return t_pJoyStick;
    }
}

bool CGJoyStick::InitGObject()
{
    m_pGameScene        = GetGScene();
    auto t_pRes         = CGResManager::sharedResManager();
    m_pUIManager        = CGUIManager::sharedUIManager();
    m_iUIName           = UI_ONLY_ID_JOYSTICK;
    m_iJoyStickValue    = 0;
    m_bObjectVisible    = true;
    m_bCanSetRect       = true;
    m_bTouchAnchor      = false;
    m_bCanSetBall       = false;
    m_bCanSetBottom     = false;
    m_bBallVisible      = false;
    m_bBottomVisible    = false;
    m_bIsLockPoint      = false;
    m_CenterPoint       = m_ObjectPosition;
    m_BottomPoint       = m_ObjectPosition;
    m_BallPoint         = m_ObjectPosition;
    m_iJoyStickWidth    = t_pRes->GetUISizeByName(UI_SIZE_JOYSTICK_WIDTH);
    m_iJoyStickHeight   = t_pRes->GetUISizeByName(UI_SIZE_JOYSTICK_HEIGHT);
    
    
    m_ValidRect.setRect(0, 0, 1334 / 2, 750);
    m_JoyStickRect.setRect(0, 0, m_iJoyStickWidth, m_iJoyStickHeight);
    
    if( m_iJoyStickType == JOYSTICK_TYPE_NORMAL )
    {
        std::string t_sJoyStickNormal   = t_pRes->GetUITextureString(UI_JOYSTICK_NORMAL);
        std::string t_sJoyStickBall     = t_pRes->GetUITextureString(UI_JOYSTICK_BALL);
        std::string t_sNormalPath       = t_pRes->GetUIResPath() + t_sJoyStickNormal;
        std::string t_sBallPath         = t_pRes->GetUIResPath() + t_sJoyStickBall;
        m_pJoyStickBottom               = Sprite::create(t_sNormalPath);
        m_pJoyStickBall                 = Sprite::create(t_sBallPath);
        
        m_pJoyStickBottom->retain();
        m_pJoyStickBottom->setPosition(m_ObjectPosition);
        m_pJoyStickBottom->setVisible(m_bObjectVisible);
        
        m_pJoyStickBall->retain();
        m_pJoyStickBall->setPosition(m_ObjectPosition);
        m_pJoyStickBall->setVisible(m_bObjectVisible);
    }
    
    return true;
}

bool CGJoyStick::CleareGObject()
{
    m_pJoyStickBall->release();
    m_pJoyStickBottom->release();
    m_pGameScene->removeChild(m_pJoyStickBall);
    m_pGameScene->removeChild(m_pJoyStickBottom);
    return true;
}

void CGJoyStick::DrawGObject()
{
    if( m_bIsAddScene == false )
    {
        m_pGameScene->addChild(m_pJoyStickBottom, DEEP_UI_DEFAULT);
        m_pGameScene->addChild(m_pJoyStickBall, DEEP_UI_DEFAULT);
        
        m_bIsAddScene = true;
    }
    
    
    
    m_ObjectPosition = m_BottomPoint;
    
    if( m_bCanSetRect )
    {
        int t_iX = m_BottomPoint.x - m_iJoyStickWidth  / 2;
        int t_iY = m_BottomPoint.y - m_iJoyStickHeight / 2;
        
        m_JoyStickRect.setRect(t_iX, t_iY, m_iJoyStickWidth +50, m_iJoyStickHeight +50);
    }

    
    if( m_bIsLockPoint == false )
    {
        
        if( ! m_pUIManager->GetTouchVecIsEmpty() )
        {
            m_lOnlyCount      = m_pUIManager->GetOnlyCountByRect(m_ValidRect);
            
            if( m_lOnlyCount != 0 )
            {
                m_bIsLockPoint = true;
            }
        }
        
    }
    
    if( m_bIsLockPoint == true )
    {
        m_TouchBeganPoint = m_pUIManager->GetBeganPointByOnlyCount(m_lOnlyCount);
        m_TouchEndPoint   = m_pUIManager->GetEndPointByOnlyCount(m_lOnlyCount);
        m_TouchMovePoint  = m_pUIManager->GetMovePointByOnlyCount(m_lOnlyCount);
    }
    
    if( m_bObjectVisible == false )
    {
        m_pJoyStickBottom->setVisible(false);
        m_pJoyStickBall->setVisible(false);
    }
    else
    {
        if( m_bIsCanWork )
        {
            if( m_TouchBeganPoint != Point(0,0) )
            {
                if( m_ValidRect.containsPoint(m_TouchBeganPoint) )
                {
                    m_bTouchAnchor     = true;
                    m_bCanSetBottom    = true;
                    m_BottomPoint      = m_TouchBeganPoint;
                }
            }
            
            if( m_TouchMovePoint != Point(0,0) )
            {
                if( m_ValidRect.containsPoint(m_TouchBeganPoint) )
                {
                    m_BallPoint        = m_TouchMovePoint;
                    m_bBallVisible     = true;
                    m_bBottomVisible   = true;
                    m_bCanSetBall      = true;
                }
                
            }
            
            if( m_TouchEndPoint != Point(0,0) )
            {
                m_TouchEndPoint.set(0, 0);
                m_TouchMovePoint.set(0, 0);
                m_TouchBeganPoint.set(0, 0);
                
                m_pUIManager->SetIsEndByOnlyCount(m_lOnlyCount, true);
                
                m_bIsLockPoint     = false;
                m_bBallVisible     = false;
                m_bBottomVisible   = false;
                m_bCanSetBall      = false;
                m_bCanSetBottom    = false;
                m_iJoyStickValue   = 0;
                m_lOnlyCount       = 0;
            }
        }
    }

    
    
    
    if( m_bBottomVisible )
    {
        m_pJoyStickBottom->setVisible(true);
    }
    else
    {
        m_pJoyStickBottom->setVisible(false);
    }
    
    if( m_bBallVisible )
    {
        m_pJoyStickBall->setVisible(true);
    }
    else
    {
        m_pJoyStickBall->setVisible(false);
    }
    
    if( m_bCanSetBall )
    {
        
        if( m_BallPoint.x > m_BottomPoint.x + m_iJoyStickWidth / 2 )
        {
            m_BallPoint.x = m_BottomPoint.x + m_iJoyStickWidth / 2;
        }
        
        if( m_BallPoint.x < m_BottomPoint.x - m_iJoyStickWidth / 2 )
        {
            m_BallPoint.x = m_BottomPoint.x - m_iJoyStickWidth / 2;
        }
        
        if( m_BallPoint.y < m_BottomPoint.y - m_iJoyStickHeight / 2 )
        {
            m_BallPoint.y = m_BottomPoint.y - m_iJoyStickHeight / 2;
        }
        
        if( m_BallPoint.y > m_BottomPoint.y + m_iJoyStickHeight / 2 )
        {
            m_BallPoint.y = m_BottomPoint.y + m_iJoyStickHeight / 2;
        }
        
        int t_iCenter   = m_BottomPoint.x;
        int t_iRightX   = m_BottomPoint.x + m_iJoyStickWidth / 4 + 10;
        int t_iLeftX    = m_BottomPoint.x - m_iJoyStickWidth / 4 - 10;

        int t_iCenterY  = m_BottomPoint.y;
        int t_iUpY      = t_iCenterY + m_iJoyStickHeight / 4;
        
        
        
        if( m_BallPoint.x < t_iCenter + 20 && m_BallPoint.x > t_iCenter - 20 && m_BallPoint.y > t_iCenterY + 60)
        {
            m_iJoyStickValue = JOYSTICK_ORIENTATION_UP;
            ///CG_DEBUG_PRINT("UP");
        }
        
        if( m_BallPoint.x > t_iRightX && m_BallPoint.y > t_iUpY )
        {
            m_iJoyStickValue = JOYSTICK_ORIENTATION_RIGHT_UP;
            ///CG_DEBUG_PRINT("right up");
        }
        
        if( m_BallPoint.x < t_iLeftX && m_BallPoint.y > t_iUpY )
        {
            m_iJoyStickValue = JOYSTICK_ORIENTATION_LEFT_UP;
            //CG_DEBUG_PRINT("left up");
        }
        
        if( m_BallPoint.x > t_iCenter && m_BallPoint.x < t_iRightX && m_BallPoint.y < t_iUpY)
        {
            m_iJoyStickValue = JOYSTICK_ORIENTATION_RIGHT_1;
            //std::cout<<"Right 1"<<std::endl;
        }
        
        else if( m_BallPoint.x > t_iCenter && m_BallPoint.x > t_iRightX && m_BallPoint.y <t_iUpY)
        {
            m_iJoyStickValue = JOYSTICK_ORIENTATION_RIGHT_2;
            //std::cout<<"Right 2"<<std::endl;
        }

        else if( m_BallPoint.x < t_iCenter && m_BallPoint.x > t_iLeftX && m_BallPoint.y <  t_iUpY)
        {
            m_iJoyStickValue = JOYSTICK_ORIENTATION_LEFT_1;
            //std::cout<<"Left 1"<<std::endl;
        }
        
        else if( m_BallPoint.x < t_iCenter && m_BallPoint.x < t_iLeftX && m_BallPoint.y < t_iUpY)
        {
            m_iJoyStickValue = JOYSTICK_ORIENTATION_LEFT_2;
            //std::cout<<"Left 2"<<std::endl;
        }
        if( m_BallPoint.x < t_iCenter + 20 && m_BallPoint.x > t_iCenter - 20 && m_BallPoint.y < t_iCenterY - 30)
        {
            m_iJoyStickValue = JOYSTICK_ORIENTATION_DOWN;
            CG_DEBUG_PRINT("down");
        }
        
        if( m_BallPoint.x > t_iRightX && m_BallPoint.y < t_iCenterY - m_iJoyStickHeight / 4)
        {
            m_iJoyStickValue = JOYSTICK_ORIENTATION_RIGHT_DOWN;
            CG_DEBUG_PRINT("right down");
        }
        
        if( m_BallPoint.x < t_iLeftX && m_BallPoint.y <  t_iCenterY - m_iJoyStickHeight / 4)
        {
            m_iJoyStickValue = JOYSTICK_ORIENTATION_LEFT_DOWN;
            CG_DEBUG_PRINT("left down");
        }
        
        else if( m_BallPoint == m_BottomPoint )
        {
            m_iJoyStickValue = 0;
            ///CG_DEBUG_PRINT("Joy 0");
        }
        
        m_pJoyStickBall->setPosition(m_BallPoint);
    }
    
    if( m_bCanSetBottom )
    {
        m_pJoyStickBottom->setPosition(m_BottomPoint);
    }
    
}

bool CGJoyStick::DeleteGObject()
{
    delete this;
    return true;
}
