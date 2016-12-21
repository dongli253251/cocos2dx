//
//  CGStateSystem.cpp
//  Game
//
//  Created by dongli on 2016/12/10.
//
//

#include "CGStateSystem.hpp"
#include "CGScene.hpp"
#include "CGResManager.hpp"
#include "CGPlayerDateManager.hpp"
#include "CGUIManager.hpp"

extern CGScene * GetGScene();

bool CGStateSystem::InitGObject()
{
    m_pGameScene         = GetGScene();
    m_pResManager        = CGResManager::sharedResManager();
    m_pDateManager       = CGPlayerDateManager::sharedPlayerDateManager();
    m_pUIManager         = CGUIManager::sharedUIManager();
    m_sUIPath            = m_pResManager->GetUIResPath();
    m_iScreenHeight      = m_pResManager->GetUISizeByName(UI_SIZE_SCREEN_HEIGHT);
    m_iScreenWidth       = m_pResManager->GetUISizeByName(UI_SIZE_SCREEN_WIDTH);
    m_sLifeBarNormal     = m_pResManager->GetUITextureString(UI_LIFE_BAR_NORMAL);
    m_sArmorBarNormal    = m_pResManager->GetUITextureString(UI_ARMOR_BAR_NORMAL);
    m_sTempBarNormal     = m_pResManager->GetUITextureString(UI_TEMP_BAR_NORMAL);
    m_sProgressDown      = m_pResManager->GetUITextureString(UI_LIFE_BAR_DOWN);
    m_fCurrentLife       = m_pDateManager->GetPlayerLife();
    m_fCurrentArmor      = m_pDateManager->GetPlayerArmor();
    m_fCurrentTemp       = m_pDateManager->GetPlayerTemp();
    m_fMaxLife           = m_pDateManager->GetPlayerMaxLife();
    m_fMaxTemp           = m_pDateManager->GetPlayerMaxTemp();
    m_fMaxArmor          = m_pDateManager->GetPlayerMaxArmor();
    m_pLifeBarNormal     = Sprite::create(m_sUIPath + m_sLifeBarNormal);
    m_pArmorBarNormal    = Sprite::create(m_sUIPath + m_sArmorBarNormal);
    m_pTempBarNormal     = Sprite::create(m_sUIPath + m_sTempBarNormal);
    m_pLifeBarDown       = Sprite::create(m_sUIPath + m_sProgressDown);
    m_pArmorBarDown      = Sprite::create(m_sUIPath + m_sProgressDown);
    m_pTempBarDown       = Sprite::create(m_sUIPath + m_sProgressDown);
    m_pLifeProgress      = ProgressTimer::create(m_pLifeBarNormal);
    m_pArmorProgress     = ProgressTimer::create(m_pArmorBarNormal);
    m_pTempProgress      = ProgressTimer::create(m_pTempBarNormal);
    m_LifePosition       = Point(170,m_iScreenHeight - 30);
    m_ArmorPosition      = Point(170,m_iScreenHeight - 72);
    m_TempPosition       = Point(170,m_iScreenHeight - 114);
    m_iLastLife          = m_pDateManager->GetPlayerLife();
    m_iLastArmor         = m_pDateManager->GetPlayerArmor();
    
    m_fAddIntervalTime        = 0.05f;
    m_fReduceIntervalTime     = 0.1f;
    m_fLifeReduceIntervalTime = 0.1f;
    m_fLifeAddIntervalTime    = 0.05f;
    m_fArmorAddIntervalTime   = 0.05f;
    m_fArmorReduceIntervalTime= 0.1f;
    m_bLifeStandby            = false;
    m_bArmorStandby           = false;
    m_bTempStandby            = false;
    m_bStartReduceTemp        = false;
    m_bCanAddTemp             = true;
    m_bCanReduceTemp          = true;
    m_iCurrentLifeIndex       = 1;
    m_iCurrentTempIndex       = 1;
    m_iCurrentArmorIndex      = 1;
    m_iTempCount              = 1;
    m_iLifeCount              = 1;
    m_iArmorCount             = 1;
    
    m_pLifeProgress->setMidpoint(Point(0,0));
    m_pLifeProgress->setBarChangeRate(Point(1,0));
    m_pLifeProgress->setType(ProgressTimer::Type::BAR);
    m_pTempProgress->setType(ProgressTimer::Type::BAR);
    m_pTempProgress->setMidpoint(Point(0,0));
    m_pTempProgress->setBarChangeRate(Point(1,0));
    m_pArmorProgress->setType(ProgressTimer::Type::BAR);
    m_pArmorProgress->setMidpoint(Point(0,0));
    m_pArmorProgress->setBarChangeRate(Point(1,0));
    
    m_pTempProgress->retain();
    m_pLifeProgress->retain();
    m_pArmorProgress->retain();
    m_pTempBarDown->retain();
    m_pArmorBarDown->retain();
    m_pLifeBarDown->retain();

    m_pTempProgress->setPosition(m_TempPosition);
    m_pTempProgress->setPercentage(0);
    m_pLifeProgress->setPosition(m_LifePosition);
    m_pLifeProgress->setPercentage(100);
    m_pArmorProgress->setPercentage(100);
    m_pArmorProgress->setPosition(m_ArmorPosition);
    
    m_pArmorBarDown->setPosition(m_ArmorPosition);
    m_pLifeBarDown->setPosition(m_LifePosition);
    m_pTempBarDown->setPosition(m_TempPosition);
    
    return true;
}

