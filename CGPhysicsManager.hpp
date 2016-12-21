//
//  CGPhysicsManager.hpp
//  Game
//
//  Created by dongli on 2016/11/30.
//
//

#ifndef CGPhysicsManager_hpp
#define CGPhysicsManager_hpp


#include <iostream>
#include <CGDataType.h>
#include <CGComObject.hpp>

class CGPhysicsObject;
class b2Body;
class b2World;
class CG_CLASS CGPhysicsManager:public CGComObject
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGPhysicsManager)
    
    CG_CONSTRUCTION_COPY(CGPhysicsManager)
    
    
public:
    CG_DESTROY_DEFAULT(CGPhysicsManager)
    
    CG_OVERLOAD_COM;
    
    CG_SINGLETON_CREATE(PhysicsManager)
    
    CG_RESULT_VOID ProcessPhysicsTask();
    
    b2Body * CreateStaticBody(int iWidth,int iHeight,const Point& Position);
    
    b2Body * CreateDynamicBody(int iWidth,int iHeight,const Point& Position);
    
    b2Body * CreateDynamicBody(int iWidth,int iHeight,const Point& Position,float fFri,float fDes);
    
    b2Body * CreateDynamicBody(const Point& Position);
    
    CG_RESULT_VOID CreatePhysicsWorld();
    
    CG_RESULT_VOID CreatePhysicsWorld(float fX,float fY);
    
    CG_RESULT_VOID DeletePhysicsBody(b2Body * pBody);
    
    CG_RESULT_VOID AddPhysicsObjectToList(CGPhysicsObject * pObject);
    
protected:
    
    std::vector<CGPhysicsObject *>          m_vPhysicsList;
    b2World *                               m_pPhysicsWorld;
    int                                     m_iPhysicsScale;
    int                                     m_iDefaultHeight;
    int                                     m_iDefaultWidth;
    bool                                    m_bCanRunPhysics;
    float                                   m_fDefaultFriction;
    float                                   m_fDefaultDensity;
};

#endif /* CGPhysicsManager_hpp */
