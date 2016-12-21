//
//  CGGlobalDateManager.hpp
//  Game
//
//  Created by dongli on 2016/11/21.
//
//

#ifndef CGGlobalDateManager_hpp
#define CGGlobalDateManager_hpp

#include <stdio.h>
#include <iostream>
#include "CGDataType.h"
#include "CGComObject.hpp"


class CG_CLASS CGGlobalDateManager:public CGComObject
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGGlobalDateManager)
    
    CG_CONSTRUCTION_COPY(CGGlobalDateManager)
    
public:
    
    CG_DESTROY_DEFAULT(CGGlobalDateManager)
    
    CG_OVERLOAD_COM
    
    CG_SINGLETON_CREATE(GlobalDateManager)
    
    CG_ACCESS_BOOL(BulletLunchSuccess);
    
    CG_ACCESS_BOOL(CanGameStart);
    
    CG_ACCESS_BOOL(IsGameOver);
    
    CG_ACCESS_BOOL(ItemUseSuccess);
    
    CG_ACCESS_BOOL(CreateRoomSuccess);
    
    Point GetNearBasePoint()const
    {
        return m_NearBasePoint;
    }
    
    CG_RESULT_VOID SetNearBasePoint(const Point& Point)
    {
        m_NearBasePoint = Point;
    }
protected:
    
    bool                m_bCreateRoomSuccess;
    bool                m_bBulletLunchSuccess;
    bool                m_bCanGameStart;
    bool                m_bIsGameOver;
    bool                m_bItemUseSuccess;
    Point               m_NearBasePoint;
    
};

#endif /* CGGlobalDateManager_hpp */
