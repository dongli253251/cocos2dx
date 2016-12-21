//
//  CGBullet.cpp
//  Game
//
//  Created by dongli on 2016/11/20.
//
//

#include "CGBullet.hpp"
#include <cocos2d.h>
#include <Box2D/Box2D.h>
#include "CGAnimateManger.hpp"
#include "CGResManager.hpp"
#include "CGUIManager.hpp"
#include "CGScene.hpp"
#include "CGDataType.h"
#include "CGPlayerDateManager.hpp"
#include "CGGlobalDateManager.hpp"

using namespace cocos2d;

extern CGScene * GetGScene();

CGBullet * CGBullet::CreateBullet(const std::string sName, float fx, float fy,int iOrien,int iType)
{
    auto t_pObject = new CGBullet(sName,fx,fy,iOrien,iType);
    
    if( t_pObject == nullptr )
    {
        CG_DEBUG_PRINT("CGBullet Create Is Error");
        throw CGException("CGBullet Create Is Error");
    }
    else
    {
        t_pObject->InitGObject();
        return t_pObject;
    }

}

CGBullet * CGBullet::CreateBullet(const std::string sName, const Point &Position, int iOrent,int iType)
{
   return CreateBullet(sName, Position.x, Position.y, iOrent,iType);
}

bool CGBullet::InitGObject()
{
    
    m_pAniamteManager    = CGAnimateManager::sharedAnimateManager();
    m_pUI                = CGUIManager::sharedUIManager();
    m_pRes               = CGResManager::sharedResManager();
    m_pDate              = CGPlayerDateManager::sharedPlayerDateManager();
    m_pGlobal            = CGGlobalDateManager::sharedGlobalDateManager();
    
    m_iWeaponHeight      = m_pRes->GetTextureHeightByName(m_sTextureName);
    m_iWeaponWidth       = m_pRes->GetTextureWidthByName(m_sTextureName);
    m_iWeaponState       = BULLET_STATE_NORMAL;
    m_iObjectDeep        = DEEP_BULLET_DEFAULT;
    m_bIsLunch           = true;
    m_bIsDead            = false;
    m_iBulletSpeed       = m_pDate->GetPlayerBulletSpeed();
    m_pGameScene         = GetGScene();
    m_NearBasePoint      = m_pGlobal->GetNearBasePoint();
    m_ScreenPosition.x   = m_NearBasePoint.x + m_ObjectPosition.x;
    m_ScreenPosition.y   = m_NearBasePoint.y + m_ObjectPosition.y;
    auto t_pCache        = SpriteFrameCache::getInstance();
  
    
    if( m_sTextureName == "FeiDanA" )
    {
        m_pAnimation = m_pAniamteManager->GetAnimationByID("FeiDanA_A");
        m_pAnimation->setLoops(-1);
        m_pAnimation->setDelayPerUnit(0.5f);
        m_pAnimate   = Animate::create(m_pAnimation);
        m_pBulletSprite = Sprite::create();
        m_pBulletSprite->retain();
        m_pBulletSprite->runAction(m_pAnimate);
    }
    else
    {
        auto t_sBullet       = m_sTextureName + "_Normal-00.png";
        m_pBulletFrame       = t_pCache->getSpriteFrameByName(t_sBullet);
        //m_pBulletFrame->retain();
        m_pBulletSprite      = Sprite::createWithSpriteFrame(m_pBulletFrame);
    }
    
    int t_iX             = m_ObjectPosition.x - m_iWeaponWidth  / 2;
    int t_iY             = m_ObjectPosition.y - m_iWeaponHeight / 2;
    
    
    if( m_iBulletOriention == BULLET_ORIENTAION_LEFT )
    {
        m_ObjectPosition.x -= 80;
        m_ScreenPosition.x -= 80;
    }
    
    if( m_iBulletOriention == BULLET_ORIENTAION_RIGHT )
    {
        m_ObjectPosition.x += 80;
        m_ScreenPosition.x += 80;
    }

    m_pBulletSprite->setPosition(m_ScreenPosition);
    m_pBulletSprite->setVisible(m_bObjectVisible);
    m_WeaponRect.setRect(t_iX, t_iY, m_iWeaponWidth, m_iWeaponHeight);
    
    m_pBulletSprite->retain();
    
    return true;
}

bool CGBullet::CleareGObject()
{
    //m_pBulletFrame->release();
    m_pBulletSprite->release();
    //m_pAnimation->release();
    //m_pAnimate->release();
    m_pGameScene->removeChild(m_pBulletSprite);
    return true;
}

bool CGBullet::DeleteGObject()
{
    delete this;
    return true;
}

void CGBullet::DrawGObject()
{
    if( m_bIsAddScene == false )
    {
        m_pGameScene->addChild(m_pBulletSprite, m_iObjectDeep);
        m_bIsAddScene = true;
    }
    
    if( m_iBulletOriention == BULLET_ORIENTAION_LEFT )
    {
        m_pBulletSprite->setFlippedX(true);
    }
    if( m_iBulletOriention == BULLET_ORIENTAION_RIGHT )
    {
        m_pBulletSprite->setFlippedX(false);
    }
    
    if( m_iBulletOwner == BULLET_OWNER_LOCAL )
    {
        if( m_pGlobal->GetBulletLunchSuccess() )
        {
            m_iBulletSpeed = m_pDate->GetPlayerBulletSpeed();
            
            m_pBulletSprite->setPosition(m_ScreenPosition);
            m_pBulletSprite->setVisible(m_bObjectVisible);
            
            int t_iX = m_ObjectPosition.x - m_iWeaponWidth  / 2;
            int t_iY = m_ObjectPosition.y - m_iWeaponHeight / 2;
            
            m_WeaponRect.setRect(t_iX, t_iY, m_iWeaponWidth, m_iWeaponHeight);
            
            if( m_bIsLunch == true )
            {
                if( m_iWeaponState == BULLET_STATE_NORMAL )
                {
                    
                    if( m_iBulletOriention == BULLET_ORIENTAION_LEFT )
                    {
                        m_ObjectPosition.x -= m_iBulletSpeed;
                        m_ScreenPosition.x -= m_iBulletSpeed;
                    }
                    
                    if( m_iBulletOriention == BULLET_ORIENTAION_RIGHT )
                    {
                        m_ObjectPosition.x += m_iBulletSpeed;
                        m_ScreenPosition.x += m_iBulletSpeed;
                    }
                }
                
                if( m_iWeaponState == BULLET_STATE_STRIKE )
                {
                    m_bIsLunch       = false;
                    m_bObjectVisible = false;
                    m_bIsDead        = true;
                }
            }
            
            
            
            if( m_ScreenPosition.x > 2000 )
            {
                m_iWeaponState = BULLET_STATE_STRIKE;
            }
            
            if( m_ScreenPosition.x < - 100 )
            {
                m_iWeaponState = BULLET_STATE_STRIKE;
            }

        }
        
        
    }
    
    
    
}
