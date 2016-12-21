//
//  CGMapScene.cpp
//  Game
//
//  Created by dongli on 2016/11/23.
//
//

#include "CGMapScene.hpp"
#include "CGResManager.hpp"
#include "CGPlayerManager.hpp"
#include "CGPlayer.hpp"
#include "CGScene.hpp"
#include "CGGlobalDateManager.hpp"

extern CGScene * GetGScene();

bool CGMapScene::InitGObject()
{
    m_pPhysics             = CGPhysicsManager::sharedPhysicsManager();
    m_pGameScene           = GetGScene();
    m_pResManager          = CGResManager::sharedResManager();
    m_pPlayerManager       = CGPlayerManager::sharedPlayerManager();

    m_sMapPath             = m_pResManager->GetMapPath();
    m_iScreenWidth         = m_pResManager->GetUISizeByName(UI_SIZE_SCREEN_WIDTH);
    m_iFarMoveScale        = m_pResManager->GetMapFarScaleByName(m_sMapName);
    m_iScreenHeight        = m_pResManager->GetUISizeByName(UI_SIZE_SCREEN_HEIGHT);
    m_sFarBackGroundName   = m_pResManager->GetMapFarGroundByName(m_sMapName);
    
    m_iObjectDeep          = DEEP_FARGROUND_DEFAULT;
    m_iActiveWidth         = 150;
    m_iActiveHeight        = 150;
    
    m_bIsAddFarGround      = false;
    m_bNeedFixFarPoint     = true;
    m_bCanMoveFarGround    = true;

    int t_iMapXScreen      = m_pResManager->GetMapWidthByName(m_sMapName);
    int t_iMapYScreen      = m_pResManager->GetMapHeightByName(m_sMapName);
    
    m_iMapWidth            = t_iMapXScreen * m_iScreenWidth;
    m_iMapHeight           = t_iMapYScreen * m_iScreenHeight;
    m_iFarWidht            = m_pResManager->GetTextureWidthByName(m_sFarBackGroundName);
    m_iFarHeight           = m_pResManager->GetTextureHeightByName(m_sFarBackGroundName);
    
    
    FillFarRect();
    
    m_CenterPoint.set(m_iScreenWidth / 2, m_iScreenHeight / 2);
    m_LeftUpPoint.set(m_iScreenWidth / 2, m_iMapHeight - m_iScreenHeight / 2);
    m_RightUpPoint.set(m_iMapWidth - m_iScreenWidth / 2, m_iMapHeight - m_iScreenHeight / 2);
    m_RightDownPoint.set(m_iMapWidth - m_iScreenWidth / 2, m_iScreenHeight / 2);
    
     m_PlayerActiveRect.setRect(m_iScreenWidth / 2 - m_iActiveWidth / 2,
                                m_iScreenHeight / 2 - m_iActiveHeight / 2,
                                m_iActiveWidth, m_iActiveHeight);
    
    
    m_pFarBackGroundSprite = Sprite::create(m_sMapPath + m_sFarBackGroundName);
    
    m_pFarBackGroundSprite->retain();
    
    int t_iOffSetX = (m_iFarWidht - m_iScreenWidth) / 2;
    int t_iOffSetY = (m_iFarHeight - m_iScreenHeight) / 2;
    
    m_FarPosition.set( m_CenterPoint.x + t_iOffSetX, m_CenterPoint.y + t_iOffSetY );
    
    
    Point t_MaxPoint = GetRectZeroPointByID(RECT_ID_RIGHT_UP__RIGHT_UP);
    
    int t_iXMaxCount = (t_MaxPoint.x - m_CenterPoint.x) / m_iFarMoveScale;
    int t_iYMaxCount = (t_MaxPoint.y - m_CenterPoint.y) / m_iFarMoveScale;

    m_FarMaxPoint    = m_FarPosition;
    m_FarMinPoint    = Point(m_FarMaxPoint.x - t_iXMaxCount,m_FarMaxPoint.y - t_iYMaxCount);
    
    m_NearBasePoint.set(0, 0);
    m_NearPosition.set(0, 0);
    m_pFarBackGroundSprite->setPosition(m_FarPosition);
    
    m_pPhysics->CreateStaticBody(m_iMapWidth, 10, Point(m_iMapWidth / 2, 0));
    m_pPhysics->CreateStaticBody(m_iMapWidth, 10, Point(m_iMapWidth / 2, m_iMapHeight));
    m_pPhysics->CreateStaticBody(10, m_iMapHeight, Point(0, m_iMapHeight / 2));
    m_pPhysics->CreateStaticBody(10, m_iMapHeight, Point(m_iMapWidth, m_iMapHeight / 2));

    
    return true;
}


