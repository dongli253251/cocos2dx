//
//  CGPirateSoldier.cpp
//  Game
//
//  Created by dongli on 2016/12/14.
//
//

#include "CGPirateSoldier.hpp"
#include "CGException.hpp"
#include "CGScene.hpp"
#include "CGAnimateManger.hpp"
#include "CGMonsterAI_LowSoldier.hpp"
#include "CGGlobalDateManager.hpp"

extern CGScene * GetGScene();

CGPirateSoldier * CGPirateSoldier::CreatePirateSoldier(const std::string &sName)
{
    auto t_pSoldier = new CGPirateSoldier(sName);
    
    if( t_pSoldier != nullptr )
    {
        t_pSoldier->InitGObject();
        return t_pSoldier;
    }
    else
    {
        throw CGException("Create PirateSoldier Is Error");
        return nullptr;
    }
}

bool CGPirateSoldier::InitGObject()
{
    auto   t_pGlobal    = CGGlobalDateManager::sharedGlobalDateManager();
    auto * t_pManager   = CGAnimateManager::sharedAnimateManager();
    auto   t_pFlag      = t_pManager->GetFlagStructVecByID(m_sMonsterName);

    
    m_pAttackAnimate    = nullptr;
    m_pDieAnimate       = nullptr;
    m_pStandAnimate     = nullptr;
    m_pMoveAnimate      = nullptr;
    m_pHitAnimate       = nullptr;
    m_pSoldierSprite    = nullptr;
    
    m_bSwitchAnimate    = true;
    m_bCanRunAI         = true;
    m_bIsDead           = false;
    
    m_iMoveSpeed        = 2;
    m_iLastAnimateState = ANIMATION_STATE_DIE;
    m_iAnimateState     = ANIMATION_STATE_STAND;
    
    m_pAI               = CGMonsterAI_LowSoldier::CreateLowSoldierAI(this);
    m_pGameScene        = GetGScene();
    m_pSoldierSprite    = Sprite::create();
    
    m_ScreenPosition    = t_pGlobal->GetNearBasePoint() + m_ObjectPosition;
    
    m_pSoldierSprite->setPosition(m_ScreenPosition);
    m_pSoldierSprite->retain();
    
    for( auto i : t_pFlag )
    {
        if( i.m_sFlagsName == "Move" )
        {
            auto t_sName      = m_sMonsterName + "_" + i.m_sFlagsName;
            auto t_pAnimation = t_pManager->GetAnimationByID(t_sName);
            
            t_pAnimation->setLoops(ANIMATION_LOOP_INFINTE);
            t_pAnimation->setDelayPerUnit(ANIMATION_DELAY_DEFAULT);
            
            m_pMoveAnimate = Animate::create(t_pAnimation);
            
            m_pMoveAnimate->retain();
        }
        
        if( i.m_sFlagsName == "Stand" )
        {
            auto t_sName      = m_sMonsterName + "_" + i.m_sFlagsName;
            auto t_pAnimation = t_pManager->GetAnimationByID(t_sName);
            
            t_pAnimation->setLoops(ANIMATION_LOOP_INFINTE);
            t_pAnimation->setDelayPerUnit(ANIMATION_DELAY_DEFAULT);
            
            m_pStandAnimate = Animate::create(t_pAnimation);
            
            m_pStandAnimate->retain();
        }
        
        if( i.m_sFlagsName == "Die" )
        {
            auto t_sName      = m_sMonsterName + "_" + i.m_sFlagsName;
            auto t_pAnimation = t_pManager->GetAnimationByID(t_sName);
            
            t_pAnimation->setLoops(ANIMATION_LOOP_ONECE);
            t_pAnimation->setDelayPerUnit(ANIMATION_DELAY_DEFAULT);
            
            m_pDieAnimate = Animate::create(t_pAnimation);
            
            m_pDieAnimate->retain();
        }
        
        if( i.m_sFlagsName == "Attack" )
        {
            auto t_sName      = m_sMonsterName + "_" + i.m_sFlagsName;
            auto t_pAnimation = t_pManager->GetAnimationByID(t_sName);
            
            t_pAnimation->setLoops(ANIMATION_LOOP_ONECE);
            t_pAnimation->setDelayPerUnit(ANIMATION_DELAY_DEFAULT);
            
            m_pAttackAnimate = Animate::create(t_pAnimation);
            
            m_pAttackAnimate->retain();
        }
        
        if( i.m_sFlagsName == "Hit" )
        {
            auto t_sName      = m_sMonsterName + "_" + i.m_sFlagsName;
            auto t_pAnimation = t_pManager->GetAnimationByID(t_sName);
            
            t_pAnimation->setLoops(ANIMATION_LOOP_ONECE);
            t_pAnimation->setDelayPerUnit(ANIMATION_DELAY_DEFAULT);
            
            m_pHitAnimate = Animate::create(t_pAnimation);
            
            m_pHitAnimate->retain();
        }
    }
    
    
    return true;
}

