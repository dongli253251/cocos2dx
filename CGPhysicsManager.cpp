//
//  CGPhysicsManager.cpp
//  Game
//
//  Created by dongli on 2016/11/30.
//
//

#include "CGPhysicsManager.hpp"
#include "CGException.hpp"
#include <Box2D/Box2D.h>
#include "CGPhysicsObject.hpp"
bool CGPhysicsManager::InitGObject()
{
    
    m_iPhysicsScale    = PHYSICS_SCALE;
    m_fDefaultDensity  = 0.5f;
    m_fDefaultFriction = 0.1f;
    m_iDefaultWidth    = 1;
    m_iDefaultHeight   = 1;
    m_bCanRunPhysics   = true;
    CreatePhysicsWorld();
    
    return true;
}

bool CGPhysicsManager::CleareGObject()
{
    delete m_pPhysicsWorld;
    return true;
}

bool CGPhysicsManager::DeleteGObject()
{
    delete this;
    return true;
}

void CGPhysicsManager::ProcessPhysicsTask()
{
    
    if( m_bCanRunPhysics )
    {
        m_pPhysicsWorld->Step(1.0f / 60.0f , 6.0f, 2.0f);
    }
    
    if( ! m_vPhysicsList.empty() )
    {
        for( auto i : m_vPhysicsList )
        {
            i->ProcessPhysicsObject();
        }
    }
    
    auto it = m_vPhysicsList.begin();
    
    for( ;it != m_vPhysicsList.end(); )
    {
        if( (*it)->GetIsDead() )
        {
            (*it)->DeleteGObject();
            
            m_vPhysicsList.erase(it);
            
            break;
        }
        else
        {
            it ++;
        }
    }
    
}

void CGPhysicsManager::CreatePhysicsWorld()
{
    b2Vec2 t_Gravity(0,-10);
    
    auto t_pWorld = new b2World(t_Gravity);
    
    if( t_pWorld != nullptr )
    {
        m_pPhysicsWorld = t_pWorld;
    }
    
    else
    {
        throw CGException("PhysicsWorld Create Error");
    }
}

void CGPhysicsManager::AddPhysicsObjectToList(CGPhysicsObject *pObject)
{
    bool t_bIsReply = false;
    
    for( auto i : m_vPhysicsList )
    {
        if( i == pObject )
        {
            t_bIsReply = true;
        }
    }
    
    if( !t_bIsReply )
    {
        m_vPhysicsList.push_back(pObject);
    }
}

void CGPhysicsManager::CreatePhysicsWorld(float fX, float fY)
{
    b2Vec2 t_Gravity(fX,fY);
    
    auto t_pWorld = new b2World(t_Gravity);
    
    if( t_pWorld != nullptr )
    {
        m_pPhysicsWorld = t_pWorld;
    }
    
    else
    {
        throw CGException("PhysicsWorld Create Error");
    }

}

void CGPhysicsManager::DeletePhysicsBody(b2Body *pBody)
{
    m_pPhysicsWorld->DestroyBody(pBody);
}

b2Body * CGPhysicsManager::CreateStaticBody(int iWidth, int iHeight, const Point &Position)
{
    b2BodyDef        t_BodyDef;
    b2PolygonShape   t_Shape;
    b2FixtureDef     t_Fixture;
    
    t_Shape.SetAsBox(iWidth / m_iPhysicsScale, iHeight / m_iPhysicsScale);
    t_BodyDef.position    = b2Vec2(Position.x / m_iPhysicsScale,Position.y / m_iPhysicsScale);
    t_BodyDef.type        = b2_staticBody;
    t_Fixture.shape       = &t_Shape;
    t_Fixture.density     = 0;
    t_Fixture.friction    = 0.5;
    t_Fixture.restitution = 0.1f;
    
    auto t_pBody          = m_pPhysicsWorld->CreateBody(&t_BodyDef);
    
    t_pBody->CreateFixture(&t_Fixture);
    
    return t_pBody;
    
}

b2Body * CGPhysicsManager::CreateDynamicBody(int iWidth, int iHeight, const Point &Position)
{
    b2BodyDef        t_BodyDef;
    b2PolygonShape   t_Shape;
    b2FixtureDef     t_Fixture;
    
    t_Shape.SetAsBox(iWidth / m_iPhysicsScale, iHeight / m_iPhysicsScale);
    t_BodyDef.position    = b2Vec2(Position.x / m_iPhysicsScale,Position.y / m_iPhysicsScale);
    t_BodyDef.type        = b2_dynamicBody;
    t_Fixture.shape       = &t_Shape;
    t_Fixture.density     = 0.1f;
    t_Fixture.friction    = 0.5f;
    t_Fixture.restitution = 0.1f;
    
    auto t_pBody          = m_pPhysicsWorld->CreateBody(&t_BodyDef);
    
    t_pBody->CreateFixture(&t_Fixture);
    
    return t_pBody;
}
