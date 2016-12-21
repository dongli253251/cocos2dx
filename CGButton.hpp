//
//  CGButton.hpp
//  Game
//
//  Created by dongli on 2016/11/8.
//
//

#ifndef CGButton_hpp
#define CGButton_hpp

#include <stdio.h>
#include <iostream>
#include <CGUIBase.hpp>
#include <cocos2d.h>

using namespace cocos2d;
class CGScene;

class CGButton:public CGUIBase
{
protected:
    explicit CGButton(int iButtonType)
    {
        m_iButtonType = iButtonType;
    }
    CGButton(const CGButton& rhs)
    {
    
    }
public:
    virtual ~CGButton()
    {
        CleareGObject();
    }
    
    enum ENUM_BUTTON_STATE
    {
        BUTTON_STATE_PUSH = 1,
        BUTTON_STATE_POP
    };
    
   
    static CGButton * CreateButton(int iButtonType);
    
    virtual bool InitGObject();
    
    virtual bool CleareGObject();
    
    virtual void DrawGObject();
    
    virtual bool DeleteGObject();
    
    
    
    int GetButtonState()const
    {
        return m_iButtonState;
    }
    
    void SetButtonState(int bState)
    {
        m_iButtonState = bState;
    }
    
    void SetButtonRect(const Rect& Rect)
    {
        m_ButtonRect = Rect;
    }
    
    const Rect& GetButtonRect()const
    {
        return m_ButtonRect;
    }
    
    
    void SetButtonScale(float fx,float fy);
    
protected:
    int                 m_iButtonType;
    int                 m_iButtonState;
    int                 m_iButtonInterval;
    long long           m_iLastTime;
    
    Rect                m_ButtonRect;
    Sprite  *           m_pNormalSprite;
    CGScene *           m_pGameScene;
    Sprite  *           m_pDownSprite;
};



#endif /* CGButton_hpp */
