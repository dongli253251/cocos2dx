//
//  CGDamegeNumber.cpp
//  Game
//
//  Created by dongli on 2016/11/30.
//
//

#include "CGDamegeNumber.hpp"
#include "CGException.hpp"
#include "CGScene.hpp"
#include "CGDamegeSystem.hpp"
extern CGScene * GetGScene();


CGDamegeNumber * CGDamegeNumber::CreateDamegeNumber(int iNumber, int iType,const Point& Position)
{
    auto t_pObject = new CGDamegeNumber(iNumber,iType,Position.x,Position.y);
    
    if( t_pObject != nullptr )
    {
        t_pObject->InitGObject();
        
        return t_pObject;
    }
    
    else
    {
        throw CGException("CGDamegeNumber Is Create Error");
        
        return nullptr;
    }
}

bool CGDamegeNumber::InitGObject()
{
    m_bIsDead       = false;
    m_bIsAddScene   = false;
    
    m_pDamegeSystem = CGDamegeSystem::sharedDamegeSystem();
    m_sFontName     = m_pDamegeSystem->GetDamegeFont();
    m_sFontPath     = m_pDamegeSystem->GetFontPath();
    m_pGameScene    = GetGScene();

    if( m_iType == NUMBER_TYPE_NORMAL_DAMEGE )
    {
        m_iFontSize = m_pDamegeSystem->GetNormalFontSize();
        m_FontColor = m_pDamegeSystem->GetNormalColor();
    }
    
    if( m_iType == NUMBER_TYPE_CRUSH_DAMEGE )
    {
        m_iFontSize = m_pDamegeSystem->GetCrushFontSize();
        m_FontColor = m_pDamegeSystem->GetCrushColor();
    }
    
    char t_sDamegeNumber[20];
    
    sprintf(t_sDamegeNumber, "%d",m_iNumber);
    
    m_pLabel = Label::createWithTTF(t_sDamegeNumber, m_sFontPath + m_sFontName, m_iFontSize);
    
    m_pLabel->setPosition(m_ObjectPosition);
    m_pLabel->setColor(m_FontColor);
    m_pLabel->retain();
    
    m_pBezier = m_pDamegeSystem->CreateBezier(1, m_ObjectPosition, Point(m_ObjectPosition.x + 100,m_ObjectPosition.y), 60);
    
    CallFunc * t_pCall      = CallFunc::create(CC_CALLBACK_0(CGDamegeNumber::MoveEndCallBack, this));
    
    m_pSequence             = Sequence::create(m_pBezier, t_pCall, NULL);
    m_pFade                 = FadeOut::create(1);
    
    CallFunc *  t_pFadeCall = CallFunc::create(CC_CALLBACK_0(CGDamegeNumber::DeadCallBack, this));
    
    m_pFadeSeq              = Sequence::create(m_pFade, t_pFadeCall, NULL);
    
    m_pFade->retain();
    m_pBezier->retain();
    m_pFadeSeq->retain();
    m_pSequence->retain();

    return true;
}

void CGDamegeNumber::MoveEndCallBack()
{
    m_pLabel->runAction(m_pFadeSeq);
}

void CGDamegeNumber::DeadCallBack()
{
    m_bIsDead = true;
}

bool CGDamegeNumber::CleareGObject()
{
    m_pLabel->release();
    m_pFade->release();
    m_pBezier->release();
    m_pSequence->release();
    m_pFadeSeq->release();
    m_pGameScene->removeChild(m_pLabel);
    return true;
}

bool CGDamegeNumber::DeleteGObject()
{
    m_pLabel->setVisible(false);
    delete this;
    return true;
}

void CGDamegeNumber::DrawGObject()
{
    if( m_bIsAddScene == false )
    {
        m_pGameScene->addChild(m_pLabel,DEEP_UI_NUMBER);
        m_pLabel->runAction(m_pSequence);
        m_bIsAddScene = true;
    }
    
    m_pLabel->setVisible(m_bObjectVisible);
    
    
}