void CGMapScene::DrawGObject()
{
    if(  m_bIsAddFarGround == false)
    {
        m_pPlayer         = m_pPlayerManager->GetLocalPlayer();
        m_pNear           = DrawNode::create();
        m_PlayerPosition  = m_pPlayer->GetObjectPosition();
        m_LastPlyaerPoint = m_PlayerPosition;
        
        m_pNear->drawRect(Point(2,2), Point(m_iMapWidth - 2, m_iMapHeight - 2), Color4F(1,0,0,1));
        
        for(int i = 0; i != 100; i++)
        {
            for(int j = 0; j != 100; j++)
            {
                Point t_Start = Point(i * 100,j * 100);
                Point t_End   = Point(i * 100 + 100, j* 100 + 100);
                m_pNear->drawRect(t_Start, t_End, Color4F(1,0,0,0.5));
            }
        }
        
        
        
        m_pGameScene->addChild(m_pFarBackGroundSprite, m_iObjectDeep);
        //m_pGameScene->addChild(m_pNode,m_iObjectDeep + 1);
        m_pGameScene->addChild(m_pNear,m_iObjectDeep + 5);
        m_bIsAddFarGround = true;
    }
    
    m_PlayerPosition = m_pPlayer->GetObjectPosition();
    //FirstFixPosition();
    
    if( m_bNeedFixFarPoint )
    {
        FirstFixPosition(m_iFarMoveScale);
        m_bNeedFixFarPoint = false;
    }
    
    if( m_bCanMoveFarGround )
    {
        MoveBackGroundByScale(m_iFarMoveScale);
    }
    
    
    ProcessNearBasePoint();
    
    /*
    Point t_OffsetPoint;
    
    t_OffsetPoint.x  = m_LastPlyaerPoint.x - m_PlayerPosition.x;
    t_OffsetPoint.y  = m_LastPlyaerPoint.y - m_PlayerPosition.y;
    
    int t_iBaseEndX = (m_iMapWidth - m_iScreenWidth ) * - 1;
    int t_iBaseEndY = (m_iMapHeight - m_iScreenHeight) * - 1;
    
    
    m_NearBasePoint.x += t_OffsetPoint.x;
    m_NearBasePoint.y += t_OffsetPoint.y;

    
    if( m_NearBasePoint.x <= t_iBaseEndX )
    {
        m_NearBasePoint.x = t_iBaseEndX;
    }
    
    if( m_NearBasePoint.x >= 0 )
    {
        m_NearBasePoint.x = 0;
    }
    
    if( m_NearBasePoint.y <= t_iBaseEndY )
    {
        m_NearBasePoint.y = t_iBaseEndY;
    }
    
    if( m_NearBasePoint.y >=  0 )
    {
        m_NearBasePoint.y = 0;
    }
    */
    //m_pNode->setPosition(Point((m_iMapWidth - m_iScreenWidth) * -1,0) + t_OffsetPoint);
    //m_pNode->setPosition(m_pNode->getPosition() + t_OffsetPoint);
    m_pNode->setPosition(m_NearPosition + m_NearBasePoint);
    m_pNear->setPosition(m_NearBasePoint + m_NearPosition);
    
    auto Screen = m_pPlayer->GetScreenPoint();
    int t_iMax  = m_iMapWidth - m_iScreenWidth;
    CG_DEBUG_PRINT_1("BaseX: ",m_NearBasePoint.x);
    CG_DEBUG_PRINT_1("BaseY: ", m_NearBasePoint.y);
    CG_DEBUG_PRINT_1("ScreenX: ", Screen.x);
    CG_DEBUG_PRINT_1("ScreenY: ", Screen.y);
    CG_DEBUG_PRINT_1("PlayerX: ", m_PlayerPosition.x);
    CG_DEBUG_PRINT_1("PlayerY: ", m_PlayerPosition.y);
    CG_DEBUG_PRINT("");
    
    m_LastPlyaerPoint = m_PlayerPosition;
}


