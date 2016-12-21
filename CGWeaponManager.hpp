//
//  CGWeaponManager.hpp
//  Game
//
//  Created by dongli on 2016/11/21.
//
//

#ifndef CGWeaponManager_hpp
#define CGWeaponManager_hpp

#include <stdio.h>
#include <iostream>
#include <CGDataType.h>
#include <CGComObject.hpp>

class CGUIManager;
class CGBullet;
class CGPlayerDateManager;
class CGWeaponBase;
class CGPlayerManager;

class CG_CLASS CGWeaponManager:public CGComObject
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGWeaponManager)
    
    CG_CONSTRUCTION_COPY(CGWeaponManager)
    
public:
    
    CG_DESTROY_DEFAULT(CGWeaponManager)
    
    CG_SINGLETON_CREATE(WeaponManager)
    
    CG_OVERLOAD_COM;
    
    CG_RESULT_VOID ProcessWeaponTask();
    
    CG_RESULT_VOID AddWeaponToList(CGWeaponBase * pWeapon);
    
    CG_ACCESS_BOOL(WeaponEnable);
    
    CG_ACCESS_BOOL(BulletEnable);
    
protected:
    bool                            m_bWeaponEnable;
    bool                            m_bBulletEnable;
    bool                            m_bCanLunch;
    long                            m_lLastTime;
    int                             m_iBulletSpeed;
    int                             m_iBulletInterval;
    CGPlayerDateManager *           m_pDate;
    CGPlayerManager *               m_pPlayer;
    CGUIManager *                   m_pUI;
    std::vector<CGWeaponBase *>     m_vWeaponList;
    std::string                     m_sBulletName;
};


#endif /* CGWeaponManager_hpp */
