//
//  CGStateSystem.hpp
//  Game
//
//  Created by dongli on 2016/12/10.
//
//

#ifndef CGStateSystem_hpp
#define CGStateSystem_hpp

#include <iostream>
#include <CGDataType.h>
#include <CGUIBase.hpp>
#include <CGException.hpp>

class CGScene;
class CGPlayerDateManager;
class CGResManager;
class CGUIManager;
class CG_CLASS CGStateSystem:public CGUIBase
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGStateSystem)
    
    CG_CONSTRUCTION_COPY(CGStateSystem)
    
public:
    
    enum
    {
        PROGRESS_TYPE_ADD = 1,
        PROGRESS_TYPE_REDUCE,
        PORGRESS_NAME_LIFE,
        PROGRESS_NAME_ARMOR,
        PROGRESS_NAME_TEMP,
    };
    
    struct STRUCT_PROGRESS
    {
        STRUCT_PROGRESS(int iValue,int iType,ULONG iIndex)
        {
            iPercentageValue = iValue;
            iProgressType    = iType;
            bIsOver          = false;
            bIsRuning        = false;
            iProgressIndex   = iIndex;
        }
        
        STRUCT_PROGRESS()
        {
            
        }
    
        ULONG       iProgressIndex;
        int         iPercentageValue;
        int         iProgressType;
        int         iValue;
        bool        bIsOver;
        bool        bIsRuning;
    };
    
    CG_DESTROY_DEFAULT(CGStateSystem)
    
    CG_OVERLOAD_GRAPHICS
    
    CG_OBJECT_CREATE(StateSystem);

    CG_RESULT_VOID ReducsLifeValue(float fValue);
    
    CG_RESULT_VOID AddLifeValue(float fValue);
    
    CG_RESULT_VOID AddArmorValue(float fValue);
    
    CG_RESULT_VOID ReduceArmorValue(float fValue);
    
    CG_RESULT_VOID AddTempValue(float fValue);
    
    CG_RESULT_VOID ReduceTempValue(float fValue);
    
    CG_RESULT_VOID LifeCallBack();
    
    CG_RESULT_VOID ArmorCallBack();
    
    CG_RESULT_VOID TempCallBack();
    
protected:
    float                               m_fAddIntervalTime;
    float                               m_fReduceIntervalTime;
    float                               m_fLifeReduceIntervalTime;
    float                               m_fLifeAddIntervalTime;
    float                               m_fArmorAddIntervalTime;
    float                               m_fArmorReduceIntervalTime;
    ULONG                               m_iCurrentTempIndex;
    ULONG                               m_iTempCount;
    ULONG                               m_iLifeCount;
    ULONG                               m_iArmorCount;
    ULONG                               m_iCurrentArmorIndex;
    ULONG                               m_iCurrentLifeIndex;
    int                                 m_iScreenHeight;
    int                                 m_iScreenWidth;
    int                                 m_iLastLife;
    int                                 m_iLastArmor;
    float                               m_fCurrentLife;
    float                               m_fCurrentArmor;
    float                               m_fCurrentTemp;
    float                               m_fMaxTemp;
    float                               m_fMaxArmor;
    float                               m_fMaxLife;
    bool                                m_bLifeStandby;
    bool                                m_bArmorStandby;
    bool                                m_bTempStandby;
    bool                                m_bCanReduceTemp;
    bool                                m_bStartReduceTemp;
    bool                                m_bCanAddTemp;
    std::string                         m_sUIPath;
    std::string                         m_sLifeBarNormal;
    std::string                         m_sArmorBarNormal;
    std::string                         m_sTempBarNormal;
    std::string                         m_sProgressDown;
    
    std::list<STRUCT_PROGRESS>          m_vLifeList;
    std::list<STRUCT_PROGRESS>          m_vArmorList;
    std::list<STRUCT_PROGRESS>          m_vTempList;
    Sprite *                            m_pLifeBarNormal;
    Sprite *                            m_pLifeBarDown;
    Sprite *                            m_pArmorBarNormal;
    Sprite *                            m_pArmorBarDown;
    Sprite *                            m_pTempBarNormal;
    Sprite *                            m_pTempBarDown;
    ProgressTimer *                     m_pLifeProgress;
    ProgressTimer *                     m_pArmorProgress;
    ProgressTimer *                     m_pTempProgress;
    Size                                m_LifeBarSize;
    Size                                m_ArmorBarSize;
    Size                                m_TempBarSize;
    Point                               m_LifePosition;
    Point                               m_ArmorPosition;
    Point                               m_TempPosition;
    CGScene *                           m_pGameScene;
    CGPlayerDateManager *               m_pDateManager;
    CGResManager *                      m_pResManager;
    CGUIManager *                       m_pUIManager;
};

#endif /* CGStateSystem_hpp */
