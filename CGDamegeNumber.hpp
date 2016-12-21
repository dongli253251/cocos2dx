//
//  CGDamegeNumber.hpp
//  Game
//
//  Created by dongli on 2016/11/30.
//
//

#ifndef CGDamegeNumber_hpp
#define CGDamegeNumber_hpp

#include <stdio.h>
#include <CGDataType.h>
#include <CGGraphicsObject.hpp>
using namespace cocos2d;
class CGScene;
class CGDamegeSystem;
class CG_CLASS CGDamegeNumber:public CGGraphicsObject
{
protected:

    CGDamegeNumber(int iNumber,int iType,float x,float y)
    {
        m_ObjectPosition.x = x;
        m_ObjectPosition.y = y;
        m_iType            = iType;
        m_iNumber          = iNumber;
        
        CG_DEBUG_PRINT("CGDamegeNumber Is Created");
    }
    
    CG_CONSTRUCTION_COPY(CGDamegeNumber)
    
public:
    CG_DESTROY_DEFAULT(CGDamegeNumber)
    
    CG_OVERLOAD_GRAPHICS
    
    static CGDamegeNumber * CreateDamegeNumber(int iNumber,int iType,const Point& Position);
    
    CG_ACCESS_BOOL(IsDead);
    
    CG_RESULT_VOID DeadCallBack();
    
    CG_RESULT_VOID MoveEndCallBack();
protected:
    int                             m_iNumber;
    int                             m_iType;
    int                             m_iFontSize;
    bool                            m_bIsDead;
    std::string                     m_sFontName;
    std::string                     m_sFontPath;
    CGDamegeSystem *                m_pDamegeSystem;
    CGScene *                       m_pGameScene;
    Label *                         m_pLabel;
    Color3B                         m_FontColor;
    BezierTo *                      m_pBezier;
    Sequence *                      m_pSequence;
    FadeOut *                       m_pFade;
    Sequence *                      m_pFadeSeq;

};

#endif /* CGDamegeNumber_hpp */