bool CGMapScene::CleareGObject()
{
    m_pFarBackGroundSprite->release();
    m_pGameScene->removeChild(m_pFarBackGroundSprite);
    return true;
}

bool CGMapScene::DeleteGObject()
{
    delete this;
    return true;
}

void CGMapScene::ProcessNearBasePoint()
{
    Point t_OffsetPoint = m_LastPlyaerPoint - m_PlayerPosition;
    
    int t_iInAnyRect = GetPlayerInAnyRect(m_PlayerPosition);
    
    int t_iBaseEndX = 0 - (m_iMapWidth - m_iScreenWidth );
    int t_iBaseEndY = 0 - (m_iMapHeight - m_iScreenHeight);
    
    switch(t_iInAnyRect)
    {
        case RECT_ID_LEFT_DOWN__LEFT_DOWN:
        {
            m_NearBasePoint.x = 0;
            m_NearBasePoint.y = 0;
            break;
        }
            
        case RECT_ID_LEFT_DOWN__LEFT_UP:
        {
            m_NearBasePoint.y += t_OffsetPoint.y;
            m_NearBasePoint.x  = 0;
            break;
        }
            
        case RECT_ID_LEFT_DOWN__RIGHT_DOWN:
        {
            m_NearBasePoint.x += t_OffsetPoint.x;
            m_NearBasePoint.y  = 0;
            break;
        }
            
        case RECT_ID_UP:
        {
            m_NearBasePoint.y  = t_iBaseEndY;
            m_NearBasePoint.x += t_OffsetPoint.x;
            break;
        }
        case RECT_ID_LEFT:
        {
            m_NearBasePoint.x  = 0;
            m_NearBasePoint.y += t_OffsetPoint.y;
            break;
        }
            
        case RECT_ID_RIGHT:
        {
            m_NearBasePoint.y += t_OffsetPoint.y;
            m_NearBasePoint.x  = t_iBaseEndX;
            break;
        }
            
        case RECT_ID_DOWN:
        {
            m_NearBasePoint.x += t_OffsetPoint.x;
            m_NearBasePoint.y  = 0;
            break;
        }
            
        case RECT_ID_CENTER:
        {
            m_NearBasePoint.x += t_OffsetPoint.x;
            m_NearBasePoint.y += t_OffsetPoint.y;
            break;
        }
        case RECT_ID_LEFT_UP__LEFT_DOWN:
        {
            m_NearBasePoint.x  = 0;
            m_NearBasePoint.y += t_OffsetPoint.y;
            break;
        }
            
        case RECT_ID_LEFT_UP__LEFT_UP:
        {
            m_NearBasePoint.x = 0;
            m_NearBasePoint.y = t_iBaseEndY;
            break;
        }
            
        case RECT_ID_LEFT_UP__RIGHT_UP:
        {
            m_NearBasePoint.x += t_OffsetPoint.x;
            m_NearBasePoint.y  = t_iBaseEndY;
            break;
        }
            
        case RECT_ID_RIGHT_UP__RIGHT_DOWN:
        {
            m_NearBasePoint.x  = t_iBaseEndX;
            m_NearBasePoint.y += t_OffsetPoint.y;
            break;
        }
            
        case RECT_ID_RIGHT_UP__RIGHT_UP:
        {
            m_NearBasePoint.x = t_iBaseEndX;
            m_NearBasePoint.y = t_iBaseEndY;
            break;
        }
            
        case RECT_ID_RIGHT_UP__LEFT_UP:
        {
            m_NearBasePoint.x += t_OffsetPoint.x;
            m_NearBasePoint.y  = t_iBaseEndY;
            break;
        }
            
        case RECT_ID_RIGHT_DOWN__LEFT_DOWN:
        {
            m_NearBasePoint.x += t_OffsetPoint.x;
            m_NearBasePoint.y  = 0;
            break;
        }
            
        case RECT_ID_RIGHT_DOWN__RIGHT_UP:
        {
            m_NearBasePoint.x  = t_iBaseEndX;
            m_NearBasePoint.y += t_OffsetPoint.y;
            break;
        }
            
        case RECT_ID_RIGHT_DOWN__RIGHT_DOWN:
        {
            m_NearBasePoint.x = t_iBaseEndX;
            m_NearBasePoint.y = 0;
            break;
        }
    }

    CGGlobalDateManager::sharedGlobalDateManager()->SetNearBasePoint(m_NearBasePoint);
}


