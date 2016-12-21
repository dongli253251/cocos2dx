//  CGPlayerDateManager.hpp
//  Game
//
//  Created by dongli on 2016/11/16.
//
//

#ifndef CGPlayerDateManager_hpp
#define CGPlayerDateManager_hpp


/**************************************************************
 * - 2016.11.15
 * - www.dongli.com
 * -
 * - Manage all Player Attribute.
 * - Request Player Attribute by Service,Storge RealTime Player
 * - Date,Storge Local Config Date.
 * - Player Date Include: 
 * - Level,ID,Name,Equnment,Item,Attribute Value.
 * - singleton class.
 * -
 **************************************************************/




#include <CGDataType.h>
#include <stdio.h>
#include <iostream>
#include <CGComObject.hpp>
#include "CGException.hpp"

class CG_CLASS CGPlayerDateManager:public CGComObject
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGPlayerDateManager)
    /**
     *- Disable Default Construction.
     */
    
    CG_CONSTRUCTION_COPY(CGPlayerDateManager)
    /**
     *- Disable Default Copystruciton.
     */
public:
    
    CG_DESTROY_DEFAULT(CGPlayerDateManager)
    /**
     *- Disable Default destruciton.
     */
    
    CG_SINGLETON_CREATE(PlayerDateManager)
    /**
     *-Create or shared a Object.
     */
    
    CG_OVERLOAD_COM
    /**
     *-over load init cleare delete.
     */
    
    CG_RESULT_VOID ProcessDate();
    /**
     *- Process All Date by every Fream.
     */

    CG_ACCESS_INT(PlayerLife);
    /**
     *- Get And Set m_iPlayerLife.
     */
    
    CG_ACCESS_INT(PlayerDefense);
    /**
     *- Get And Set m_iPlayerDefense.
     */

    CG_ACCESS_INT(PlayerRank);
    /**
     *- Get And Set m_iPlayerRank.
     */
    
    CG_ACCESS_INT(PlayerAttack);
    /**
     *- Get And Set m_iPlayerAttack.
     */

    CG_ACCESS_INT(PlayerMaxLife)
    
    CG_ACCESS_INT(PlayerMaxArmor)
    
    CG_ACCESS_INT(PlayerArmor)
    
    CG_ACCESS_INT(PlayerTemp)
    
    CG_ACCESS_INT(PlayerMaxTemp)
    
    CG_ACCESS_INT(PlayerEnergy);
    /**
     *- Get And Set m_iPlayerEnergy.
     */

    CG_ACCESS_INT(PlayerBulletSpeed);
    
    
    CG_ACCESS_STR(PlayerID);
    /**
     *- Get And Set m_iPlayerID.
     */

    CG_ACCESS_STR(PlayerName);
    /**
     *- Get And Set m_iPlayerName.
     */
    
    CG_ACCESS_INT(PlayerBulletInterval)
    
    CG_ACCESS_STR(BulletName);
    
    CG_ACCESS_INT(PlayerObliqueForceX)
    
    CG_ACCESS_INT(PlayerObliqueForceY)

    CG_ACCESS_INT(PlayerHorizontalForceX)
    
    CG_ACCESS_INT(PlayerHorizontalForceY)
    
    CG_ACCESS_INT(PlayerVerticalForceX)
    
    CG_ACCESS_INT(PlayerVerticalForceY)
    
    CG_ACCESS_INT(PlayerBuoyancy);
    
    CG_ACCESS_INT(PlayerObliqueDownForceX)
    
    CG_ACCESS_INT(PlayerObliqueDownForceY)

    CG_ACCESS_INT(PlayerHorizontalMaxSpeed)
    
    CG_ACCESS_INT(PlayerVerticalMaxSpeed)
    
    CG_ACCESS_INT(PlayerVerticalDownForce)

    CG_NET_ACCESS_STR(ID);
    /**
     *- Get And Set Net Player ID.
     */

    CG_NET_ACCESS_STR(Name);
    /**
     *- Get And Set Net Player Name.
     */

    CG_NET_ACCESS_INT(Attack)
    /**
     *- Get And Set Net Player Attack.
     */

    CG_NET_ACCESS_INT(Life)
    /**
     *- Get And Set Net Player Life.
     */

    CG_NET_ACCESS_INT(Defense)
    /**
     *- Get And Set Net Player Defense.
     */

    CG_NET_ACCESS_INT(Energy)
    /**
     *- Get And Set Net Player ENergy.
     */

    CG_NET_ACCESS_INT(Rank)
    /**
     *- Get And Set Net Player Rank.
     */

    CG_NET_ACCESS_INT(Item)
    /**
     *- Get And Set Net Player Item.
     */

    void ReducePlayerTemp(int iValue)
    {
        m_iPlayerTemp -= iValue;
        
        if( m_iPlayerTemp < 0 )
        {
            m_iPlayerTemp = 0;
        }
    }
    
    void ReducePlayerLife(int iValue)
    {
        m_iPlayerLife -= iValue;
        
        if( m_iPlayerLife < 0 )
        {
            m_iPlayerLife = 0;
        }
    }
    
    void ReducePlayerArmor(int iValue)
    {
        m_iPlayerArmor -= iValue;
        
        if( m_iPlayerArmor < 0 )
        {
            m_iPlayerArmor = 0;
        }
    }
    
    void AddPlayerTemp(int iValue)
    {
        m_iPlayerTemp += iValue;
        
        if( m_iPlayerTemp > m_iPlayerMaxTemp )
        {
            m_iPlayerTemp = m_iPlayerMaxTemp;
        }
    }
    
    void AddPlayerArmor(int iValue)
    {
        m_iPlayerArmor += iValue;
        
        if( m_iPlayerArmor > m_iPlayerMaxArmor )
        {
            m_iPlayerArmor = m_iPlayerMaxArmor;
        }
    }
    
    void AddPlayerLife(int iValue)
    {
        m_iPlayerLife += iValue;
        
        if( m_iPlayerLife > m_iPlayerMaxLife )
        {
            m_iPlayerLife = m_iPlayerMaxLife;
        }
    }
    
    CG_ACCESS_INT(PlayerTempAddValue)
    
    CG_ACCESS_INT(PlayerTempReduceValue)