bool CGPirateSoldier::CleareGObject()
{
    if( m_pHitAnimate != nullptr )
    {
        m_pHitAnimate->release();
    }
    
    if( m_pDieAnimate != nullptr )
    {
        m_pDieAnimate->release();
    }
    
    if( m_pStandAnimate != nullptr )
    {
        m_pStandAnimate->release();
    }
    
    if( m_pMoveAnimate != nullptr )
    {
        m_pMoveAnimate->release();
    }
    
    if( m_pAttackAnimate != nullptr )
    {
        m_pAttackAnimate->release();
    }
    
    if( m_pSoldierSprite != nullptr )
    {
        m_pSoldierSprite->release();
        m_pGameScene->removeChild(m_pSoldierSprite);
    }
    
    return true;
}



void CGPirateSoldier::DrawGObject()
{
    if( m_bIsAddScene == false )
    {
        m_pGameScene->addChild(m_pSoldierSprite,DEEP_MONSTER_DEFAULT);
        
        m_bIsAddScene = true;
        
        m_pSoldierSprite->setScale(1.5f, 1.5f);
    }
    
    if( m_bCanRunAI )
    {
        m_pAI->ProcessAITask();
    }
    
    m_ScreenPosition = CGGlobalDateManager::sharedGlobalDateManager()->GetNearBasePoint() + m_ObjectPosition;
    
    m_pSoldierSprite->setPosition(m_ScreenPosition);
    
    if( m_iOrientation == MONSTER_ORIENTATION_RIGHT )
    {
        m_pSoldierSprite->setFlippedX(true);
    }
    
    if( m_iOrientation == MONSTER_ORIENTATION_LEFT )
    {
        m_pSoldierSprite->setFlippedX(false);
    }
    
    if( m_iLastAnimateState != m_iAnimateState )
    {
        m_bSwitchAnimate    = true;
        m_iLastAnimateState = m_iAnimateState;
    }
    
    switch (m_iAnimateState)
    {
        case ANIMATION_STATE_MOVE:
        {
            PlayMoveAnimate();
            break;
        }
            
        case ANIMATION_STATE_DIE:
        {
            PlayDieAnimate();
            break;
        }
            
        case ANIMATION_STATE_ATTACK:
        {
            PlayAttackAnimate();
            break;
        }
            
        case ANIMATION_STATE_HIT:
        {
            PlayHitAnimate();
            break;
        }
            
        case ANIMATION_STATE_STAND:
        {
            PlayStandAnimate();
            break;
        }
    }
    
    //m_pAI->ProcessAITask();
    
}

void CGPirateSoldier::ApplyPosition(const Point &Position)
{
    m_ObjectPosition.x += Position.x;
    m_ObjectPosition.y += Position.y;
}

void CGPirateSoldier::PlayDieAnimate()
{
    if( m_bSwitchAnimate )
    {
        m_pSoldierSprite->stopAllActions();
        m_pSoldierSprite->runAction(m_pDieAnimate);
        
        m_bSwitchAnimate = false;
    }
}

void CGPirateSoldier::PlayAttackAnimate()
{
    if( m_bSwitchAnimate )
    {
        m_pSoldierSprite->stopAllActions();
        
        if( m_pAttackAnimate == nullptr )
        {
            CG_DEBUG_PRINT("CGPirateSoldier::PlayAttackAniamte Is Error");
            
            throw CGException("PlayAttackAnimate Is Error");
        }
        
        else
        {
            m_pSoldierSprite->runAction(m_pAttackAnimate);
        }
        
        m_bSwitchAnimate = false;
    }

}

void CGPirateSoldier::PlayMoveAnimate()
{
    if( m_bSwitchAnimate )
    {
        m_pSoldierSprite->stopAllActions();
        m_pSoldierSprite->runAction(m_pMoveAnimate);
        
        m_bSwitchAnimate = false;
    }

}

void CGPirateSoldier::PlayStandAnimate()
{
    if( m_bSwitchAnimate )
    {
        m_pSoldierSprite->stopAllActions();
        m_pSoldierSprite->runAction(m_pStandAnimate);
        
        m_bSwitchAnimate = false;
    }
}

void CGPirateSoldier::PlayHitAnimate()
{
    if( m_bSwitchAnimate )
    {
        m_pSoldierSprite->stopAllActions();
        m_pSoldierSprite->runAction(m_pHitAnimate);
        
        m_bSwitchAnimate = false;
    }
}

void CGPirateSoldier::AddMoveEvetnToList(float fX, float fY, int iType)
{

}
bool CGPirateSoldier::DeleteGObject()
{
    delete this;
    return true;
}
