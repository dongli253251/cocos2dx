//
//  CGMonsterAI_LowSoldier.cpp
//  Game
//
//  Created by dongli on 2016/12/15.
//
//


#include "CGMonsterAI_LowSoldier.hpp"
#include "CGPirateSoldier.hpp"
#include "CGUIManager.hpp"


CGMonsterAI_LowSoldier * CGMonsterAI_LowSoldier::CreateLowSoldierAI(CGMonsterBase *pMonster)
{
    auto t_pMonster = new CGMonsterAI_LowSoldier(pMonster);
    
    if( t_pMonster != nullptr )
    {
        t_pMonster->InitGObject();
        
        return t_pMonster;
    }
    
    else
    {
        CG_DEBUG_PRINT("CGMonsterAI_LowSoldier Create Is Error");
        
        throw CGException("CGMonsterAI_LowSoldier Create Is Erro");
    }
}

bool CGMonsterAI_LowSoldier::InitGObject()
{
    m_iCurrentEventIndex = 1;
    m_iInterval          = 10;
    m_iEventCount        = 1;
    m_iLastTime          = 0;
    m_fXMovedCount       = 0.f;
    m_fYMovedCount       = 0.f;
    m_iMoveSpeed         = m_pSoldier->GetMoveSpeed();
    m_bIsBreakEvent      = false;
    m_bIsProcessPoint    = false;
    m_bIsRunEvent        = false;
    
    AddMoveEventToList(100, 2000, EVENT_TYPE_SEQUNCE);
    
    return true;
}

bool CGMonsterAI_LowSoldier::CleareGObject()
{
    return true;
}

bool CGMonsterAI_LowSoldier::DeleteGObject()
{
    delete this;
    return true;
}

void CGMonsterAI_LowSoldier::ProcessAITask()
{
    
    static long t_iLastTime = 0 ;
    
    if( GetMilliSecond() - t_iLastTime > 500 )
    {
        t_iLastTime = GetMilliSecond();
        
        if(CGUIManager::sharedUIManager()->GetLunchButtonIsTouch())
        {
            AddMoveEventToList(rand() % 3000, rand()% 3000, EVENT_TYPE_NOW);
        }
    }
    
    if( ! m_vEventList.empty() )
    {
        
        
        
        std::vector<STRUCT_AI_EVENT>::iterator it = m_vEventList.begin();
        
        m_it = it;
        
        for(; it != m_vEventList.end(); it++)
        {
            
            if( m_bIsBreakEvent == false )
            {
                if( it->iIndex == m_iCurrentEventIndex )
                {
                    
                    m_it = it;
                    
                    if( it->bIsOver == false )
                    {
                        
                        m_bIsRunEvent = true;
                        
                        switch(it->iEventName)
                        {
                            case AI_EVENT_MOVE:
                            {
                                
                                ProcessMoveEvent(*it);
                                
                                break;
                            }
                                
                            case AI_EVENT_STAND:
                            {
                                ProcessStandEvent(*it);
                                
                                break;
                            }
                        }
                        
                    }
                }
                
            }
            
            if( m_bIsBreakEvent == true )
            {
                if( m_bIsRunEvent )
                {
                    m_TargetPoint     = Point(0,0);
                    m_bIsRunEvent     = false;
                    m_bIsProcessPoint = false;
                    m_bIsBreakEvent   = false;
                    
                    m_fXMovedCount    = 0;
                    m_fYMovedCount    = 0;
                    m_fXSetup         = 0;
                    m_fYSetup         = 0;
                    m_fXRange         = 0;
                    m_fYRange         = 0;
                    
                    m_iCurrentEventIndex ++;
                    
                    m_pSoldier->SetAnimateState(ANIMATION_STATE_STAND);
                    
                    m_it->bIsOver = true;
                    

                }
                else
                {
                    m_bIsRunEvent     = false;
                    m_bIsProcessPoint = false;
                    m_bIsBreakEvent   = false;
                    m_fXMovedCount    = 0;
                    m_fYMovedCount    = 0;
                    m_fXSetup         = 0;
                    m_fYSetup         = 0;
                    m_fXRange         = 0;
                    m_fYRange         = 0;
                    m_TargetPoint     = Point(0,0);
                    
                    m_pSoldier->SetAnimateState(ANIMATION_STATE_STAND);
                }
                
            }
            
        }
    }
    
    if( ! m_vEventList.empty() )
    {
        auto it = m_vEventList.begin();
        
        for(; it != m_vEventList.end() ;)
        {
            if( it->bIsOver )
            {
                m_vEventList.erase(it);
                break;
            }
            
            else
            {
                it++;
            }
        }
    }
}


