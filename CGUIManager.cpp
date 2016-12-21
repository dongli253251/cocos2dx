//
//  CGUIManager.cpp
//  Game
//
//  Created by dongli on 2016/11/8.
//
//

#include "CGUIManager.hpp"
#include "CGDataType.h"
#include <iostream>
#include <cocos2d.h>
#include "CGButton.hpp"
#include "CGPowerButton.hpp"
#include "CGJoyStick.hpp"
#include "CGException.hpp"
using namespace cocos2d;

static CGUIManager * g_pUIManager = nullptr;


CGUIManager * CGUIManager::sharedUIManager()
{
    if( g_pUIManager == nullptr )
    {
        g_pUIManager = new CGUIManager();
        
        if( g_pUIManager != nullptr )
        {
            g_pUIManager->InitGObject();
            return g_pUIManager;
        }
    }
    else
    {
        return g_pUIManager;
    }
}


void CGUIManager::PushTouchInfo(const STRUCT_TOUCH_INFO &Info)
{
    m_vTouch.push_back(Info);
}

const std::vector<STRUCT_TOUCH_INFO>& CGUIManager::GetTouchVector()const
{
    return m_vTouch;
}

void CGUIManager::SetMovePointByID(int iID, const Point &Point)
{
    
    if( !m_vTouch.empty() )
    {
        bool t_bIsfind = false;
        
        for( int i = 0 ; i != m_vTouch.size() ; i ++ )
        {
            if( m_vTouch[i].uTouchID == iID )
            {
                m_vTouch[i].MovePoint = Point;
                t_bIsfind             = true;
            }
        }
        
        if( t_bIsfind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::SetMovePoint Is Can Not Find ID: ",iID);
            
            throw CGException("CGUIManager Is Error");
        }

    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");
    }
    
}

void CGUIManager::SetBeganPointByID(int iID, const Point &Point)
{
    
    if( ! m_vTouch.empty() )
    {
        bool t_bIsfind = false;
        
        for( int i = 0 ; i != m_vTouch.size() ; i ++ )
        {
            if( m_vTouch[i].uTouchID == iID )
            {
                m_vTouch[i].BeganPoint = Point;
                t_bIsfind              = true;
            }
        }
        
        if( t_bIsfind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::SetBeganPoint Is Can Not Find ID: ",iID);
            
            throw CGException("CGUIManager Is Error");
        }

    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");
    }
    
    
}

void CGUIManager::SetEndPointByID(int iID, const Point &Point)
{
    if( !m_vTouch.empty() )
    {
        bool t_bIsfind = false;
        
        for( int i = 0 ; i != m_vTouch.size() ; i ++ )
        {
            if( m_vTouch[i].uTouchID == iID )
            {
                m_vTouch[i].EndPoint = Point;
                t_bIsfind             = true;
            }
        }
        
        if( t_bIsfind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::SetEndPoint Is Can Not Find ID: ",iID);
            
            throw CGException("CGUIManager Is Error");
        }

    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");
    }

}

void CGUIManager::SetIsEndByID(int iID, bool bIs)
{
    if( !m_vTouch.empty() )
    {
        bool t_bIsfind = false;
        
        for( int i = 0 ; i != m_vTouch.size() ; i ++ )
        {
            if( m_vTouch[i].uTouchID == iID )
            {
                m_vTouch[i].bIsEnd = bIs;
                t_bIsfind          = true;
            }
        }
        
        if( t_bIsfind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::SetIsEnd Is Can Not Find ID: ",iID);
            
            throw CGException("CGUIManager Is Error");
        }

    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");
    }
}


const Point& CGUIManager::GetMovePointByID(int iID)const
{
    
    if( !m_vTouch.empty() )
    {
        bool t_bIsfind = false;
        
        for( auto i : m_vTouch )
        {
            if( i.uTouchID == iID )
            {
                t_bIsfind   = true;
                return i.MovePoint;
            }
        }
        
        if( t_bIsfind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::GetMovePoint Is Can Not Find ID: ",iID);
            
            throw CGException("CGUIManager Is Error");
        }

    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");
    }
}

const Point& CGUIManager::GetBeganPointByID(int iID)const
{
    if( !m_vTouch.empty() )
    {
        
        bool t_bIsfind = false;
        
        for( auto i : m_vTouch )
        {
            if( i.uTouchID == iID )
            {
                t_bIsfind   = true;
                return i.BeganPoint;
            }
        }
        
        if( t_bIsfind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::GetBeganPoint Is Can Not Find ID: ",iID);
            
            throw CGException("CGUIManager Is Error");
        }

    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");
    }
}

const Point& CGUIManager::GetEndPointByID(int iID)const
{
    
    if( !m_vTouch.empty() )
    {
        bool t_bIsfind = false;
        
        for( auto i : m_vTouch )
        {
            if( i.uTouchID == iID )
            {
                t_bIsfind   = true;
                return i.EndPoint;
            }
        }
        
        if( t_bIsfind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::GetEndPoint Is Can Not Find ID: ",iID);
            
            throw CGException("CGUIManager Is Error");
        }

    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");
    }

}


const Point& CGUIManager::GetEndPointByOnlyCount(unsigned long uCount)const
{
    
    if( !m_vTouch.empty() )
    {
        bool t_bIsFind = false;
        
        for( auto i : m_vTouch )
        {
            if( i.uOnlyCount == uCount )
            {
                t_bIsFind = true;
                return i.EndPoint;
            }
        }
        
        if( t_bIsFind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::GetEndPointByCount",uCount);
            throw CGException("CGUIManager Is Error");
        }

    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");

    }
    
}

