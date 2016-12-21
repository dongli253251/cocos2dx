//
//  CGScene.hpp
//  Game
//
//  Created by dongli on 2016/10/27.
//
//

#ifndef CGScene_hpp
#define CGScene_hpp



/**************************************************************
 * - 2016.11.15
 * - www.dongli.com
 * -
 * - manage game secene
 * -
 **************************************************************/




#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "CGSocket.hpp"
#include <Box2D/Box2D.h>
#include "CGDataType.h"
using namespace cocos2d;
class CGMapManager;
class CGBullet;
class CGPlayerManager;
class CGWeaponManager;
class CGPlayer;
class CGResManager;
class CGProtocolManager;
class CGUIManager;
class CGDamegeSystem;
class CGPhysicsManager;
class CG_CLASS CGScene:public cocos2d::Layer
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGScene);
    
    CG_CONSTRUCTION_COPY(CGScene)
    
public:
    
    virtual ~CGScene()
    {
        
    }
    //CG_DESTROY_DEFAULT(CGScene)
    
public:
    static CGScene * CreateGScene();
    
    static cocos2d::Scene * GetCocosSecene();
    
    virtual CG_RESULT_BOOL init();
    
    
    CG_RESULT_VOID RunGameWithFrame(float);
    
    
    
    static CG_RESULT_VOID * SendProtocolThread(void *);
    
    
    
    CG_RESULT_VOID OnGameLogo();
    
    CG_RESULT_VOID OnGameMain();
    
    CG_RESULT_VOID OnGameLogic();
    
    CG_RESULT_BOOL OnTouchBegan(Touch * pTouch,Event * pEvent);
    
    CG_RESULT_VOID OnTouchEnd(Touch * pTouch,Event * pEvent);
    
    CG_RESULT_VOID OnTouchMoved(Touch * pTouch,Event * pEvent);
    
    b2World * GetPhysicsWorld()const
    {
        return m_pWorld;
    }
    
    CGSocket *  GetSocket()
    {
        return m_pSocket;
    }
    

    
    b2Body * CreatePhysicsBody(float iWidth,float iHeight,const Point& Position,float fDensity,float fFriction);

    b2Body * CreateStaticBody(float iWidth,float fHeight,const Point& Position);
    
protected:
    CGSocket *                      m_pSocket;
    b2World  *                      m_pWorld;
    CGPlayerManager *               m_pPlayer;
    CGUIManager *                   m_pUI;
    CGResManager *                  m_pRes;
    CGDamegeSystem *                m_pDamege;
    CGMapManager *                  m_pMap;
    CGProtocolManager *             m_pProtocol;
    CGWeaponManager *               m_pWeapon;
    CGPhysicsManager *              m_pPhysics;
    b2Body   *                      m_pGroundBody;
    b2Body   *                      m_pBody;
    b2BodyDef                       m_GroundDef;
    b2BodyDef                       m_BodyDef;
    b2FixtureDef                    m_FixtureDef;
    b2PolygonShape                  m_BodyShape;
    b2PolygonShape                  m_GroundShape;
    Layer    *                      m_pFarLayer;
    Layer    *                      m_pNearLayer;
    bool                            m_bFirstLogic;
    bool                            m_bCanPhysics;
    int                             m_iGameState;
    int                             m_iTouchCount;

};


#endif /* CGScene_hpp */
