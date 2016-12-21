//
//  CGBullet.hpp
//  Game
//
//  Created by dongli on 2016/11/20.
//
//

#ifndef CGBullet_hpp
#define CGBullet_hpp

#include <stdio.h>
#include "CGDataType.h"
#include "CGWeaponBase.hpp"
#include <cocos2d.h>
#include "CGException.hpp"
#include <Box2D/Box2D.h>
#include "CGPlayerDateManager.hpp"

const int BULLET_STATE_NORMAL  = 1;
const int BULLET_STATE_STRIKE  = 2;

using namespace cocos2d;
class CGResManager;
class CGScene;
class CGGlobalDateManager;
class CGUIManager;
class CGAnimateManager;
class CG_CLASS CGBullet:public CGWeaponBase
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGBullet)
    
    CG_CONSTRUCTION_COPY(CGBullet)
    
    explicit CGBullet(int iType)
    {
        m_iBulletType = iType;
    }
    
    explicit CGBullet(const std::string& sName,float fX, float fY,int iOrien,int iOwner)
    {
        m_sTextureName     = sName;
        m_ObjectPosition.x = fX;
        m_ObjectPosition.y = fY;
        m_iBulletOriention = iOrien;
        m_iBulletOwner     = iOwner;
    }
    
public:
    CG_DESTROY_DEFAULT(CGBullet)
    
    CG_OVERLOAD_GRAPHICS;
    
    CG_ACCESS_INT(BulletType);
    
    CG_ACCESS_INT(BulletOwner);
    
    static CGBullet * CreateBullet(const std::string sName,float fx,float fy,int iOrient,int iType);
    
    static CGBullet * CreateBullet(const std::string sName,const Point& Position,int iOrent,int iType);
    
protected:
    
    int                     m_iBulletType;
    int                     m_iBulletSpeed;
    int                     m_iBulletOriention;
    int                     m_iBulletCount;
    int                     m_iBulletOwner;
    bool                    m_bIsLunch;
    
    Point                   m_NearBasePoint;
    Point                   m_ScreenPosition;
    CGScene *               m_pGameScene;
    CGGlobalDateManager *   m_pGlobal;
    CGAnimateManager *      m_pAniamteManager;
    CGPlayerDateManager *   m_pDate;
    CGResManager *          m_pRes;
    CGUIManager  *          m_pUI;
    Sprite *                m_pBulletSprite;
    SpriteFrame *           m_pBulletFrame;
    b2Body *                m_pPhysicsbody;
    Animation *             m_pAnimation;
    Animate *               m_pAnimate;
    std::string             m_sTextureName;

};


#endif /* CGBullet_hpp */
