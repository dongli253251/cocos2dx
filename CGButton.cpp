//
//  CGButton.cpp
//  Game
//
//  Created by dongli on 2016/11/8.
//
//

#include "CGButton.hpp"
#include "CGResManager.hpp"
#include "CGDataType.h"
#include "CGScene.hpp"

extern CGScene * GetGScene();

CGButton * CGButton::CreateButton(int iButtonType)
{
    CGButton * t_pButton = new CGButton(iButtonType);
    
    if(t_pButton == nullptr)
    {
        std::cout<<"CGButton Create Is Error "<<std::endl;
        return nullptr;
    }
    else
    {
        t_pButton->InitGObject();
        return t_pButton;
    }
}

bool CGButton::InitGObject()
{
    m_TouchEndPoint.set(0, 0);
    
    m_iLastTime           = 0;
    m_iButtonInterval     = 500;
    m_bIsCanWork          = true;
    m_bObjectVisible      = true;
    m_bIsAddScene         = false;
    m_pGameScene          = GetGScene();
    m_iButtonState        = BUTTON_STATE_POP;
    m_iUIName             = UI_NORMAL_BUTTON;
    auto * pRes           = CGResManager::sharedResManager();
    std::string t_sUIPath = pRes->GetUIResPath();
    
    m_ObjectPosition.set(0, 0);
    
    if( m_iButtonType == BUTTON_TYPE_OK )
    {
        std::string t_sButtonDown   = pRes->GetUITextureString(UI_BUTTON_OK_DOWN);
        std::string t_sButtonNormal = pRes->GetUITextureString(UI_BUTTON_OK_NORMAL);
        m_pNormalSprite             = Sprite::create(t_sUIPath + t_sButtonNormal);
        m_pDownSprite               = Sprite::create(t_sUIPath + t_sButtonDown);
    }
    
    if( m_iButtonType == BUTTON_TYPE_KNOW )
    {
        std::string t_sButtonDown   = pRes->GetUITextureString(UI_BUTTON_KNOW_DOWN);
        std::string t_sButtonNormal = pRes->GetUITextureString(UI_BUTTON_KNOW_NORMAL);
        m_pNormalSprite             = Sprite::create(t_sUIPath + t_sButtonNormal);
        m_pDownSprite               = Sprite::create(t_sUIPath + t_sButtonDown);
    }
    
    if( m_iButtonType == BUTTON_TYPE_CANCEL )
    {
        std::string t_sButtonDown   = pRes->GetUITextureString(UI_BUTTON_CANCEL_DOWN);
        std::string t_sButtonNormal = pRes->GetUITextureString(UI_BUTTON_CANCEL_NORMAL);
        m_pNormalSprite             = Sprite::create(t_sUIPath + t_sButtonNormal);
        m_pDownSprite               = Sprite::create(t_sUIPath + t_sButtonDown);
    }
    
    if( m_iButtonType == BUTTON_TYPE_POWER)
    {
        std::string t_sButtonDown   = pRes->GetUITextureString(UI_BUTTON_POWER_DOWN);
        std::string t_sButtonNormal = pRes->GetUITextureString(UI_BUTTON_POWER_NORMAL);
        m_pNormalSprite             = Sprite::create(t_sUIPath + t_sButtonNormal);
        m_pDownSprite               = Sprite::create(t_sUIPath + t_sButtonDown);
    }
    
    m_pDownSprite->retain();
    m_pNormalSprite->retain();
    
    
    
}




long long GetCurrentMSce()
{
    timeval t_Time;
    gettimeofday(&t_Time, NULL);

    return t_Time.tv_sec * 1000 + t_Time.tv_usec / 1000;
}

bool CGButton::CleareGObject()
{
    m_pDownSprite->release();
    m_pNormalSprite->release();
    m_pGameScene->removeChild(m_pDownSprite);
    m_pGameScene->removeChild(m_pNormalSprite);

    return true;
}

bool CGButton::DeleteGObject()
{
    delete this;
    return true;
}

void CGButton::SetButtonScale(float fx, float fy)
{
    m_pDownSprite->setScale(fx, fy);
    m_pNormalSprite->setScale(fx, fy);
}

void CGButton::DrawGObject()
{
    if( m_bIsAddScene == false )
    {
        m_pGameScene->addChild(m_pNormalSprite, m_iObjectDeep);
        m_pGameScene->addChild(m_pDownSprite, m_iObjectDeep);
        m_bIsAddScene = true;
    }
    
    
    
    int t_iButtonX      = m_ObjectPosition.x - 50;
    int t_iButtonY      = m_ObjectPosition.y - 25;
    int t_iButtonHeight = 100;
    int t_iButtonWidth  = 200;
    
    m_ButtonRect.setRect(t_iButtonX, t_iButtonY, t_iButtonWidth, t_iButtonHeight);
    
    m_pNormalSprite->setPosition(m_ObjectPosition);
    m_pDownSprite->setPosition(m_ObjectPosition);
    
    if( m_iButtonState == BUTTON_STATE_POP )
    {
        m_pNormalSprite->setVisible(true);
        m_pDownSprite->setVisible(false);
    }
    
    if( m_iButtonState == BUTTON_STATE_PUSH )
    {
        m_pNormalSprite->setVisible(false);
        m_pDownSprite->setVisible(true);
    }
    
    
    
    
}