void CGMonsterAI_LowSoldier::ProcessPoint(STRUCT_AI_EVENT & Event)
{
    if( m_bIsProcessPoint == false )
    {
        m_TargetPoint = Point(Event.fPointX,Event.fPointY);

        m_fXRange     = m_TargetPoint.x - m_pSoldier->GetObjectPosition().x;
        m_fYRange     = m_TargetPoint.y - m_pSoldier->GetObjectPosition().y;

        if( m_fXRange < 0 )
        {
            m_pSoldier->SetOrientation(MONSTER_ORIENTATION_LEFT);
        }

        else if( m_fXRange > 0 )
        {
            m_pSoldier->SetOrientation(MONSTER_ORIENTATION_RIGHT);
        }
                                
                                   
        if( m_fXRange < 0 && m_fYRange < 0 )
        {
            if( m_fXRange * - 1 > m_fYRange * - 1 )
            {
                m_fXSetup = m_iMoveSpeed * - 1;
                m_fYSetup = m_fYRange / (m_fXRange / m_fXSetup);
            }

            if( m_fXRange * - 1 < m_fYRange * - 1)
            {
                m_fYSetup = m_iMoveSpeed  * - 1;
                m_fXSetup = m_fXRange / m_fYRange / m_fYSetup;
            }

            if( m_fXRange == m_fYRange )
            {
                m_fXSetup = m_iMoveSpeed * - 1;
                m_fYSetup = m_iMoveSpeed * - 1;
            }

        }

        if( m_fXRange > 0 && m_fYRange > 0 )
        {
            if( m_fXRange  > m_fYRange )
            {
                m_fXSetup = m_iMoveSpeed;
                m_fYSetup = m_fYRange / (m_fXRange / m_fXSetup);
            }

            if( m_fXRange < m_fYRange)
            {
                m_fYSetup = m_iMoveSpeed;
                m_fXSetup = m_fXRange / m_fYRange / m_fYSetup;
            }
            
            if( m_fXRange == m_fYRange )
            {
                m_fXSetup = m_iMoveSpeed;
                m_fYSetup = m_iMoveSpeed;
            }

        }

        if( m_fXRange > 0 && m_fYRange < 0 )
        {
            if( m_fXRange  > m_fYRange * - 1 )
            {
                m_fXSetup = m_iMoveSpeed;
                m_fYSetup = m_fYRange / (m_fXRange / m_fXSetup);
            }
            
            if( m_fXRange < m_fYRange * - 1 )
            {
                m_fYSetup = m_iMoveSpeed * - 1;
                m_fXSetup = m_fXRange / m_fYRange / m_fYSetup;
            }
            
            if( m_fXRange == m_fYRange * - 1 )
            {
                m_fXSetup = m_iMoveSpeed;
                m_fYSetup = m_iMoveSpeed * - 1;
            }
            
        }

        if( m_fXRange < 0 && m_fYRange > 0 )
        {
            if( m_fXRange * - 1 > m_fYRange )
            {
                m_fXSetup = m_iMoveSpeed * - 1;
                m_fYSetup = m_fYRange / (m_fXRange / m_fXSetup);
            }
            
            if( m_fXRange * - 1 < m_fYRange)
            {
                m_fYSetup = m_iMoveSpeed;
                m_fXSetup = m_fXRange / m_fYRange / m_fYSetup ;
            }
            
            if( m_fXRange * - 1 == m_fYRange )
            {
                m_fXSetup = m_iMoveSpeed * - 1;
                m_fYSetup = m_iMoveSpeed;
            }
            
        }

        m_bIsProcessPoint = true;
    }
}