bool CGStateSystem::CleareGObject()
{
    m_pTempProgress->release();
    m_pLifeProgress->release();
    m_pArmorProgress->release();
    m_pLifeBarDown->release();
    m_pArmorBarDown->release();
    m_pTempBarDown->release();
    return true;
}

void CGStateSystem::AddLifeValue(float fValue)
{
    float t_fPercentage     = fValue / m_fMaxLife;
    int   t_iPercentage     = t_fPercentage * 100;
    
    STRUCT_PROGRESS t_Progress(t_iPercentage,PROGRESS_TYPE_ADD,m_iLifeCount++);
    
    t_Progress.iValue = fValue;
    
    m_vLifeList.push_back(t_Progress);
    
}

void CGStateSystem::AddArmorValue(float fValue)
{
    float t_fPercentage     = fValue / m_fMaxArmor;
    int   t_iPercentage     = t_fPercentage * 100;
    
    STRUCT_PROGRESS t_Progress(t_iPercentage,PROGRESS_TYPE_ADD,m_iArmorCount++);
    
    t_Progress.iValue = fValue;
    
    m_vArmorList.push_back(t_Progress);
}

void CGStateSystem::AddTempValue(float fValue)
{
    static ULONG t_LastTime   = 0;
    static int   t_iTimeCount = 0;
    static bool  t_bCanNew    = true;
    
    if( m_pUIManager->GetPowerButtonIsTouch() )
    {
        if( m_fCurrentTemp < m_fMaxTemp )
        {
            if( GetMilliSecond() - t_LastTime > 10 )
            {
                t_iTimeCount += 10;
                t_LastTime    = GetMilliSecond();
            }
            
            if( t_iTimeCount >= 50 )
            {
                
                t_iTimeCount          = 0;
                float t_fPercentage   = fValue / m_fMaxTemp;
                int   t_iPercentage   = t_fPercentage * 100;
                
                STRUCT_PROGRESS t_Progress(t_iPercentage,PROGRESS_TYPE_ADD, m_iTempCount++);
                
                t_Progress.iValue = fValue;
                
                m_vTempList.push_back(t_Progress);
                
            }
            
            else if( t_iTimeCount < 50 )
            {
                if( t_bCanNew )
                {
                    float t_fPercentage         = fValue / m_fMaxTemp;
                    int   t_iPercentage         = t_fPercentage * 100;
                    
                    STRUCT_PROGRESS t_Progress(t_iPercentage,PROGRESS_TYPE_ADD, m_iTempCount++);
                    
                    t_Progress.iValue = fValue;
                    
                    m_vTempList.push_back(t_Progress);
                    
                    t_bCanNew = false;
                }
            }
        }
    }
    else
    {
        t_bCanNew    = true;
        t_iTimeCount = 0;
        t_LastTime   = GetMilliSecond();
    }
}

