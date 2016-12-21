//
//  CGProtocolManager.cpp
//  Game
//
//  Created by dongli on 2016/10/28.
//
//

#include "CGProtocolManager.hpp"
#include <iostream>
#include "CGSocket.hpp"
#include "CGScene.hpp"


extern CGScene * GetGScene();

static CGProtocolManager * g_pProtocolManager = NULL;

CGProtocolManager * CGProtocolManager::sharedProtocolManager()
{
    if(g_pProtocolManager == NULL)
    {
        g_pProtocolManager = new CGProtocolManager();
        
        if(g_pProtocolManager != NULL)
        {
            g_pProtocolManager->InitGObject();
            return g_pProtocolManager;
        }
        else
        {
            std::cout<<"CGProtocolManager Create Is Error"<<std::endl;
            return NULL;
        }
    }
    else
    {
        return g_pProtocolManager;
    }
}

bool CGProtocolManager::DeleteGObject()
{
    delete this;
    return true;
}

bool CGProtocolManager::InitGObject()
{
    auto t_pScene = GetGScene();
    m_pSocket = t_pScene->GetSocket();
    return true;
}

bool CGProtocolManager::CleareGObject()
{
    return true;
}

bool CGProtocolManager::RecvProtocolPacket()
{
    return true;
}

void CGProtocolManager::SendProtocolThread()
{
    if(!m_vSendRequestVec.empty())
    {
        std::vector<CGRequest *>::iterator i = m_vSendRequestVec.begin();
        for(;i != m_vSendRequestVec.end(); i++)
        {
            if((*i)->GetSendOver() == false)
            {
                std::string t_sHead = (*i)->GetProtocolPacketHeadString();
                std::string t_sBody = (*i)->GetProtocolPakcetString();
                m_pSocket->SendSocketDate(t_sHead);
                m_pSocket->SendSocketDate(t_sBody);
                (*i)->SetSendOver(true);
            }
        }
    }
}

bool CGProtocolManager::PushRequestToSendStack(CGRequest * pRequest)
{
    pRequest->EncapsulationProtocolPacket();
    //
    m_vSendRequestVec.push_back(pRequest);
    return true;
}

bool CGProtocolManager::ProcessProtocolPakcet()
{
    
    auto it = m_vSendRequestVec.begin();
    
    for(;it != m_vSendRequestVec.end();it++)
    {
        (*it)->SetSendOver(true);
    }
    
    
    if( !m_vSendRequestVec.empty() )
    {
        
        auto it = m_vSendRequestVec.begin();
        
        for(;it != m_vSendRequestVec.end();)
        {
            if((*it)->GetSendOver())
            {
                (*it)->DeleteGObject();
                m_vSendRequestVec.erase(it);
                break;
            }
            else
            {
                it++;
            }
        }

    }
    
    
    return true;
    
}
