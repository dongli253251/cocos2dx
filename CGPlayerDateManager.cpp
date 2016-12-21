//
//  CGPlayerDateManager.cpp
//  Game
//
//  Created by dongli on 2016/11/16.
//
//

#include "CGPlayerDateManager.hpp"
#include "CGException.hpp"

bool CGPlayerDateManager::InitGObject()
{
 
    m_iPlayerHorizontalForceX   = 2000;
    m_iPlayerHorizontalForceY   = 800;
    m_iPlayerVerticalForceX     = 0;
    m_iPlayerVerticalForceY     = 1500;
    m_iPlayerObliqueForceX      = 1500;
    m_iPlayerObliqueForceY      = 1000;
    m_iPlayerObliqueDownForceX  = 800;
    m_iPlayerObliqueDownForceY  = 500;
    m_iPlayerVerticalDownForce  = -500;
    m_iPlayerVerticalMaxSpeed   = 50;
    m_iPlayerHorizontalMaxSpeed = 50;
    m_iPlayerBuoyancy           = 00;
    m_iPlayerBulletSpeed        = 150;
    m_iPlayerLife               = 100;
    m_iPlayerRank               = 1;
    m_iPlayerAttack             = 10;
    m_iPlayerEnergy             = 100;
    m_iPlayerDefense            = 10;
    m_iPlayerBulletInterval     = 100;
    m_iPlayerMaxLife            = 100;
    m_iPlayerArmor              = 100;
    m_iPlayerMaxArmor           = 100;
    m_iPlayerTemp               = 0;
    m_iPlayerMaxTemp            = 100;
    m_iPlayerTempAddValue       = 1;
    m_iPlayerTempReduceValue    = 4;
    m_sBulletName               = "BulletA";
    m_sPlayerID                 = "dongli253251";
    return true;
}

bool CGPlayerDateManager::CleareGObject()
{
    
    
    
    return true;
}




bool CGPlayerDateManager::DeleteGObject()
{
    delete this;
    return true;
}

void CGPlayerDateManager::ProcessDate()
{
    
}
