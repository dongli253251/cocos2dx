//
//  CGMapScene.hpp
//  Game
//
//  Created by dongli on 2016/11/23.
//
//

#ifndef CGMapScene_hpp
#define CGMapScene_hpp

#include <stdio.h>
#include <iostream>
#include <CGGraphicsObject.hpp>
#include "CGDataType.h"
#include <cocos2d.h>
#include <CGException.hpp>
#include <CGPhysicsManager.hpp>


using namespace cocos2d;
class CGPlayerManager;
class CGResManager;
class CGMapElement;
class CGScene;
class CGPlayer;
class CG_CLASS CGMapScene:public CGGraphicsObject
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGMapScene)
    
    CG_CONSTRUCTION_COPY(CGMapScene)
    
    explicit CGMapScene(const std::string& MapName)
    {
        m_sMapName = MapName;
    }
    
public:
    
    typedef enum tagOffsetOrient
    {
        OFFSET_UP = 1,
        OFFSET_DOWN,
        OFFSET_LEFT,
        OFFSET_RIGHT,
        OFFSET_LEFT_UP,
        OFFSET_LEFT_DOWN,
        OFFSET_RIGHT_UP,
        OFFSET_RIGHT_DOWN,
        
    }ENUM_OFFSET_ORIENTATION;
    
    
    CG_DESTROY_DEFAULT(CGMapScene);
    
    CG_OVERLOAD_GRAPHICS;
    
    CG_OBJECT_CREATE_CSTR_1(MapScene, sMapName);
    
    CG_ACCESS_INT(MapHeight)
    
    CG_ACCESS_INT(MapWidth)
    
    CG_ACCESS_INT(FarMoveScale)
    
    CG_ACCESS_INT(ActiveHeight);
    
    CG_ACCESS_INT(ActiveWidth);
    
    CG_ACCESS_BOOL(NeedFixFarPoint);
    
    CG_RESULT_VOID FirstFixPosition(int iScale);
    
    CG_RESULT_VOID ProcessLeftDownPoint();
    
    CG_RESULT_VOID ProcessLeftUpPoint();
    
    CG_RESULT_VOID ProcessRightUpPoint();
    
    CG_RESULT_VOID ProcessRightDownPoint();
    
    CG_RESULT_VOID ProcessNearLayer();
    
    CG_RESULT_INT GetPlayerInAnyRect(const Point& Point);
    
    CG_RESULT_INT GetOffsetOrientation(const Point& Offset);
    
    CG_RESULT_VOID MoveBackGroundByScale(int iSacle);
    
    CG_RESULT_VOID ProcessNearBasePoint();
    
    CG_RESULT_VOID FillFarRect();
    
    const std::list<STRUCT_FARRECT>& GetFarRectList()const
    {
        return m_FarRectList;
    }
    
    Point GetRectZeroPointByID(int iID);
    
    Point GetNearBasePoint()const 
    {
        return m_NearBasePoint;
    }
protected:
    
    int                                 m_iMapHeight;
    int                                 m_iMapWidth;
    int                                 m_iFarMoveScale;
    int                                 m_iNearMoveScale;
    int                                 m_iFarHeight;
    int                                 m_iFarWidht;
    int                                 m_iScreenHeight;
    int                                 m_iScreenWidth;
    int                                 m_iActiveHeight;
    int                                 m_iActiveWidth;
    int                                 m_iXOffset;
    int                                 m_iYOffset;
    bool                                m_bIsAddFarGround;
    bool                                m_bNeedFixFarPoint;
    bool                                m_bCanMoveFarGround;
    CGScene *                           m_pGameScene;
    CGResManager *                      m_pResManager;
    CGPlayerManager *                   m_pPlayerManager;
    CGPhysicsManager *                  m_pPhysics;
    CGPlayer *                          m_pPlayer;
    Sprite *                            m_pFarBackGroundSprite;
    Rect                                m_PlayerActiveRect;
    Rect                                m_LeftDownRect;
    Rect                                m_LeftUpRect;
    Rect                                m_RightUpRect;
    Rect                                m_RightDownRect;
    Rect                                m_UpRect;
    Rect                                m_RightRect;
    Rect                                m_LeftRect;
    Rect                                m_DownRect;
    DrawNode *                          m_pNode;
    DrawNode *                          m_pNear;
    Point                               m_CenterPoint;
    Point                               m_LastPlyaerPoint;
    Point                               m_PlayerPosition;
    Point                               m_LeftUpPoint;
    Point                               m_RightDownPoint;
    Point                               m_RightUpPoint;
    Point                               m_FarPosition;
    Point                               m_NearBasePoint;
    Point                               m_NearPosition;
    Point                               m_FarMaxPoint;
    Point                               m_FarMinPoint;
    std::string                         m_sMapPath;
    std::string                         m_sMapName;
    std::string                         m_sFarBackGroundName;
    
    std::list<STRUCT_FARRECT>           m_FarRectList;
    std::vector<CGMapElement *>         m_pElementVec;
    
};


#endif /* CGMapScene_hpp */
