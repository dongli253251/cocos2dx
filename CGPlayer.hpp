//
//  CGPlayer.hpp
//  Game
//
//  Created by dongli on 2016/11/1.
//
//

#ifndef CGPlayer_hpp
#define CGPlayer_hpp

#include <stdio.h>
#include "CGGraphicsObject.hpp"
#include "cocos2d.h"
#include <iostream>
#include <Box2D/Box2D.h>
#include "CGDataType.h"
#include "CGException.hpp"
#include "CGPhysicsManager.hpp"
#include "CGPhysicsObject.hpp"
/**************************************************************
 * - 2016.11.16
 * - www.dongli.com
 
 * - CGPlayer Use Static Create Method.
 * - CGPlayer Object Represent a Local or Net Player.
 * - Player Type Specify by PlayerType.
 * - Include Physics Effect.
 * -
 *
 **************************************************************/



using namespace cocos2d;

class CGResManager;
class CGUIManager;
class CGEquitment;
class CGAnimateManager;
class CGScene;
class CGPlayerDateManager;
class CGPlayer:public CGGraphicsObject
{
    
protected:
    
    CGPlayer(const std::string& sPlayerID, UINT uType,float fX,float fY)
    {
        m_pEquitment         = nullptr;
        m_pMoveAnimate       = nullptr;
        m_pDieAnimate        = nullptr;
        m_pStandAnimate      = nullptr;
        m_pAttackAnimate     = nullptr;
        m_pStandAnimate      = nullptr;
        m_pAnimateManaget    = nullptr;
        m_pFrameCache        = nullptr;
        m_pGameScene         = nullptr;
        m_pPlayerSprite      = nullptr;
        m_pPhysicsObject     = nullptr;
        m_sTextureID         = sPlayerID;
        m_uPlayerType        = uType;
        m_ObjectPosition.x   = fX;
        m_ObjectPosition.y   = fY;
        /**
         *- Init All date.
         */
        
        CG_DEBUG_PRINT("CGPlayer Is Create");
    }
    
    CG_CONSTRUCTION_DEFAULT(CGPlayer)
    /**
     *- Disable Default Construction.
     */
    
    CG_CONSTRUCTION_COPY(CGPlayer)
    /**
     *- Disable Default Copy Construction.
     */

public:
    
    CG_DESTROY_DEFAULT(CGPlayer)
    
public:
    
    static CGPlayer * CreatePlayer(const std::string& sPlayer, UINT iType);
    
    static CGPlayer * CreatePlayer(const std::string& sPlayer,UINT iType,float fx, float fy);
    
    /**
     *- Create Palyer Object by ID and Type, ID get by Manager
     */

    CG_OVERLOAD_GRAPHICS;
    
    /**
     *- Init Date.
     */

    /**
     *- Remove Sprite and Clean Object Deap.
     */

    /**
     *- Draw and Update Player State, Process all Logic.
     */

    /**
     *- Delete this object.
     */
    
    CG_ACCESS_INT(AnimationState);
    
    
    /**
     *- Set Current Animate State.
     */
    
    /**
     *- Get Animate State.
     */
    
    
    /**
     *- Set Player Logic State, like die or avlie.
     */

    
    CG_ACCESS_INT(PlayerState);

    
    /**
     *- Get Player State.
     */

    inline CG_RESULT_VOID SetObjectPosition(float x, float y);
    /**
     *- Set Player Position.
     */
    inline CG_RESULT_VOID SetObjectPosition(const Point& Postion);
    
    
    inline virtual CG_RESULT_POINT_CREF GetObjectPosition()const;
    /**
     *- Get Player Position.
     */

    CG_ACCESS_STR(TextureID);
    
    /*
     *- Set Texture ID.
     */

    /*
     *- Get Texture ID.
     */
    
    CG_ACCESS_INT(PlayerOrientation);
    /*
     *- Set Orientation.
     */

    /*
     *- Get Orientation.
     */

    inline CG_RESULT_VOID PlayStandAnimation();
    /*
     *- Play Stand Animate.
     */
    
    inline CG_RESULT_VOID PlayDieAnimation();
    /*
     *- Play Dead Animate.
     */

    inline CG_RESULT_VOID PlayAttackAnimation();
    /*
     *- Play Attack Aniamte.
     */

    inline CG_RESULT_VOID PlayMoveAnimation();
    /*
     *- Play Moving Aniamte.
     */

