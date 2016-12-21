//
//  CGMonsterBase.hpp
//  Game
//
//  Created by dongli on 2016/12/13.
//
//

#ifndef CGMonsterBase_hpp
#define CGMonsterBase_hpp


#include <iostream>
#include <CGDataType.h>
#include <CGGraphicsObject.hpp>
class CGScene;
class CG_CLASS CGMonsterBase:public CGGraphicsObject
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGMonsterBase)
    
    CG_CONSTRUCTION_COPY(CGMonsterBase);
public:
    CG_DESTROY_DEFAULT(CGMonsterBase)
    
    CG_OVERLOAD_GRAPHICS;
    
    CG_RESULT_VOID SetBasePoint(const Point& Position)
    {
        m_BasePoint = Position;
    }
    
    CG_RESULT_VOID SetScreenPosition(const Point& Position)
    {
        m_ScreenPosition = Position;
    }
    
    CG_ACCESS_STR(MonsterName);
    
    CG_ACCESS_INT(MonsterType);
    
    CG_ACCESS_INT(AnimateState);
    
    CG_ACCESS_INT(Orientation);
    
protected:
    CGScene *               m_pGameScene;
    Point                   m_ScreenPosition;
    Point                   m_BasePoint;
    std::string             m_sMonsterName;
    int                     m_iMonsterType;
    int                     m_iAnimateState;
    int                     m_iOrientation;
    int                     m_iLastAnimateState;
    
};
#endif /* CGMonsterBase_hpp */
