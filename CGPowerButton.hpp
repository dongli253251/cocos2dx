//
//  CGPowerButton.hpp
//  Game
//
//  Created by dongli on 2016/11/11.
//
//

#ifndef CGPowerButton_hpp
#define CGPowerButton_hpp

/**************************************************************
 * - 2016.11.15
 * - www.dongli.com
 *
 * - This Class Create a Only Button for Energy System View.
 * - Auto Accept Touch Input and Process Input Also Update
 * - Button State
 *
 **************************************************************/


#include <stdio.h>
#include <iostream>
#include <CGUIBase.hpp>
#include <CGDataType.h>
#include <cocos2d.h>
#include <CGException.hpp>
using namespace cocos2d;
class CGScene;
class CGUIManager;
class CGPowerButton:public CGUIBase
{
protected:
    explicit CGPowerButton(int iType)
    {
        m_iButtonType = iType;
    }
    /**
     *- Construction.
     */
    
    CG_CONSTRUCTION_COPY(CGPowerButton)
    /**
     *- Disable Default Construction.
     */

public:
    
    CG_DESTROY_DEFAULT(CGPowerButton)
    /**
     *- Disable Default Destruction.
     */

    CG_OBJECT_CREATE_INT_1(PowerButton, Type);
    /**
     *- Create CGPowerButton Object by Type.
     */
    
    CG_OVERLOAD_GRAPHICS;
    /**
     *- OverLoad Default Graphics Method.
     */
    
    CG_RESULT_INT GetUIOnlyID()const
    {
        return m_iUIOnlyID;
    }
    /**
     *- Get Only UI Id.
     */
    
    CG_RESULT_VOID SetUIOnlyID(int iID)
    {
        m_iUIOnlyID = iID;
    }
    /**
     *- Set Only ID
     */

    CG_RESULT_BOOL GetButtonIsTouch()const
    {
        return m_bButtonIsTouch;
    }
    /**
     *- Get Button State, Push or Pops
     */

    
    CG_RESULT_VOID SetButtonIsTouch(bool bIs)
    {
        m_bButtonIsTouch = bIs;
    }
    /**
     *- Set Button State.
     */

    
    CG_RESULT_VOID SetButtonScale(float fx, float fy);
    /**
     *- Scale Button.
     */

    
protected:
    CGScene *           m_pGameScene;
    //////////////////  Game Scene Pointer.
    
    CGUIManager *       m_pUIManager;
    
    Sprite  *           m_pNormalSprite;
    //////////////////  Normal State Sprite. Pop State.

    Sprite  *           m_pDownSprite;
    //////////////////  Push Down Sprite.

    Rect                m_ButtonRect;
    //////////////////  Button Rect.

    bool                m_bCanZeroPoint;
    //////////////////  ????? i forget it

    bool                m_bLockPoint;
    
    bool                m_bButtonIsTouch;
    //////////////////  Button Touch State.

    long                m_lOnlyCount;
    
    int                 m_iUIOnlyID;
    //////////////////  Every UI Object Has a Only ID
    
    int                 m_iButtonType;
    //////////////////  Button Name.
    
    int                 m_iButtonHeight;
    //////////////////  Button Height.

    int                 m_iButtonWidth;
    //////////////////  Button Width.

    int                 m_iButtonState;
    //////////////////  State. Push or Pop.

};


#endif /* CGPowerButton_hpp */
