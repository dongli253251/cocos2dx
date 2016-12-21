//
//  CGUIManager.hpp
//  Game
//
//  Created by dongli on 2016/11/8.
//
//

#ifndef CGUIManager_hpp
#define CGUIManager_hpp

/**************************************************************
 * - 2016.11.16
 * - www.dongli.com
 
 * - Manage all UI Object.
 * - Process all Input Point.
 *
 *
 * -
 *
 **************************************************************/



#include <stdio.h>
#include "CGComObject.hpp"

#include <iostream>
#include <cocos2d.h>
#include <CGUIBase.hpp>

using namespace cocos2d;

class CGUIManager:public CGComObject
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGUIManager);
    /**
     *-
     */
    
    CG_CONSTRUCTION_COPY(CGUIManager);
    /**
     *-
     */

public:
    
    CG_DESTROY_DEFAULT(CGUIManager)
    /**
     *-
     */


    static CGUIManager * sharedUIManager();
    /**
     *-
     */
    
    CG_OVERLOAD_COM;
    /**
     *-
     */
    
    CG_RESULT_VOID ProcessUITask();
    /**
     *-
     */

    CG_RESULT_VOID AddUIToList(CGUIBase * pUI);
    /**
     *-
     */

    CG_RESULT_VOID PushTouchInfo(const STRUCT_TOUCH_INFO& Info);
    /**
     *-
     */

    const std::vector<STRUCT_TOUCH_INFO>& GetTouchVector()const;
    /**
     *-
     */

    CG_RESULT_BOOL GetPowerButtonIsTouch()const
    {
        return m_bPowerButtonIsTouch;
    }
    /**
     *-
     */

    CG_RESULT_VOID SetPowerButtonIsTouch(bool bIs)
    {
        m_bPowerButtonIsTouch = bIs;
    }
    /**
     *-
     */

    CG_RESULT_INT GetJoyStickValue()const
    {
        return m_iJoyStickValue;
    }
    /**
     *-
     */

    CG_RESULT_VOID SetMovePointByID(int iID,const Point& Point);
    /**
     *-Set Move Point.
     */

    CG_RESULT_VOID SetEndPointByID(int iID,const Point& Point);
    /**
     *-Set End Point.
     */

    CG_RESULT_VOID SetBeganPointByID(int iID,const Point& Point);
    /**
     *-Set Began Point.
     */

    CG_RESULT_VOID SetIsEndByID(int iID,bool bIs);
    /**
     *- Set Is End.
     */

    CG_RESULT_VOID SetOnlyCount(int iID,long lCount);
    /**
     *-Set Only Count.
     */

    CG_RESULT_BOOL GetIsEndByID(int iID)const;
    /**
     *-Get Is End.
     */

    CG_RESULT_INT GetOnlyCount(int iID)const;
    /**
     *-Get Touch Only Count Value.
     */

    CG_RESULT_POINT_CREF GetMovePointByID(int iID)const;
    /**
     *- Get Move Point.
     */

    CG_RESULT_POINT_CREF GetBeganPointByID(int iID)const;
    /**
     *- Get Began Point.
     */

    CG_RESULT_POINT_CREF GetEndPointByID(int iID)const;
    /**
     *- Get End Point.
     */
    
    CG_RESULT_VOID SetIsEndByOnlyCount(long uCount, bool bIs);
    
    CG_RESULT_BOOL GetTouchVecIsEmpty()const;
    
    CG_RESULT_POINT_CREF GetMovePointByOnlyCount(ULONG uCount)const;
    
    CG_RESULT_POINT_CREF GetEndPointByOnlyCount(ULONG uCount)const;
    
    CG_RESULT_POINT_CREF GetBeganPointByOnlyCount(ULONG uCount)const;
    
    
    CG_RESULT_LONG GetOnlyCountByRect(const Rect& Point)const;
    
    CG_RESULT_BOOL GetLunchButtonIsTouch()const
    {
        return m_bLunchButtonIsTouch;
    }
    
    CG_RESULT_VOID SetLunchButtonisTouch(bool bIs)
    {
        m_bLunchButtonIsTouch = bIs;
    }
    
protected:
    bool                            m_bPowerButtonIsTouch;
    
    bool                            m_bLunchButtonIsTouch;
    /////////////////////////////   Power Button State.
    
    std::vector<CGUIBase *>         m_vUIVector;
    /////////////////////////////   all UI in This Vector
    
    std::vector<STRUCT_TOUCH_INFO>  m_vTouch;
    /////////////////////////////   All Touch Point Info
    
    int                             m_iJoyStickValue;
    /////////////////////////////   JoyStick
};


#endif /* CGUIManager_hpp */