const Point& CGUIManager::GetMovePointByOnlyCount(unsigned long uCount)const
{
    if( ! m_vTouch.empty() )
    {
        bool t_bIsFind = false;
        
        for( auto i : m_vTouch )
        {
            if( uCount == i.uOnlyCount )
            {
                t_bIsFind = true;
                return i.MovePoint;
            }
        }
        
        if( t_bIsFind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::GetMovePointCount", uCount);
            throw CGException("CGUIManager TouchVec Is Empty");
        }

    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");
    }
    
}

const Point& CGUIManager::GetBeganPointByOnlyCount(unsigned long uCount)const
{
    if( !m_vTouch.empty() )
    {
        bool t_bIsFind = false;
        
        for( auto i : m_vTouch )
        {
            if( uCount == i.uOnlyCount )
            {
                t_bIsFind = true;
                return i.BeganPoint;
            }
        }
        
        if( t_bIsFind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::GetBeganPointCount", uCount);
            throw CGException("CGUIManager Is Error");
        }

    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");
    }
}


long CGUIManager::GetOnlyCountByRect(const Rect &Rect)const
{
    if( !m_vTouch.empty() )
    {
        bool t_bIsFind = false;
        
        for( auto i : m_vTouch )
        {
            if( Rect.containsPoint(i.BeganPoint) )
            {
                t_bIsFind = true;
                return i.uOnlyCount;
            }
        }
        
        if( t_bIsFind == false )
        {
            return 0;
        }
    }
    else
    {
        throw CGException("CGUIManager TouchVec Is Empty");
    }
   
    
    return 0;
}

bool CGUIManager::GetTouchVecIsEmpty()const
{
    return m_vTouch.empty();
}

void CGUIManager::SetIsEndByOnlyCount(long uCount, bool bIs)
{
    if( !m_vTouch.empty() )
    {
        bool t_bIsFind = false;
        
        for( int i = 0 ; i != m_vTouch.size() ; i ++ )
        {
            if( m_vTouch[i].uOnlyCount == uCount)
            {
                m_vTouch[i].bIsEnd = bIs;
                t_bIsFind          = true;
            }
        }

        if( t_bIsFind == false )
        {
            CG_DEBUG_PRINT_1("CGUIManager::SetIsEndByCount Is Can Not Find ID: ", uCount);
            
            throw CGException("CGUIManager Is Error");
        }
        else
        {
            auto it = m_vTouch.begin();
            
            for( ; it != m_vTouch.end(); )
            {
                if( (it)->bIsEnd == true )
                {
                    m_vTouch.erase(it);
                    /// bug ?? ,only can delete once.
                    break;
                }
                else
                {
                    it++;
                }
            }

        }
    }
    else
    {
        throw CGException("Touch Vec Is Empty");
    }
}


void CGUIManager::ProcessUITask()
{
    
    if( m_vTouch.empty() == false )
    {
        auto it = m_vTouch.begin();
        
        for( ; it != m_vTouch.end(); )
        {
            if( (it)->bIsEnd == true )
            {
                m_vTouch.erase(it);
                /// bug ?? ,only can delete once.
                break;
            }
            else
            {
                it++;
            }
        }
        
        auto it1 = m_vTouch.begin();
        
        for( ; it1 != m_vTouch.end(); )
        {
            if( (it1)->bIsEnd == true )
            {
                m_vTouch.erase(it1);
                /// bug ?? ,only can delete once.
                break;
            }
            else
            {
                it1++;
            }
        }

    }
    
    
    
    /*
     *- Delete Invaild Touch Point in mvTouch.
     *- End Point Cause Invaild.
     */
    
    if( m_vUIVector.empty() == false )
    {
        auto i = m_vUIVector.begin();
        
        for(; i != m_vUIVector.end(); i++)
        {
            (*i)->DrawGObject();
            
            if( (*i)->GetUIName() == UI_ONLY_ID_POWER_BUTTON )
            {
                m_bPowerButtonIsTouch = ((CGPowerButton *)(*i))->GetButtonIsTouch();
            }
            
            if( (*i)->GetUIName() == UI_ONLY_ID_JOYSTICK )
            {
                m_iJoyStickValue = ((CGJoyStick *)(*i))->GetJoyStickValue();
            }
            
            if( (*i)->GetUIName() == UI_ONLY_ID_BULLET )
            {
                m_bLunchButtonIsTouch = ((CGPowerButton *)(*i))->GetButtonIsTouch();
            }
        }
        
    }
    
    
    /*
    if( m_TouchEndPoint != Point(0,0) )
    {
        m_TouchBeganPoint.set(0, 0);
        m_TouchEndPoint.set(0, 0);
        m_TouchMovePoint.set(0, 0);
    }
    
    */
}

void CGUIManager::AddUIToList(CGUIBase *pUI)
{
    bool t_bIsRep = false;
    
    for( int i = 0; i != m_vUIVector.size(); i++ )
    {
        if( m_vUIVector[i] == pUI )
        {
            t_bIsRep = true;
        }
    }
    if( t_bIsRep == false )
    {
        m_vUIVector.push_back(pUI);
    }
}

bool CGUIManager::InitGObject()
{
    m_bPowerButtonIsTouch = false;
    
    
    //m_TouchBeganPoint.set(0, 0);
    //m_TouchEndPoint.set(0, 0);
    //m_TouchMovePoint.set(0, 0);
    
    
    return true;
}

bool CGUIManager::CleareGObject()
{
    return true;
}

bool CGUIManager::DeleteGObject()
{
    delete this;
    return true;
}

