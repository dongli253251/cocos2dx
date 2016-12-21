//
//  CGPhysicsObject.cpp
//  Game
//
//  Created by dongli on 2016/12/2.
//
//

#include "CGPhysicsObject.hpp"
#include "CGException.hpp"
#include <Box2D/Box2D.h>
#include "CGScene.hpp"

extern CGScene * GetGScene();

CGPhysicsObject * CGPhysicsObject::CreatePhysicsObject(int iType, int iWidth, int iHeight, float fX, float fY)
{
    auto t_pObject = new CGPhysicsObject(iType,iWidth,iHeight,fX,fY);
    
    if( t_pObject != nullptr )
    {
        t_pObject->InitGObject();
        return t_pObject;
    }
    
    else
    {
        throw CGException("CreatePhysicsObject Is Create Error");
        return nullptr;
    }
}

bool CGPhysicsObject::InitGObject()
{
    m_bIsDead         = false;
    m_bIsDisplayRect  = true;
    
    m_pGameScene      = GetGScene();
    m_pPhysicsManager = CGPhysicsManager::sharedPhysicsManager();
    
    if( m_iPhysicsType == PHYSICS_TYPE_STATIC )
    {
        m_pPhysicsBody = m_pPhysicsManager->CreateStaticBody(m_iPhysicsWidth, m_iPhysicsHeight, m_PhysicsPosition);
    }
    
    if( m_iPhysicsType == PHYSICS_TYPE_DYNAMIC )
    {
        m_pPhysicsBody = m_pPhysicsManager->CreateDynamicBody(m_iPhysicsWidth, m_iPhysicsHeight, m_PhysicsPosition);
    }
    
    
    m_pRectNode = DrawNode::create();
    
    Point t_Start;
    Point t_End;
    
    t_Start.x = m_PhysicsPosition.x - m_iPhysicsWidth / 2;
    t_Start.y = m_PhysicsPosition.y - m_iPhysicsHeight / 2;
    
    t_End.x   = m_PhysicsPosition.x + m_iPhysicsWidth / 2;
    t_End.y   = m_PhysicsPosition.y + m_iPhysicsHeight / 2;
    
    m_pRectNode->drawRect(t_Start, t_End, Color4F(1,0,0,1));
    
    m_pGameScene->addChild(m_pRectNode,DEEP_UI_DEFAULT);
    
    m_PhysicsRect.setRect(t_Start.x, t_Start.y, m_iPhysicsWidth, m_iPhysicsHeight);

    
    return true;
}

void CGPhysicsObject::ProcessPhysicsObject()
{
    m_PhysicsPosition.x = m_pPhysicsBody->GetPosition().x * PHYSICS_SCALE;
    m_PhysicsPosition.y = m_pPhysicsBody->GetPosition().y * PHYSICS_SCALE;
    
    if( m_bIsDisplayRect )
    {
        m_pRectNode->setVisible(true);
    }
    else
    {
        m_pRectNode->setVisible(false);
    }
    
    Point t_Start;
    
    t_Start.x = m_PhysicsPosition.x - m_iPhysicsWidth / 2 ;
    t_Start.y = m_PhysicsPosition.y - m_iPhysicsHeight / 2;
    
    m_PhysicsRect.setRect(t_Start.x, t_Start.y, m_iPhysicsWidth, m_iPhysicsHeight);
    
    m_fPhysicsXSpeed = m_pPhysicsBody->GetLinearVelocity().x;
    m_fPhysicsYSpeed = m_pPhysicsBody->GetLinearVelocity().y;
}

void CGPhysicsObject::SetVerticalSpeed(float fSpeed)
{
    b2Vec2 t_Speed;
    
    t_Speed.x = m_pPhysicsBody->GetLinearVelocity().x;
    t_Speed.y = fSpeed;
    
    m_pPhysicsBody->SetLinearVelocity(t_Speed);
}

void CGPhysicsObject::SetHorizontalSpeed(float fSpeed)
{
    b2Vec2 t_Speed;
    
    t_Speed.x = fSpeed;
    t_Speed.y =  m_pPhysicsBody->GetLinearVelocity().y;
    
    m_pPhysicsBody->SetLinearVelocity(t_Speed);
}

void CGPhysicsObject::ApplyForce(int iX, int iY)
{
    b2Vec2 t_Force;
    
    t_Force.x = iX;
    t_Force.y = iY;
    
    m_pPhysicsBody->ApplyForceToCenter(t_Force, 1);
    
}

void CGPhysicsObject::SetPhysicsPosition(const Point &Position)
{
    m_PhysicsPosition = Position;
    
    m_pPhysicsBody->SetTransform(b2Vec2(Position.x / PHYSICS_SCALE,Position.y / PHYSICS_SCALE), 0);
}

bool CGPhysicsObject::CleareGObject()
{
    m_pGameScene->removeChild(m_pRectNode);
    return true;
}

bool CGPhysicsObject::DeleteGObject()
{
    ///delete body.
    m_pPhysicsManager->DeletePhysicsBody(m_pPhysicsBody);
    delete this;
    return true;
}