    inline CG_RESULT_VOID PlayHitAnimation();
    /*
     *- Play Be Hit Animate.
     */
    
    CG_ACCESS_BOOL(PlayerHide)
    /*
     *- Get Hide Value.
     */
    
    inline CG_RESULT_VOID DieCallBack();
    /*
     *- Dead Call Back function.
     */
    
    CG_RESULT_VOID ApplyForce(float x, float y);
    
    CG_RESULT_POINT_CREF GetScreenPoint()const
    {
        return m_ScreenPoint;
    }
    
    CG_RESULT_VOID ProcessScreenPoint();
    
protected:
    CGEquitment      *      m_pEquitment;
    CGUIManager      *      m_pUI;
    CGAnimateManager *      m_pAnimateManaget;
    CGResManager     *      m_pRes;
    CGPlayerDateManager *   m_pDate;
    //////////////////////  CG Manager.
    
    SpriteFrameCache *      m_pFrameCache;
    //////////////////////  cocos2d object.
    
    CGPhysicsManager *      m_pPhysicsManager;
    CGPhysicsObject *       m_pPhysicsObject;
    b2BodyDef               m_BodyDef;
    b2PolygonShape          m_BodyShpae;
    b2FixtureDef            m_BodyFixture;
    b2Vec2                  m_Gravity;
    //////////////////////  Physics Object.
    
    Animate          *      m_pMoveAnimate;
    Animate          *      m_pStandAnimate;
    Animate          *      m_pHitAnimate;
    Animate          *      m_pDieAnimate;
    Animate          *      m_pAttackAnimate;
    //////////////////////  Animate
    
    Sequence         *      m_pDieSequnce;
    Sequence         *      m_pHitSequnce;
    CGScene          *      m_pGameScene;
    Sprite           *      m_pPlayerSprite;
  
    Rect                    m_SceneRect;
    Point                   m_ScreenPoint;
    Point                   m_CenterPoint;
    Point                   m_RightUpZeroPoint;
    Point                   m_LeftUpZeroPoint;
    Point                   m_RightDownZeroPoint;
    Point                   m_LeftDownZeroPoint;
    Point                   m_UpPoint;
    Point                   m_RightPoint;
    Point                   m_DownPoint;
    Point                   m_LeftPoint;
    Point                   m_LeftUp_RightUpPoint;
    Point                   m_LeftUp_LeftDownPoint;
    Point                   m_RightUp_LeftUpPoint;
    Point                   m_RightUp_RightDownPoint;
    Point                   m_RightDown_RightUpPoint;
    Point                   m_RightDown_LeftDownPoint;
    std::string             m_sPlayerName;
    //////////////////////  Player Nick Name
    
    std::string             m_sTextureID;
    //////////////////////  Player Texture ID
    
    //std::string             m_sPlayerID;
    
    bool                    m_bPlayerDead;
    bool                    m_bStateSwitch;
    bool                    m_bPlayerHide;
    bool                    m_bOpenPhysics;
    bool                    m_bCallDie;
    bool                    m_bPowerButton;

    //////////////////////  Player State.
    
    int                     m_iJoyStickValue;
    //////////////////////  JoyStick
    
    int                     m_iPlayerOrientation;
    int                     m_iLastState;
    int                     m_iPlayerState;
    int                     m_iAnimationState;
    UINT                    m_iPhysicsState;
    UINT                    m_uPlayerType;
    //////////////////////  Local Player or Net Player.
    
    int                     m_iAnimateNumber;
    int                     m_iMoveSpeed;
    
    int                     m_iBodyWidth;
    int                     m_iBodyHeight;
    int                     m_iScreenHeight;
    int                     m_iScreenWidth;
    
    int                     m_iHorizontalForceY;
    int                     m_iHorizontalForceX;
    int                     m_iVerticalForceX;
    int                     m_iVerticalForceY;
    int                     m_iObliqueForceX;
    int                     m_iObliqueForceY;
    int                     m_iObliqueDownForceX;
    int                     m_iObliqueDownForceY;
    int                     m_iVerticalDownFroce;
    float                   m_fHorizontalSpeed;
    float                   m_fVerticalSpeed;
    float                   m_fHorizontalMaxSpeed;
    float                   m_fVerticalMaxSpeed;
    int                     m_iBuoyancy;
    float                   m_fLastX;
    float                   m_fLastY;
};

#endif /* CGPlayer_hpp */
