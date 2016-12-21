//
//  CGPhysicsObject.hpp
//  Game
//
//  Created by dongli on 2016/12/2.
//
//

#ifndef CGPhysicsObject_hpp
#define CGPhysicsObject_hpp

#include <iostream>
#include <CGDataType.h>
#include <CGComObject.hpp>
#include <CGPhysicsManager.hpp>

class b2Body;
class CGScene;

class CG_CLASS CGPhysicsObject:public CGComObject
{
protected:
    CGPhysicsObject(int iType,int iWidth,int iHeight,float fX,float fY)
    {
        m_iPhysicsType      = iType;
        m_iPhysicsWidth     = iWidth;
        m_iPhysicsHeight    = iHeight;
        m_PhysicsPosition.x = fX;
        m_PhysicsPosition.y = fY;
        
        CG_DEBUG_PRINT("CGPhysicsObject Is Create")
    }
    
    CG_CONSTRUCTION_COPY(CGPhysicsObject)
    
public:
    CG_DESTROY_DEFAULT(CGPhysicsObject)
    
    static CGPhysicsObject * CreatePhysicsObject(int iType, int iWidth, int iHeight, float fX, float fY);
    
    CG_OVERLOAD_COM;
    
    CG_ACCESS_BOOL(IsDead);
    
    CG_RESULT_VOID ProcessPhysicsObject();
    
    CG_RESULT_VOID SetPhysicsPosition(const Point& Position);
    
    CG_RESULT_VOID ApplyForce(int iX,int iY);
    
    CG_ACCESS_FLOAT(PhysicsXSpeed)
    
    CG_ACCESS_FLOAT(PhysicsYSpeed)
    
    Rect GetPhysicsRect()const
    {
        return m_PhysicsRect;
    }
    
    Point GetPhysicsPosition()const
    {
        return m_PhysicsPosition;
    }
    
    CG_RESULT_VOID SetHorizontalSpeed(float fSpeed);
    
    CG_RESULT_VOID SetVerticalSpeed(float fSpeed);
    
protected:
    bool                        m_bIsDisplayRect;
    bool                        m_bIsDead;
    int                         m_iPhysicsType;
    int                         m_iPhysicsHeight;
    int                         m_iPhysicsWidth;
    float                       m_fPhysicsXSpeed;
    float                       m_fPhysicsYSpeed;
    CGScene *                   m_pGameScene;
    Point                       m_PhysicsPosition;
    DrawNode *                  m_pRectNode;
    Rect                        m_PhysicsRect;
    b2Body *                    m_pPhysicsBody;
    CGPhysicsManager *          m_pPhysicsManager;
};

#endif /* CGPhysicsObject_hpp */
