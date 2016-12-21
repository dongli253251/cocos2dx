//
//  CGJoyStick.hpp
//  Game
//
//  Created by dongli on 2016/11/13.
//
//

#ifndef CGJoyStick_hpp
#define CGJoyStick_hpp

#include <stdio.h>
#include <iostream>
#include "CGDataType.h"
#include "CGUIBase.hpp"
#include <cocos2d.h>

using namespace cocos2d;
class CGScene;
class CGUIManager;
class CGJoyStick:public CGUIBase
{
protected:
    explicit CGJoyStick(int iType)
    {
        m_iJoyStickType = iType;
    }
    CGJoyStick(const CGJoyStick& rhs)
    {
    
    }
public:
    virtual ~CGJoyStick()
    {
        CleareGObject();
    }
    
    static CGJoyStick * CreateJoyStick(int iType);
    
    CG_OVERLOAD_GRAPHICS;
    
    void SetTouchAnchor(bool bIs)
    {
        m_bTouchAnchor = bIs;
    }
    
    bool GetTouchAnchor()const
    {
        return m_bTouchAnchor;
    }
    
    void SetCenterPoint(const Point& Point)
    {
        m_CenterPoint = Point;
    }
    
    const Point& GetCenterPoint()const
    {
        return m_CenterPoint;
    }
    
    const Rect& GetJoyStickRect()const
    {
        return m_JoyStickRect;
    }
    
    const Rect& GetValidRect()const
    {
        return m_ValidRect;
    }
    
    void SetJoyStickValue(int iValue)
    {
        m_iJoyStickValue = iValue;
    }
    
    int GetJoyStickValue()const
    {
        return m_iJoyStickValue;
    }
    
protected:
    int             m_iJoyStickWidth;
    int             m_iJoyStickHeight;
    int             m_iJoyStickType;
    int             m_iJoyStickValue;
    long            m_lOnlyCount;
    bool            m_bTouchAnchor;
    bool            m_bIsLockPoint;
    bool            m_bCanSetBottom;
    bool            m_bCanSetBall;
    bool            m_bBottomVisible;
    bool            m_bBallVisible;
    bool            m_bCanSetRect;
    CGUIManager *   m_pUIManager;
    CGScene *       m_pGameScene;
    Sprite  *       m_pJoyStickBottom;
    Sprite  *       m_pJoyStickBall;
    Rect            m_JoyStickRect;
    Rect            m_ValidRect;
    Point           m_CenterPoint;
    Point           m_BottomPoint;
    Point           m_BallPoint;
};


#endif /* CGJoyStick_hpp */