void CGStateSystem::ReduceTempValue(float fValue)
{
    static ULONG t_iLastTime  = 0;
    static ULONG t_iLastTime2 = 0;
    if( m_pUIManager->GetPowerButtonIsTouch() == false )
    {
        if( m_fCurrentTemp > 0)
        {
            if( GetMilliSecond() - t_iLastTime > 500)
            {
                t_iLastTime        = GetMilliSecond();
                m_bStartReduceTemp = true;
            }
            
            if( m_bStartReduceTemp )
            {
                if( GetMilliSecond() - t_iLastTime2 > 100)
                {
                    float t_fPercentage   = fValue / m_fMaxTemp;
                    int   t_iPercentage   = t_fPercentage * 100;
                    
                    STRUCT_PROGRESS t_Progress(t_iPercentage,PROGRESS_TYPE_REDUCE,m_iTempCount++);
                    
                    t_Progress.iValue     = fValue;
                    
                    m_vTempList.push_back(t_Progress);
                    
                    t_iLastTime2 = GetMilliSecond();
                }
                
            }

        }
    }
    else
    {
        m_bStartReduceTemp = false;
        t_iLastTime        = GetMilliSecond();
    }
    
    
}

void CGStateSystem::ReduceArmorValue(float fValue)
{
    float t_fPercentage     = fValue / m_fMaxArmor;
    int   t_iPercentage     = t_fPercentage * 100;
    
    STRUCT_PROGRESS t_Progress(t_iPercentage,PROGRESS_TYPE_REDUCE,m_iArmorCount++);
    
    t_Progress.iValue = fValue;
    
    m_vArmorList.push_back(t_Progress);

}

void CGStateSystem::ReducsLifeValue(float fValue)
{
    float t_fPercentage     = fValue / m_fMaxLife;
    int   t_iPercentage     = t_fPercentage * 100;
    
    STRUCT_PROGRESS t_Progress(t_iPercentage,PROGRESS_TYPE_REDUCE,m_iLifeCount++);
    
    t_Progress.iValue = fValue;
    
    m_vLifeList.push_back(t_Progress);
}

