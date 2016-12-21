//
//  CGGraphicsObject.hpp
//  Game
//
//  Created by dongli on 2016/10/27.
//
//

#ifndef CGGraphicsObject_hpp
#define CGGraphicsObject_hpp

#include <stdio.h>
#include <iostream>
#include "CGObject.hpp"
#include <iostream>
#include "CGDataType.h"
using namespace cocos2d;

class CG_CLASS CGGraphicsObject:public CGObject
{
protected:
    CGGraphicsObject()
    {
        std::cout<<"CGGraphicObject Is Create"<<std::endl;
        
        m_bIsAddScene    = false;
        m_bObjectVisible = true;
        m_ObjectPosition.set(0, 0);
    }
    
    CG_CONSTRUCTION_COPY(CGGraphicsObject)
    /*
     *- Disable Default Construction Function.
     */
public:
    
    CG_DESTROY_DEFAULT(CGGraphicsObject)
    /*
     *- Destruction Function.
     */
public:
    
    virtual CG_RESULT_BOOL InitGObject()
    {
        return true;
    }
    /*
     *- init game object.
     */

    virtual CG_RESULT_BOOL CleareGObject()
    {
        return true;
    }
    
    virtual CG_RESULT_BOOL DeleteGObject()
    {
        return true;
    }
    
    virtual CG_RESULT_VOID DrawGObject()
    {
        
    }
    
    virtual CG_RESULT_VOID SetObjectPosition(const Point& Position)
    {
        m_ObjectPosition = Position;
    }
    
    virtual CG_RESULT_POINT_CREF GetObjectPosition()const
    {
        return m_ObjectPosition;
    }
    
    virtual CG_RESULT_VOID SetObjectPosition(float fx, float fy)
    {
        m_ObjectPosition.x = fx;
        m_ObjectPosition.y = fy;
    }
    
    
    CG_RESULT_VOID SetObjectVisible(bool b_Visible)
    {
        m_bObjectVisible = b_Visible;
    }
    
    
    CG_RESULT_INT GetObjectDeep()const
    {
        return m_iObjectDeep;
    }
    
    CG_RESULT_VOID SetObjectDeep(int iDeep)
    {
        m_iObjectDeep = iDeep;
    }
    
    CG_RESULT_BOOL GetObjectVisible()const
    {
        return m_bObjectVisible;
    }
    
    
    CG_RESULT_VOID SetIsAddScene(bool bIs)
    {
        m_bIsAddScene = bIs;
    }
    
    CG_RESULT_BOOL GetIsAddScene()const
    {
        return m_bIsAddScene;
    }
    
protected:
    Point           m_ObjectPosition;
    bool            m_bObjectVisible;
    bool            m_bIsAddScene;
    int             m_iObjectDeep;
};

#endif /* CGGraphicsObject_hpp */
