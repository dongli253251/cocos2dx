//
//  CGPowerButton.cpp
//  Game
//
//  Created by dongli on 2016/11/11.
//
//

#include "CGPowerButton.hpp"
#include "CGResManager.hpp"
#include "CGScene.hpp"
#include <iostream>
#include <cocos2d.h>
#include "CGUIManager.hpp"

extern CGScene * GetGScene();


bool CGPowerButton::InitGObject()
{
    
    m_bButtonIsTouch        = false;
    m_bCanZeroPoint         = false;
    m_bLockPoint            = false;
    m_bIsCanWork            = true;
    m_bObjectVisible        = true;
    m_iButtonState          = BUTTON_STATE_POP;
    m_iUIName               = UI_ONLY_ID_POWER_BUTTON;

    CGResManager * t_pRes   = CGResManager::sharedResManager();
    m_pUIManager            = CGUIManager::sharedUIManager();
    std::string t_sUIRes    = t_pRes->GetUIResPath();
    m_pGameScene            = GetGScene();
    m_lOnlyCount            = 0;
    
    m_ButtonRect.setRect(0, 0, 100, 100);
    m_ObjectPosition.set(0, 0);
    
    
    if( m_iButtonType == BUTTON_TYPE_POWER )
    {
        std::string t_sNormalString = t_pRes->GetUITextureString(UI_BUTTON_POWER_NORMAL);
        std::string t_sDownString   = t_pRes->GetUITextureString(UI_BUTTON_POWER_DOWN);
        m_pNormalSprite             = Sprite::create(t_sUIRes + t_sNormalString);
        m_pDownSprite               = Sprite::create(t_sUIRes + t_sDownString);
        m_pDownSprite->retain();
        m_pNormalSprite->retain();
    }
    
    
    
    return true;
}

void CGPowerButton::SetButtonScale(float fx, float fy)
{
    m_pNormalSprite->setScale(fx, fy);
    m_pDownSprite->setScale(fx, fy);
}

void CGPowerButton::DrawGObject()
{
    if( m_bIsAddScene == false )
    {
        m_bIsAddScene = true;
        m_pGameScene->addChild(m_pNormalSprite, DEEP_UI_DEFAULT);
        m_pGameScene->addChild(m_pDownSprite, DEEP_UI_DEFAULT);
    }
    auto size = Director::getInstance()->getWinSize();
    
    m_pNormalSprite->setPosition(m_ObjectPosition);
    
    m_pDownSprite->setPosition(m_ObjectPosition);
    
    auto t_pRes = CGResManager::sharedResManager();
    
    if( m_iUIName == UI_ONLY_ID_BULLET )
    {
        m_iButtonWidth    = t_pRes->GetUISizeByName(UI_SIZE_BULLET_WIDTH);
        m_iButtonHeight   = t_pRes->GetUISizeByName(UI_SIZE_BULLET_HEIGHT);
        
        int t_iX          = m_ObjectPosition.x - m_iButtonWidth;
        int t_iY          = m_ObjectPosition.y - m_iButtonHeight;
        
        m_ButtonRect.setRect(t_iX, t_iY, m_iButtonWidth * 2 , m_iButtonHeight * 2 );
    }
    
    if(  m_iUIName == UI_ONLY_ID_POWER_BUTTON )
    {
        m_iButtonWidth    = t_pRes->GetUISizeByName(UI_SIZE_POWER_WIDTH);
        m_iButtonHeight   = t_pRes->GetUISizeByName(UI_SIZE_POWER_HEIGHT);
        
        int t_iX          = m_ObjectPosition.x - m_iButtonWidth;
        int t_iY          = m_ObjectPosition.y - m_iButtonHeight;
        
        m_ButtonRect.setRect(t_iX, t_iY, m_iButtonWidth * 2 , m_iButtonHeight * 2 );
    }
    
    
    
    if( m_bLockPoint == false )
    {
        if( ! m_pUIManager->GetTouchVecIsEmpty() )
        {
            m_lOnlyCount = m_pUIManager->GetOnlyCountByRect(m_ButtonRect);
            
            if( m_lOnlyCount != 0 )
            {
                m_bLockPoint = true;
            }
        }
    }
    
    if( m_bLockPoint == true )
    {
        m_TouchBeganPoint = m_pUIManager->GetBeganPointByOnlyCount(m_lOnlyCount);
        m_TouchMovePoint  = m_pUIManager->GetMovePointByOnlyCount(m_lOnlyCount);
        m_TouchEndPoint   = m_pUIManager->GetEndPointByOnlyCount(m_lOnlyCount);
    }
    
    
    if( m_bObjectVisible == false )
    {
        m_pNormalSprite->setVisible(false);
        m_pDownSprite->setVisible(false);
    }
    else
    {
        if( m_bIsCanWork == true )
        {
            if( m_iButtonState == BUTTON_STATE_POP )
            {
                m_pDownSprite->setVisible(false);
                m_pNormalSprite->setVisible(true);
            }
            
            if( m_iButtonState == BUTTON_STATE_PUSH )
            {
                m_pDownSprite->setVisible(true);
                m_pNormalSprite->setVisible(false);
            }
            
            
            
            if( m_ButtonRect.containsPoint(m_TouchBeganPoint) == true)
            {
                m_bButtonIsTouch = true;
            }
            else
            {
                m_bButtonIsTouch = false;
            }
            
            if( m_TouchMovePoint != Point(0, 0) )
            {
                if( m_ButtonRect.containsPoint(m_TouchMovePoint) == false)
                {
                    m_bButtonIsTouch = false;
                }
            }
            
            if( m_bButtonIsTouch )
            {
                m_iButtonState = BUTTON_STATE_PUSH;
            }
            else
            {
                m_iButtonState = BUTTON_STATE_POP;
            }
            
            if( m_TouchEndPoint != Point(0,0) )
            {
                m_bButtonIsTouch = false;
                m_TouchBeganPoint.set(0, 0);
                m_TouchMovePoint.set(0, 0);
                m_TouchEndPoint.set(0, 0);
                
                m_pUIManager->SetIsEndByOnlyCount(m_lOnlyCount, true);
                m_bLockPoint = false;
            }
            
        }
        
    }
    
}

bool CGPowerButton::CleareGObject()
{
    m_pGameScene->removeChild(m_pNormalSprite);
    m_pGameScene->removeChild(m_pDownSprite);
}

bool CGPowerButton::DeleteGObject()
{
    delete this;
    return true;
}
