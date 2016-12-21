//
//  CGPlayerManager.cpp
//  Game
//
//  Created by dongli on 2016/11/21.
//
//

#include "CGPlayerManager.hpp"
#include "CGDataType.h"
#include "CGPlayer.hpp"

bool CGPlayerManager::InitGObject()
{
    return true;
}

bool CGPlayerManager::CleareGObject()
{
    return true;
}

bool CGPlayerManager::DeleteGObject()
{
    delete this;
    return true;
}

void CGPlayerManager::ProcessPlayerTask()
{
    if( ! m_vNetPlayerList.empty() )
    {
        for( auto i : m_vNetPlayerList )
        {
            i->DrawGObject();
        }
    }

    if( ! m_vLocalPlayerList.empty() )
    {
        for( auto i : m_vLocalPlayerList )
        {
            i->DrawGObject();
        }
    }
   
}

void CGPlayerManager::AddNetPlayerToList(CGPlayer *pPlayer)
{
    bool t_bIsReplay = false;
    
    for( auto i : m_vNetPlayerList )
    {
        if( i == pPlayer )
        {
            t_bIsReplay = true;
            CG_DEBUG_PRINT("AddNetPlayerToList Is Replay");
        }
    }
    
    if( !t_bIsReplay )
    {
        m_vNetPlayerList.push_back(pPlayer);
    }
}

void CGPlayerManager::AddLocalPlayerToList(CGPlayer *pPlayer)
{
    bool t_bIsReplay = false;
    
    for( auto i : m_vLocalPlayerList )
    {
        if( i == pPlayer )
        {
            t_bIsReplay = true;
            CG_DEBUG_PRINT("AddLocalPlayerToList Is Replay");
        }
    }
    
    if( !t_bIsReplay )
    {
        m_vLocalPlayerList.push_back(pPlayer);
    }

}

void CGPlayerManager::DeleteNetPlayer(CGPlayer *pPlayer)
{
    bool t_bIsFind = false;
    
    auto it = m_vNetPlayerList.begin();
    
    for(; it != m_vNetPlayerList.end() ;)
    {
        if( *it == pPlayer )
        {
            m_vNetPlayerList.erase(it);
            t_bIsFind = true;
        }
    }
    
    if( !t_bIsFind )
    {
        CG_DEBUG_PRINT("DeleteNetPlayer Is Can Not Find");
    }
}

CGPlayer * CGPlayerManager::GetLocalPlayer()
{
    if( ! m_vLocalPlayerList.empty() )
    {
        return m_vLocalPlayerList[0];
    }
    else
    {
        CG_DEBUG_PRINT("GetLocalPlayer Is Empty");
        throw CGException("LocalPlayer List Is Empty");
        return 0;
    }
}

void CGPlayerManager::DeleteNetPlayerAll()
{
    m_vNetPlayerList.clear();
}

void CGPlayerManager::DeleteLocalPlayer(CGPlayer *pPlayer)
{
    bool t_bIsFind = false;
    
    auto it = m_vLocalPlayerList.begin();
    
    for(; it != m_vLocalPlayerList.end() ;)
    {
        if( *it == pPlayer )
        {
            m_vLocalPlayerList.erase(it);
            t_bIsFind = true;
        }
    }
    
    if( !t_bIsFind )
    {
        CG_DEBUG_PRINT("DeleteLocalPlayer Is Can Not Find");
    }

}

void CGPlayerManager::DeleteLocalPlayerAll()
{
    m_vLocalPlayerList.clear();
}