void CGStateSystem::DrawGObject()
{
    if( ! m_bIsAddScene )
    {
        m_bIsAddScene = true;
        
        m_pGameScene->addChild(m_pLifeProgress,DEEP_UI_DEFAULT);
        m_pGameScene->addChild(m_pArmorProgress,DEEP_UI_DEFAULT);
        m_pGameScene->addChild(m_pTempProgress,DEEP_UI_DEFAULT);
        m_pGameScene->addChild(m_pTempBarDown,DEEP_UI_DEFAULT - 1);
        m_pGameScene->addChild(m_pLifeBarDown,DEEP_UI_DEFAULT - 1);
        m_pGameScene->addChild(m_pArmorBarDown,DEEP_UI_DEFAULT - 1);
    }
    
    m_fMaxTemp         = m_pDateManager->GetPlayerMaxTemp();
    m_fMaxLife         = m_pDateManager->GetPlayerMaxLife();
    m_fMaxArmor        = m_pDateManager->GetPlayerMaxArmor();
    
    int t_iAddValue    = m_pDateManager->GetPlayerTempAddValue();
    int t_iReducaValue = m_pDateManager->GetPlayerTempReduceValue();
    
    int t_iCurrentLife = m_pDateManager->GetPlayerLife();
    
    if( m_iLastLife != t_iCurrentLife )
    {
        int t_iMinusValue = m_iLastLife - t_iCurrentLife;
        
        if( t_iMinusValue <= 0 )
        {
            AddLifeValue(t_iMinusValue);
        }
        
        if( t_iMinusValue >= 0 )
        {
            ReducsLifeValue(t_iMinusValue);
        }
        
        m_iLastLife = t_iCurrentLife;
    }
    
    int t_iCurrentArmor = m_pDateManager->GetPlayerArmor();
    
    if( m_iLastArmor != t_iCurrentArmor )
    {
        int t_iMinusValue = m_iLastArmor - t_iCurrentArmor;
        
        if( t_iMinusValue <= 0 )
        {
            AddArmorValue(t_iMinusValue);
        }
        
        if( t_iMinusValue >= 0 )
        {
            ReduceArmorValue(t_iMinusValue);
        }
        
        m_iLastArmor = t_iCurrentArmor;
    }
    
    if( ! m_vArmorList.empty() )
    {
        auto it = m_vArmorList.begin();
        
        for(; it != m_vArmorList.end(); it++ )
        {
            if( it->iProgressIndex == m_iCurrentArmorIndex )
            {
                if( it->bIsOver == false )
                {
                    if( it->bIsRuning == false )
                    {
                        it->bIsRuning = true;
                        
                        if( it->iProgressType == PROGRESS_TYPE_REDUCE )
                        {
                            int t_iLastPer    = m_pArmorProgress->getPercentage();
                            int t_iCurrentPer = t_iLastPer - it->iPercentageValue;
                            
                            ProgressTo * t_pTo = ProgressTo::create(m_fArmorReduceIntervalTime, t_iCurrentPer);
                            
                            CallFunc * t_pCall = CallFunc::create(CC_CALLBACK_0(CGStateSystem::ArmorCallBack, this));
                            
                            Sequence * t_pSeq  = Sequence::create(t_pTo, t_pCall, NULL);
                            
                            m_pArmorProgress->runAction(t_pSeq);
                        }
                        
                        if( it->iProgressType == PROGRESS_TYPE_ADD )
                        {
                            int t_iLastPer    = m_pArmorProgress->getPercentage();
                            int t_iCurrentPer = t_iLastPer + it->iPercentageValue;
                            
                            ProgressTo * t_pTo = ProgressTo::create(m_fArmorReduceIntervalTime, t_iCurrentPer);
                            
                            CallFunc * t_pCall = CallFunc::create(CC_CALLBACK_0(CGStateSystem::ArmorCallBack, this));
                            
                            Sequence * t_pSeq  = Sequence::create(t_pTo, t_pCall, NULL);
                            
                            m_pArmorProgress->runAction(t_pSeq);
                        }
                    }
                }
            }
        }
    }
    
    if( ! m_vLifeList.empty() )
    {
        auto it = m_vLifeList.begin();
        
        for(;it != m_vLifeList.end(); it++ )
        {
            if( it->iProgressIndex == m_iCurrentLifeIndex )
            {
                if( it->bIsOver == false )
                {
                    if( it->bIsRuning == false )
                    {
                        it->bIsRuning = true;
                        
                        if( it->iProgressType == PROGRESS_TYPE_REDUCE )
                        {
                            int t_iLastPer    = m_pLifeProgress->getPercentage();
                            int t_iCurrentPer = t_iLastPer - it->iPercentageValue;
                            
                            ProgressTo * t_pTo = ProgressTo::create(m_fLifeReduceIntervalTime, t_iCurrentPer);
                            
                            CallFunc * t_pCall = CallFunc::create(CC_CALLBACK_0(CGStateSystem::LifeCallBack, this));
                            
                            Sequence * t_pSeq  = Sequence::create(t_pTo, t_pCall, NULL);
                            
                            m_pLifeProgress->runAction(t_pSeq);
                        }
                        
                        if( it->iProgressType == PROGRESS_TYPE_ADD )
                        {
                            int t_iLastPer    = m_pLifeProgress->getPercentage();
                            int t_iCurrentPer = t_iLastPer + it->iPercentageValue;
                            
                            ProgressTo * t_pTo = ProgressTo::create(m_fLifeReduceIntervalTime, t_iCurrentPer);
                            
                            CallFunc * t_pCall = CallFunc::create(CC_CALLBACK_0(CGStateSystem::LifeCallBack, this));
                            
                            Sequence * t_pSeq  = Sequence::create(t_pTo, t_pCall, NULL);
                            
                            m_pLifeProgress->runAction(t_pSeq);
                        }
                    }
                }
            }
        }
    }

    if( m_bCanAddTemp )
    {
        AddTempValue(t_iAddValue);
    }
    
    if( m_bCanReduceTemp )
    {
        ReduceTempValue(t_iReducaValue);
    }

    CG_DEBUG_PRINT_1("CurrentTemp: ", m_fCurrentTemp);
    CG_DEBUG_PRINT_1("DateTemp: ", m_pDateManager->GetPlayerTemp());
    CG_DEBUG_PRINT_1("CurrentLife: ", m_fCurrentLife);
    CG_DEBUG_PRINT_1("DateLife: ", m_pDateManager->GetPlayerLife());
    CG_DEBUG_PRINT_1("CurrentArmor: ", m_fCurrentArmor);
    CG_DEBUG_PRINT_1("DateArmor: ", m_pDateManager->GetPlayerArmor());
    
    if( ! m_vTempList.empty() )
    {
        auto it = m_vTempList.begin();
        
        for(; it != m_vTempList.end(); it++)
        {
            if( it->iProgressIndex == m_iCurrentTempIndex )
            {
                if( it->bIsOver == false )
                {
                    if( it->bIsRuning == false )
                    {
                        it->bIsRuning = true;
                        ///runing
                        
                        if( it->iProgressType == PROGRESS_TYPE_ADD )
                        {
                            int t_iLastPercentage    = m_pTempProgress->getPercentage();
                            int t_iCurrentPercentage = t_iLastPercentage + it->iPercentageValue;
                            
                            ProgressTo * t_pTo = ProgressTo::create(m_fAddIntervalTime, t_iCurrentPercentage);
                            
                            CallFunc * t_pCall = CallFunc::create(CC_CALLBACK_0(CGStateSystem::TempCallBack, this));
            
                            Sequence * t_pSeq  = Sequence::create(t_pTo, t_pCall, NULL);
                            
                            m_pTempProgress->runAction(t_pSeq);
                        }
                        
                        if( it->iProgressType == PROGRESS_TYPE_REDUCE )
                        {
                            int t_iLastPercentage    = m_pTempProgress->getPercentage();
                            int t_iCurrentPercentage = t_iLastPercentage - it->iPercentageValue;
                            
                            ProgressTo * t_pTo   = ProgressTo::create(m_fReduceIntervalTime, t_iCurrentPercentage);
                            
                            CallFunc * t_pCall = CallFunc::create(CC_CALLBACK_0(CGStateSystem::TempCallBack, this));
                            
                            Sequence * t_pSeq  = Sequence::create(t_pTo, t_pCall, NULL);
                            
                            m_pTempProgress->runAction(t_pSeq);

                        }
                    }

                }
            }
        }
    }
    
    if( ! m_vLifeList.empty() )
    {
        auto it = m_vLifeList.begin();
        
        for(; it != m_vLifeList.end() ; )
        {
            if( it->bIsOver == true )
            {
                m_vLifeList.erase(it);
                break;
            }
            else
            {
                it++;
            }
        }
    }
    
    if( ! m_vArmorList.empty() )
    {
        auto it = m_vArmorList.begin();
        
        for(; it != m_vArmorList.end() ; )
        {
            if( it->bIsOver == true )
            {
                m_vArmorList.erase(it);
                break;
            }
            else
            {
                it++;
            }
        }
    }
    
    if( ! m_vTempList.empty() )
    {
        auto it = m_vTempList.begin();
        
        for(; it != m_vTempList.end(); )
        {
            if( it->bIsOver == true )
            {
                if( it->iProgressType == PROGRESS_TYPE_REDUCE )
                {
                    m_fCurrentTemp -= it->iValue;
                    
                    m_pDateManager->ReducePlayerTemp(it->iValue);
                }
                else if( it->iProgressType == PROGRESS_TYPE_ADD )
                {
                    m_fCurrentTemp += it->iValue;
                    
                    m_pDateManager->AddPlayerTemp(it->iValue);
                }
                
                if( m_fCurrentTemp < 0 )
                {
                    m_fCurrentTemp = 0;
                }
                
                if( m_fCurrentTemp > m_fMaxTemp )
                {
                    m_fCurrentTemp = m_fMaxTemp;
                }
            
                m_vTempList.erase(it);
                break;
            }
            else
            {
                it++;
            }
        }
    }
}

void CGStateSystem::TempCallBack()
{
    auto it = m_vTempList.begin();
    
    for(; it != m_vTempList.end() ; it++)
    {
        if( it->iProgressIndex == m_iCurrentTempIndex )
        {
            it->bIsOver = true;
            
            break;
        }
    }
    
    m_iCurrentTempIndex ++;
}

void CGStateSystem::LifeCallBack()
{
    if( ! m_vLifeList.empty() )
    {
        auto it = m_vLifeList.begin();
        
        for(; it != m_vLifeList.end(); it++)
        {
            if( it->iProgressIndex == m_iCurrentLifeIndex )
            {
                it->bIsOver = true;
                break;
            }
        }
    }
    
    m_iCurrentLifeIndex ++;
}

void CGStateSystem::ArmorCallBack()
{
    if( ! m_vArmorList.empty() )
    {
        auto it = m_vArmorList.begin();
        
        for(; it != m_vArmorList.end() ; it ++ )
        {
            if( it->iProgressIndex == m_iCurrentArmorIndex )
            {
                it->bIsOver = true;
                break;
            }
        }
    }
    
    m_iCurrentArmorIndex ++;
}

bool CGStateSystem::DeleteGObject()
{
    delete this;
    return true;
}
