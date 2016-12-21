//
//  CGWeaponManager.cpp
//  Game
//
//  Created by dongli on 2016/11/21.
//
//

#include "CGWeaponManager.hpp"
#include "CGDataType.h"
#include "CGBullet.hpp"
#include "CGPlayer.hpp"
#include "CGUIManager.hpp"
#include "CGPlayerDateManager.hpp"
#include "CGProtocolManager.hpp"
#include "CGPlayerManager.hpp"
#include "CGRequest.hpp"
#include <cocos2d.h>
using namespace cocos2d;

long GetMilliSecond()
{
    timeval time;
    gettimeofday(&time, 0);
    
    return time.tv_sec * 1000 + time.tv_usec / 1000;
}

bool CGWeaponManager::InitGObject()
{
    m_bWeaponEnable = true;
    m_bBulletEnable = true;
    m_bCanLunch     = true;
    m_lLastTime     = 0;
    m_pDate         = CGPlayerDateManager::sharedPlayerDateManager();
    m_pUI           = CGUIManager::sharedUIManager();
    m_pPlayer       = CGPlayerManager::sharedPlayerManager();
    return true;
}

bool CGWeaponManager::CleareGObject()
{
    return true;
}

bool CGWeaponManager::DeleteGObject()
{
    delete this;
    return true;
}

void CGWeaponManager::AddWeaponToList(CGWeaponBase *pWeapon)
{
    bool t_bIsReply = false;
    
    for(auto i : m_vWeaponList)
    {
        if( i == pWeapon )
        {
            t_bIsReply = true;
            CG_DEBUG_PRINT("AddWeaponToList Reaply");
        }
    }
    
    if( !t_bIsReply )
    {
        m_vWeaponList.push_back(pWeapon);
    }
}

void CGWeaponManager::ProcessWeaponTask()
{
    
    if( ! m_vWeaponList.empty() )
    {
        for( auto i : m_vWeaponList )
        {
            i->DrawGObject();
        }
        
        
        auto it = m_vWeaponList.begin();
        
        for(; it != m_vWeaponList.end() ;)
        {
            if( (*it)->GetIsDead() == true )
            {
                (*it)->DeleteGObject();
                m_vWeaponList.erase(it);
                break;
            }
            else
            {
                it++;
            }
        }
    }
    
    if( m_bWeaponEnable )
    {
        if( m_bBulletEnable )
        {
            if( m_pUI->GetLunchButtonIsTouch() )
            {
                CGPlayer *  t_pPlayer   = m_pPlayer->GetLocalPlayer();
                Point       t_Position  = t_pPlayer->GetObjectPosition();
                int         t_iOrient   = t_pPlayer->GetPlayerOrientation();
                
                m_sBulletName           = m_pDate->GetBulletName();
                m_iBulletSpeed          = m_pDate->GetPlayerBulletSpeed();
                m_iBulletInterval       = m_pDate->GetPlayerBulletInterval();
                
                if( m_bCanLunch )
                {
                    m_lLastTime          = GetMilliSecond();
                    m_bCanLunch          = false;
                    
                    CGBullet * t_pBullet = CGBullet::CreateBullet(m_sBulletName, t_Position, t_iOrient,BULLET_OWNER_LOCAL);
                    
                    auto * t_pRequest = CGRequest_CreateBullet::CreateRequest_CreateBullet();
                    
                    auto t_sPlayerID  = CGPlayerDateManager::sharedPlayerDateManager()->GetPlayerID();
                    
                    t_pRequest->SetBulletName("FeiDanA");
                    t_pRequest->SetBulletOwnerUserName(t_sPlayerID);
                    t_pRequest->SetBulletOriention(t_iOrient);
                    t_pRequest->SetBulletPosition(t_Position);
                    
                    CGProtocolManager::sharedProtocolManager()->PushRequestToSendStack(t_pRequest);
                    
                    AddWeaponToList(t_pBullet);
                }

                
                if( GetMilliSecond() - m_lLastTime > m_iBulletInterval )
                {
                    m_bCanLunch = true;
                }
                
            }
        }
    }
    
}