void CGMonsterAI_LowSoldier::ProcessMoveEvent(STRUCT_AI_EVENT & Event)
{
    ProcessPoint(Event);

    if( m_fXRange < 0 )
    {
        m_fXRange *= - 1;
    }
    
    if( m_fYRange < 0 )
    {
        m_fYRange *= - 1;
    }
    
    if( m_fYMovedCount < m_fYRange && m_fXMovedCount < m_fXRange )
    {
        
        if( GetMilliSecond() - m_iLastTime >= m_iInterval )
        {
            m_iLastTime = GetMilliSecond();
            
            m_pSoldier->SetAnimateState(ANIMATION_STATE_MOVE);
            
            
            m_pSoldier->ApplyPosition(Point(m_fXSetup,m_fYSetup));
            
            if( m_fXSetup < 0 )
            {
                m_fXMovedCount += m_fXSetup * - 1;
            }
            
            else
            {
                m_fXMovedCount += m_fXSetup;
            }
            
            if( m_fYSetup < 0 )
            {
                m_fYMovedCount += m_fYSetup * - 1;
            }
            
            else
            {
                m_fYMovedCount += m_fYSetup;
            }
        }
        
        
    }
    
    
    if( m_fXMovedCount >= m_fXRange && m_fYMovedCount >= m_fYRange )
    {
        m_bIsProcessPoint = false;
        m_bIsRunEvent     = false;
        m_bIsBreakEvent   = false;
        Event.bIsOver     = true;
        m_TargetPoint     = Point(0,0);
        m_fXMovedCount    = 0;
        m_fYMovedCount    = 0;
        m_fXSetup         = 0;
        m_fYSetup         = 0;
        m_fXRange         = 0;
        m_fYRange         = 0;
        m_iCurrentEventIndex ++;
        
        m_pSoldier->SetAnimateState(ANIMATION_STATE_STAND);
    }

}

void CGMonsterAI_LowSoldier::ProcessStandEvent(STRUCT_AI_EVENT & Event)
{
    
}


void CGMonsterAI_LowSoldier::AddMoveEventToList(float fX, float fY, int iType)
{
    if( iType == EVENT_TYPE_NOW )
    {
        STRUCT_AI_EVENT t_Event;
        
        t_Event.iEventName = AI_EVENT_MOVE;
        t_Event.fPointX    = fX;
        t_Event.fPointY    = fY;
        t_Event.bIsOver    = false;
        t_Event.bIsRuning  = false;
        t_Event.iIndex     = m_iEventCount++;
        
        m_bIsBreakEvent    = true;
        
        m_vEventList.push_back(t_Event);
    }
    
    else if( iType == EVENT_TYPE_SEQUNCE )
    {
        STRUCT_AI_EVENT t_Event;
        
        t_Event.iEventName = AI_EVENT_MOVE;
        t_Event.fPointX    = fX;
        t_Event.fPointY    = fY;
        t_Event.bIsOver    = false;
        t_Event.bIsRuning  = false;
        t_Event.iIndex     = m_iEventCount++;
                
        m_vEventList.push_back(t_Event);

    }
}

void CGMonsterAI_LowSoldier::AddEventToList(int iName, float fPointX, float fPointY, int iRange, int iOrient, int iType)
{
    if( iType == EVENT_TYPE_NOW )
    {

            STRUCT_AI_EVENT t_Event(iName,iRange,iOrient,m_iEventCount ++);


            m_vEventList.push_back(t_Event);

            m_bIsBreakEvent = true;
    }

    else if( iType == EVENT_TYPE_SEQUNCE )
    {
        STRUCT_AI_EVENT t_Event(iName,iRange,iOrient,m_iEventCount ++);

        m_vEventList.push_back(t_Event);
        

    }
}

void CGMonsterAI_LowSoldier::SetDirveObject(CGMonsterBase *pMonster)
{
    m_pSoldier = dynamic_cast<CGPirateSoldier *>(pMonster);
}
