//
//  CGDamegeSystem.cpp
//  Game
//
//  Created by dongli on 2016/11/30.
//
//

#include "CGDamegeSystem.hpp"
#include <cocos2d.h>
#include "CGResManager.hpp"
#include "CGException.hpp"
#include "CGDamegeNumber.hpp"
using namespace cocos2d;

bool CGDamegeSystem::InitGObject()
{
    m_sFontPath       = CGResManager::sharedResManager()->GetFontPath();
    m_sDamegeFont     = "DamegeNumber5.ttf";
    m_iCrushFontSize  = 150;
    m_iNormalFontSize = 80;
    m_NormalColor     = Color3B(255,255,255);
    m_CrushColor      = Color3B(255,0,0);
    
    return true;
}

bool CGDamegeSystem::CleareGObject()
{
    return true;
}

bool CGDamegeSystem::DeleteGObject()
{
    delete this;
    return true;
}

void CGDamegeSystem::ProcessDamegeTask()
{
    if( ! m_vNumber.empty() )
    {
        for(auto i : m_vNumber)
        {
            i->DrawGObject();
        }
        
        auto it = m_vNumber.begin();
        
        for(;it != m_vNumber.end(); )
        {
            if( (*it)->GetIsDead() )
            {
                (*it)->DeleteGObject();
                
                m_vNumber.erase(it);
            }
            else
            {
                it++;
            }
        }
    }
}

BezierTo * CGDamegeSystem::CreateBezier(float fTime, const Point &Start, const Point &End, float fAngle)
{
    
    float t_Radian        = fAngle * 3.14159 / 180;
    float t_Control1X     = Start.x + (End.x - Start.x) / 4;
    float t_Control2X     = Start.x + (End.x - Start.x) / 2;
    
    Point t_ControlPoint1 = Point(t_Control1X,Start.y + cos(t_Radian) * t_Control1X);
    Point t_ControlPoint2 = Point(t_Control2X,Start.y + cos(t_Radian) * t_Control2X);
    
    ccBezierConfig t_Config;
    
    t_Config.controlPoint_1 = t_ControlPoint1;
    t_Config.controlPoint_2 = t_ControlPoint2;
    t_Config.endPosition    = End;
    
    auto t_pBezier          = BezierTo::create(fTime, t_Config);
    
    if( t_pBezier != nullptr )
    {
        return t_pBezier;
    }
    else
    {
        throw CGException("CreateBezier Is Error");
        return nullptr;
    }
}

void CGDamegeSystem::ShowDamegeNumber(int iNumber, int iType,const Point& Position)
{
    auto t_pNumber = CGDamegeNumber::CreateDamegeNumber(iNumber, iType, Position);
    
    m_vNumber.push_back(t_pNumber);
}
