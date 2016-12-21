//
//  CGPirateSoldier.hpp
//  Game
//
//  Created by dongli on 2016/12/14.
//
//

#ifndef CGPirateSoldier_hpp
#define CGPirateSoldier_hpp

#include <iostream>
#include <CGDataType.h>
#include <CGMonsterBase.hpp>
class CGAnimateManager;
class CGMonsterDateManager;
class CGMonsterAI;
class CG_CLASS CGPirateSoldier:public CGMonsterBase
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGPirateSoldier)
    
    CGPirateSoldier(const std::string& sName)
    {
        m_sMonsterName = sName;
    }
    
    CG_CONSTRUCTION_COPY(CGPirateSoldier)
public:
    CG_DESTROY_DEFAULT(CGPirateSoldier)
    
    CG_OVERLOAD_GRAPHICS
    
    static CGPirateSoldier * CreatePirateSoldier(const std::string& sName);
    
    CG_RESULT_VOID PlayAttackAnimate();

    CG_RESULT_VOID PlayMoveAnimate();
    
    CG_RESULT_VOID PlayHitAnimate();
    
    CG_RESULT_VOID PlayStandAnimate();
    
    CG_RESULT_VOID PlayDieAnimate();
    
    CG_ACCESS_INT(AnimateState)
    
    CG_ACCESS_BOOL(IsDead)
    
    CG_ACCESS_INT(MoveSpeed);
    
    CG_RESULT_VOID ApplyPosition(const Point& Position);
    
    CG_ACCESS_BOOL(CanRunAI);
    
    CG_RESULT_VOID AddMoveEvetnToList(float fX,float fY,int iType);
protected:
    Sprite *                        m_pSoldierSprite;
    Animate *                       m_pMoveAnimate;
    Animate *                       m_pStandAnimate;
    Animate *                       m_pDieAnimate;
    Animate *                       m_pAttackAnimate;
    Animate *                       m_pHitAnimate;
    bool                            m_bIsDead;
    bool                            m_bSwitchAnimate;
    bool                            m_bCanRunAI;
    CGMonsterAI *                   m_pAI;
    int                             m_iMoveSpeed;
    
};

#endif /* CGPirateSoldier_hpp */