void CGMapScene::MoveBackGroundByScale(int iScale)
{
    Point t_OffsetPoint;
    
    t_OffsetPoint.x = m_LastPlyaerPoint.x - m_PlayerPosition.x;
    t_OffsetPoint.y = m_LastPlyaerPoint.y - m_PlayerPosition.y;
    
    int t_iInAnyRect = GetPlayerInAnyRect(m_PlayerPosition);
    int t_iOrent     = GetOffsetOrientation(t_OffsetPoint);
    
    if( t_OffsetPoint.x < 0 )
    {
        t_OffsetPoint.x *= -1;
    }
    
    if( t_OffsetPoint.y < 0 )
    {
        t_OffsetPoint.y *= -1;
    }

    if( m_FarPosition.x <= m_FarMinPoint.x )
    {
        m_FarPosition.x= m_FarMinPoint.x;
    }
    
    if( m_FarPosition.y <= m_FarMinPoint.y )
    {
        m_FarPosition.y= m_FarMinPoint.y;
    }
    
    if( m_FarPosition.x >= m_FarMaxPoint.x )
    {
        m_FarPosition.x = m_FarMaxPoint.x;
    }
    
    if( m_FarPosition.y >= m_FarMaxPoint.y )
    {
        m_FarPosition.y = m_FarMaxPoint.y;
    }
    
    CG_DEBUG_PRINT_1("FarX: ", m_FarPosition.x);
    CG_DEBUG_PRINT_1("FarY: ", m_FarPosition.y);
    

    
    switch(t_iInAnyRect)
    {
            
        case -1:
        {
            ///nothing to do;
            break;
        }
        case RECT_ID_CENTER:
        {
            ///中间的矩形！！！老子不用英文写注释了！！！
            if( t_iOrent == OFFSET_LEFT)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == - 1 )
            {
                CG_DEBUG_PRINT("-1");
            }
            
            break;

        }
        
        case RECT_ID_LEFT_DOWN__RIGHT_DOWN:
        {
            
            /// can not move to down
            if( t_iOrent == OFFSET_LEFT)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
                CG_DEBUG_PRINT("LeftDownRightDown");
                CG_DEBUG_PRINT_1("offx: ", t_OffsetPoint.x);
                CG_DEBUG_PRINT_1("offy: ", t_OffsetPoint.y);
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            
            break;
        }
            
        case RECT_ID_LEFT_DOWN__LEFT_DOWN:
        {
            CG_DEBUG_PRINT("leftdown_leftdown")
            /// can not move to left and down
            if( t_iOrent == OFFSET_LEFT)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                //m_FarPosition.y -= t_OffsetPoint. y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                ///nope
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
                //_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            
            break;
        }
            
        case RECT_ID_LEFT_DOWN__LEFT_UP:
        {
            
            /// can not move to left
            if( t_iOrent == OFFSET_LEFT)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            
            break;
        }
            
        case RECT_ID_LEFT_UP__RIGHT_UP:
        {
            ///can not move to up
            
            if( t_iOrent == OFFSET_LEFT)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                m_FarPosition.x -= t_OffsetPoint.x /iScale;
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            
            break;
        }
            
        case RECT_ID_LEFT_UP__LEFT_UP:
        {
            ///can not move to left and up
            
            if( t_iOrent == OFFSET_LEFT)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            
            break;
        }
            
        case RECT_ID_LEFT_UP__LEFT_DOWN:
        {
            ///can not move to left
            
            if( t_iOrent == OFFSET_LEFT)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            
            break;
        }
            
            
        case RECT_ID_RIGHT_UP__LEFT_UP:
        {
            /// can not move to up
            
            if( t_iOrent == OFFSET_LEFT)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
             ///no
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            
            break;

        }
            
        case RECT_ID_RIGHT_UP__RIGHT_UP:
        {
            /// can not move to right and up
            
            if( t_iOrent == OFFSET_LEFT)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            
            break;
            
        }
            
        case RECT_ID_RIGHT_UP__RIGHT_DOWN:
        {
            /// can not move to right
            
            if( t_iOrent == OFFSET_LEFT)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                /// no
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            
            break;
            
        }
            
        case RECT_ID_RIGHT_DOWN__LEFT_DOWN:
        {
            /// can not move to down
            if( t_iOrent == OFFSET_LEFT)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
            /// no
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            
            break;
            
        }
            
        case RECT_ID_RIGHT_DOWN__RIGHT_UP:
        {
            /// can not move to right
            
            if( t_iOrent == OFFSET_LEFT)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                /// no
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            
            break;
            
        }
            
        case RECT_ID_RIGHT_DOWN__RIGHT_DOWN:
        {
            /// can not move to right and down
            if( t_iOrent == OFFSET_LEFT)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                ///no
            }
            
            
            break;
            
        }
        
        case RECT_ID_RIGHT:
        {
            /// can not move to right
            if( t_iOrent == OFFSET_LEFT)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
                break;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                /// no
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                //m_FarPosition.x += t_OffsetPoint.x / iScale;
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            
            
            break;
            
        }
            
        case RECT_ID_LEFT:
        {
            /// can not move to left
            if( t_iOrent == OFFSET_LEFT)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
                m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                //m_FarPosition.x -= t_OffsetPoint.x / iScale;
                m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            
            break;
            
        }
        case RECT_ID_DOWN:
        {
            /// can not move to down
            if( t_iOrent == OFFSET_LEFT)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                /// no
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
                //m_FarPosition.y -= t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            
            
            break;
            
        }

        case RECT_ID_UP:
        {
            
            ///can not move to up
            
            if( t_iOrent == OFFSET_LEFT)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_UP)
            {
                ///no
            }
            
            if( t_iOrent == OFFSET_DOWN)
            {
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_UP)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_LEFT_DOWN)
            {
                m_FarPosition.x += t_OffsetPoint.x / iScale;
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_UP)
            {
                m_FarPosition.x -= t_OffsetPoint.x / iScale;
            }
            
            if( t_iOrent == OFFSET_RIGHT_DOWN)
            {
                m_FarPosition.x -= t_OffsetPoint.x /iScale;
                //m_FarPosition.y += t_OffsetPoint.y / iScale;
            }
            
            break;
            
        }
   
        
            
    }
    
    
    
    m_pFarBackGroundSprite->setPosition(m_FarPosition);



}