protected:
    
    std::string                         m_sPlayerID;
    //////////////////////////////////  User ID.
    
    std::string                         m_sPlayerName;
    //////////////////////////////////  NickName.
    
    std::string                         m_sBulletName;
    
    int                                 m_iPlayerAttack;
    //////////////////////////////////  Attack value.
    
    int                                 m_iPlayerDefense;
    //////////////////////////////////  DefenseValue.
    
    int                                 m_iPlayerLife;
    //////////////////////////////////  Life Value.

    int                                 m_iPlayerEnergy;
    //////////////////////////////////  Energy Value.

    int                                 m_iPlayerRank;
    //////////////////////////////////  Game Level

    int                                 m_iPlayerArmor;
    
    int                                 m_iPlayerMaxArmor;
    
    int                                 m_iPlayerMaxTemp;
    
    int                                 m_iPlayerMaxLife;
    int                                 m_iPlayerTemp;
    int                                 m_iPlayerTempAddValue;
    int                                 m_iPlayerTempReduceValue;
    
    std::vector<STRUCT_NET_PLAYER>      m_vNetPlayer;
    //////////////////////////////////  Other Player.

    int                                 m_iPlayerHorizontalForceY;
    int                                 m_iPlayerHorizontalForceX;
    int                                 m_iPlayerVerticalForceX;
    int                                 m_iPlayerVerticalForceY;
    int                                 m_iPlayerVerticalDownForce;
    int                                 m_iPlayerObliqueForceX;
    int                                 m_iPlayerObliqueForceY;
    int                                 m_iPlayerObliqueDownForceX;
    int                                 m_iPlayerObliqueDownForceY;
    float                               m_iPlayerHorizontalMaxSpeed;
    float                               m_iPlayerVerticalMaxSpeed;
    int                                 m_iPlayerBuoyancy;
    int                                 m_iPlayerBulletSpeed;
    int                                 m_iPlayerBulletInterval;
    
};

#endif /* CGPlayerDateManager_hpp */
