//
//  CGGlobalDateManager.cpp
//  Game
//
//  Created by dongli on 2016/11/21.
//
//

#include "CGGlobalDateManager.hpp"
#include "CGDataType.h"

bool CGGlobalDateManager::InitGObject()
{
    m_bBulletLunchSuccess = true;
    m_bCanGameStart       = false;
    m_bItemUseSuccess     = false;
    m_bIsGameOver         = false;
    m_bCreateRoomSuccess  = false;
    
    
    return true;
}

bool CGGlobalDateManager::DeleteGObject()
{
    delete this;
    return true;
}

bool CGGlobalDateManager::CleareGObject()
{
    return true;
}