void CGMapScene::FillFarRect()
{
    STRUCT_FARRECT far;
    
    far.iRectID = RECT_ID_UP;
    
    far.Rect.setRect(m_iScreenWidth, m_iMapHeight - m_iScreenHeight / 2,
                     m_iMapWidth - m_iScreenWidth * 2, m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_DOWN;
    
    far.Rect.setRect(m_iScreenWidth, 0,
                     m_iMapWidth - m_iScreenWidth * 2, m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_LEFT;
    
    far.Rect.setRect(0, m_iScreenHeight,
                     m_iScreenWidth / 2 , m_iMapHeight - m_iScreenHeight * 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_RIGHT;
    
    far.Rect.setRect(m_iMapWidth - m_iScreenWidth / 2, m_iScreenHeight,
                     m_iScreenWidth / 2 , m_iMapHeight - m_iScreenHeight * 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_LEFT_DOWN__LEFT_UP;
    
    far.Rect.setRect(0, m_iScreenHeight / 2,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_LEFT_DOWN__LEFT_DOWN;
    
    far.Rect.setRect(0, 0,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_LEFT_DOWN__RIGHT_DOWN;
    
    far.Rect.setRect(m_iScreenWidth / 2, 0,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_LEFT_UP__LEFT_UP;
    
    far.Rect.setRect(0, m_iMapHeight - m_iScreenHeight / 2,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_LEFT_UP__LEFT_DOWN;
    
    far.Rect.setRect(0, m_iMapHeight - m_iScreenHeight,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_LEFT_UP__RIGHT_UP;
    
    far.Rect.setRect(m_iScreenWidth / 2, m_iMapHeight - m_iScreenHeight / 2,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_RIGHT_UP__LEFT_UP;
    
    far.Rect.setRect(m_iMapWidth - m_iScreenWidth, m_iMapHeight - m_iScreenHeight / 2,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_RIGHT_UP__RIGHT_UP;
    
    far.Rect.setRect(m_iMapWidth - m_iScreenWidth / 2, m_iMapHeight - m_iScreenHeight / 2,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_RIGHT_UP__RIGHT_DOWN;
    
    far.Rect.setRect(m_iMapWidth - m_iScreenWidth / 2, m_iMapHeight - m_iScreenHeight,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_RIGHT_DOWN__LEFT_DOWN;
    
    far.Rect.setRect(m_iMapWidth - m_iScreenWidth, 0,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_RIGHT_DOWN__RIGHT_DOWN;
    
    far.Rect.setRect(m_iMapWidth - m_iScreenWidth / 2, 0,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    far.iRectID = RECT_ID_RIGHT_DOWN__RIGHT_UP;
    
    far.Rect.setRect(m_iMapWidth - m_iScreenWidth / 2, m_iScreenHeight / 2,
                     m_iScreenWidth / 2 , m_iScreenHeight / 2);
    
    m_FarRectList.push_back(far);
    
    
    far.iRectID = RECT_ID_CENTER;
    
    far.Rect.setRect(m_iScreenWidth / 2, m_iScreenHeight / 2,
                     m_iMapWidth - m_iScreenWidth ,m_iMapHeight - m_iScreenHeight);
    
    m_FarRectList.push_back(far);
    
    
    
    
    m_pNode = DrawNode::create();
    
    for(auto i : m_FarRectList)
    {
        Vec2 start(i.Rect.origin);
        Vec2 end(i.Rect.origin.x + i.Rect.size.width,i.Rect.origin.y + i.Rect.size.height);
        m_pNode->drawRect(start,end , Color4F(1,1,0,1));
    }
    m_pGameScene->addChild(m_pNode,m_iObjectDeep + 2);
}

void CGMapScene::FirstFixPosition(int iScale)
{
    int t_iInAnyRect = GetPlayerInAnyRect(m_PlayerPosition);
    m_PlayerPosition = m_pPlayer->GetObjectPosition();
    Point t_Offset   = Point(0,0);
    
    Point t_FarPosition;
    
    switch(t_iInAnyRect)
    {
            
        case RECT_ID_LEFT:
        {
            t_Offset.y = m_PlayerPosition.y - m_CenterPoint.y;
            break;
        }
            
        case RECT_ID_DOWN:
        {
            t_Offset.x = m_PlayerPosition.x - m_CenterPoint.x;
            break;
        }
            
        case RECT_ID_LEFT_DOWN__LEFT_DOWN:
        {
            t_Offset.x = 0;
            t_Offset.y = 0;
            break;
        }
            
        case RECT_ID_LEFT_DOWN__LEFT_UP:
        {
            t_Offset.y = m_PlayerPosition.y - m_CenterPoint.y;
            break;
        }
            
        case RECT_ID_LEFT_DOWN__RIGHT_DOWN:
        {
            t_Offset.x = m_PlayerPosition.x - m_CenterPoint.x;
            break;
        }
            
        case RECT_ID_LEFT_UP__LEFT_DOWN:
        {
            t_Offset.y = m_PlayerPosition.y - m_CenterPoint.y;
            break;
        }
            
        case RECT_ID_LEFT_UP__LEFT_UP:
        {
            t_Offset.y = m_PlayerPosition.y - m_CenterPoint.y;
            break;
        }
            
        case RECT_ID_RIGHT_DOWN__LEFT_DOWN:
        {
            t_Offset.x = m_PlayerPosition.x - m_CenterPoint.x;
            break;
        }
            
        case RECT_ID_RIGHT_DOWN__RIGHT_DOWN:
        {
            t_Offset.x = m_PlayerPosition.x - m_CenterPoint.x;
            break;
        }
            
        default:
        {
            t_Offset.x = m_PlayerPosition.x - m_CenterPoint.y;
            t_Offset.y = m_PlayerPosition.y - m_CenterPoint.y;
            break;
        }
            
    }
    
    Point MaxPoint = GetRectZeroPointByID(RECT_ID_RIGHT_UP__RIGHT_UP);
    
    if( t_Offset.x >= (MaxPoint.x - m_CenterPoint.x ))
    {
        t_Offset.x = MaxPoint.x - m_CenterPoint.x;
    }
    
    if(  t_Offset.y >= (MaxPoint.y - m_CenterPoint.y ))
    {
        t_Offset.y = MaxPoint.y - m_CenterPoint.y;
    }
    
    t_FarPosition.x -= t_Offset.x / iScale;
    t_FarPosition.y -= t_Offset.y / iScale;
    
    
    if( iScale == 10 )
    {
        m_pFarBackGroundSprite->setPosition(t_FarPosition);
    }
    
    if( iScale == 5 )
    {
        ///near
    }
    
    
    
}

Point CGMapScene::GetRectZeroPointByID(int iID)
{
    for(auto i : m_FarRectList)
    {
        if( i.iRectID == iID )
        {
            return i.Rect.origin;
        }
    }
    
    throw CGException("GetRectZeroPoint Can Not Find");
}

int CGMapScene::GetPlayerInAnyRect(const Point &Point)
{
    
    for(auto i : m_FarRectList)
    {
        if(i.Rect.containsPoint(Point))
        {
            return i.iRectID;
        }
    }
    ///throw CGException("GetPlayerInAnyRect Is Can Not Find Point");
    return -1;
    
}

int CGMapScene::GetOffsetOrientation(const Point &Offset)
{
    if( Offset.x == 0 && Offset.y > 0 )
    {
        return OFFSET_DOWN;
    }
    
    else if( Offset.x == 0 && Offset.y < 0 )
    {
        return OFFSET_UP;
    }
    
    else if( Offset.x > 0 && Offset.y == 0 )
    {
        return OFFSET_LEFT;
    }
    
    else if( Offset.x < 0 && Offset.y == 0 )
    {
        return OFFSET_RIGHT;
    }
    
    else if( Offset.x < 0 && Offset.y < 0 )
    {
        return OFFSET_RIGHT_UP;
    }
    
    else if( Offset.x < 0 && Offset.y > 0 )
    {
        return OFFSET_RIGHT_DOWN;
    }
    
    else if( Offset.x > 0 && Offset.y > 0 )
    {
        return OFFSET_LEFT_DOWN;
    }
    
    else if( Offset.x > 0 && Offset.y < 0 )
    {
        return OFFSET_LEFT_UP;
    }
    
    else
    {
        return -1;
    }
}

