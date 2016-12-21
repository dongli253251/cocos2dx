//
//  CGWeaponBase.hpp
//  Game
//
//  Created by dongli on 2016/11/20.
//
//

#ifndef CGWeaponBase_hpp
#define CGWeaponBase_hpp

#include <stdio.h>
#include <iostream>
#include <cocos2d.h>
#include "CGDataType.h"
#include "CGGraphicsObject.hpp"

using namespace cocos2d;

class CG_CLASS CGWeaponBase:public CGGraphicsObject
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGWeaponBase)
    
    CG_CONSTRUCTION_COPY(CGWeaponBase)
    
public:
    
    CG_DESTROY_DEFAULT(CGWeaponBase)
    
    CG_OVERLOAD_GRAPHICS
    
    CG_ACCESS_INT(WeaponID);
    
    CG_ACCESS_INT(WeaponState);
    
    CG_ACCESS_INT(WeaponHeight);
    
    CG_ACCESS_INT(WeaponWidth);
    
    const Rect& GetWeaponRect()const
    {
        return m_WeaponRect;
    }
    
    void SetWeaponRect(const Rect& rect)
    {
        m_WeaponRect = rect;
    }
    
    CG_ACCESS_BOOL(IsDead);
    
protected:
    
    int         m_iWeaponID;
    int         m_iWeaponState;
    int         m_iWeaponHeight;
    int         m_iWeaponWidth;
    bool        m_bIsDead;
    Rect        m_WeaponRect;

};


#endif /* CGWeaponBase_hpp */
