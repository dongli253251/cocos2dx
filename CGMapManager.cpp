//
//  CGMapManager.cpp
//  Game
//
//  Created by dongli on 2016/11/27.
//
//

#include "CGMapManager.hpp"

bool CGMapManager::InitGObject()
{
    return true;
}

bool CGMapManager::CleareGObject()
{
    return true;
}

bool CGMapManager::DeleteGObject()
{
    delete this;
    return true;
}

const Point& CGMapManager::GetFarRectZeroPoint(int iID)
{
    const std::list<STRUCT_FARRECT>& Rect = m_vMapList[0]->GetFarRectList();
    
    for(auto it = Rect.begin(); it != Rect.end(); it++)
    {
        if( (*it).iRectID == iID )
        {
            return (*it).Rect.origin;
        }
    }
    
    throw CGException("GetFarRectZeroPoint Can Not Find");
    
}

void CGMapManager::AddMapSceneToList(CGMapScene *pMap)
{
    bool t_bIsReply = false;
    
    for(auto i : m_vMapList)
    {
        if( i == pMap )
        {
            t_bIsReply =  true;
        }
    }
    
    if( ! t_bIsReply )
    {
        m_vMapList.push_back(pMap);
    }
}

void CGMapManager::ProcessMapScene()
{
    if( ! m_vMapList.empty() )
    {
        for( auto i : m_vMapList )
        {
            i->DrawGObject();
        }

    }
}

