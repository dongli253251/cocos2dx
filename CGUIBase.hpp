//
//  CGUIBase.hpp
//  Game
//
//  Created by dongli on 2016/11/8.
//
//

#ifndef CGUIBase_hpp
#define CGUIBase_hpp

/**************************************************************
 * - 2016.11.15
 * - www.dongli.com
 *
 * - CGUIBase is Root Class of All CG UI Class.
 * - This Class Provoid Abstruct Interface for UI.
 * -
 * - this class must be pure virtual class.
 * - this class cannot alone instantiation and that must
 * - instantiation in subclass and make use of static createmethod.
 * - this class is an top class
 *
 **************************************************************/


#include <stdio.h>
#include <CGGraphicsObject.hpp>
#include <iostream>
#include "CGDataType.h"

class CG_CLASS CGUIBase:public CGGraphicsObject
{
protected:
    CGUIBase()
    {
        std::cout<<"CGUIBase Is Create"<<std::endl;
        m_iObjectDeep = DEEP_UI_DEFAULT;
        m_bIsCanWork  = true;
        
        m_TouchEndPoint.set(0, 0);
        m_TouchMovePoint.set(0, 0);
        m_TouchBeganPoint.set(0, 0);
    }
    
    CG_CONSTRUCTION_COPY(CGUIBase)
    
public:
    
    CG_DESTROY_DEFAULT(CGUIBase)
    
    virtual bool InitGObject()
    {
        return true;
    }
    
    virtual bool CleareGObject()
    {
        return true;
    }
    
    virtual void DrawGObject()
    {
        
    }
    
    virtual bool DeleteGObject()
    {
        delete this;
        return true;
    }
    
    void SetTouchBeganPoint(const Point& Point)
    {
        m_TouchBeganPoint = Point;
    }
    
    const Point& GetTouchBeganPoint()const
    {
        return m_TouchBeganPoint;
    }
    
    void SetTouchMovePoint(const Point& Point)
    {
        m_TouchMovePoint = Point;
    }
    
    const Point& GetTouchMovePoint()const
    {
        return m_TouchMovePoint;
    }
    
    void SetTouchEndPoint(const Point& Point)
    {
        m_TouchEndPoint = Point;
    }
    
    const Point& GetTouchEndPoint()const
    {
        return m_TouchEndPoint;
    }
    
    void SetCanWork(bool bWork)
    {
        m_bIsCanWork = bWork;
    }
    
    bool GetCanWork()const
    {
        return m_bIsCanWork;
    }
    
    int GetUIName()const
    {
        return m_iUIName;
    }
    
    void SetUIName(int iUIName)
    {
        m_iUIName = iUIName;
    }

    
protected:
    Point               m_TouchBeganPoint;
    Point               m_TouchEndPoint;
    Point               m_TouchMovePoint;
    bool                m_bIsCanWork;
    
    int                 m_iUIName;
};


#endif /* CGUIBase_hpp */
