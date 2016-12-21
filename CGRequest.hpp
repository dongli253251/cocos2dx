//
//  CGRequest.hpp
//  Game
//
//  Created by dongli on 2016/10/30.
//
//

#ifndef CGRequest_hpp
#define CGRequest_hpp

#include <stdio.h>
#include <iostream>
#include "CGDataType.h"
#include "CGComObject.hpp"
#include "CGException.hpp"
#include <cocos2d.h>

using namespace cocos2d;

class  CG_CLASS CGRequest:public CGComObject
/*
 * - provide an abstract interface for all request
 */
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGRequest)
    
    CG_CONSTRUCTION_COPY(CGRequest)
    
public:
    
    CG_DESTROY_DEFAULT(CGRequest)
    
    CG_OVERLOAD_COM;
    
    virtual CG_RESULT_BOOL EncapsulationProtocolPacket()
    {
        return true;
    };
    /*
     * make a protocol packet
     */
    
    virtual CG_RESULT_STR_CREF GetProtocolPakcetString()
    {
        return m_sPacketString;
    };
    
    virtual CG_RESULT_STR_CREF GetProtocolPacketHeadString()
    {
        return m_sPacketHeadString;
    };
    
    
    CG_RESULT_BOOL GetSendOver()const
    {
        return m_bIsSendOver;
    }
    
    CG_RESULT_VOID SetSendOver(bool bSend)
    {
        m_bIsSendOver = bSend;
    }
    
    CG_RESULT_VOID PushProtocolDate_Int(const std::string& sName,int iData);
    
    CG_RESULT_VOID PushProtocolDate_Str(const std::string& sName,const std::string sDate);
    
    CG_RESULT_VOID PushProtocolDate_Float(const std::string& sName,int fDate);
    
    CG_RESULT_VOID PushProtocolDate_Long(const std::string& sName,long lDate);
    
    CG_RESULT_VOID PushProtocolDate_Double(const std::string& sName,double dDate);
    
    CG_RESULT_VOID CreateProtocolPacket();
    
    CG_RESULT_VOID SetRequestName(const std::string& sName)
    {
        m_sRequestName = sName;
    }
    
protected:
    bool                                    m_bIsEncryption;
    bool                                    m_bIsSendOver;
    
    std::vector<STRUCT_PROTOCOL_PACKET>     m_vProtocol;
    std::string                             m_sRequestName;
    std::string                             m_sPacketString;
    std::string                             m_sPacketHeadString;
};

class CG_CLASS CGRequest_Login:public CGRequest
/*
 * - Login in service
 */
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGRequest_Login)
    
    CG_CONSTRUCTION_COPY(CGRequest_Login)
    
public:
    
    CG_DESTROY_DEFAULT(CGRequest_Login);
    
    CG_OVERLOAD_COM;
    
    
    CG_OBJECT_CREATE(Request_Login);
    
    bool EncapsulationProtocolPacket();
    /*
     * - make a protocol packet by specify parameter.
     * - return true if success, else return false.
     */
    
    
    void SetUserName(const std::string& sUser)
    {
        m_sUserName = sUser;
    }
    /*
     * - set user name.
     */
    void SetPassWord(const std::string& sPassWord)
    {
        m_sPassWord = sPassWord;
    }
    /*
     * - set pass word.
     */

    void SetIsEncryption(bool bIs)
    {
        m_bIsEncryption = bIs;
    }
    /*
     * - set is encryption packet.
     */
    bool GetIsEncryption()const
    {
        return m_bIsEncryption;
    }
    /*
     * - get encryption state.
     */
    const std::string& GetPassWord()const
    {
        return m_sPassWord;
    }
    /*
     * - get pass word.
     */
    const std::string& GetUserName()const
    {
        return m_sUserName;
    }
    /*
     * - get user name.
     */
protected:
    std::string         m_sUserName;
    std::string         m_sPassWord;
};
class CGRequest_GetPlayerInfo:public CGRequest
{};
/*
 * - get player infomation include player's position,
 * - gaming state,dead or live ...
 */

class CGRequest_GetRoomInfo;
/*
 * - get game room's infomation,include player count,
 * - player ID,player state...
 */
class CGRequest_GetAllPlayerInfo;
/*
 * - get all player infomation
 */
class CGRequest_GetGameInfo;
/*
 * - get game state,include timer,win or lose,and item's infomation,
 * - scene's infomation
 */

class CG_CLASS CGRequest_ReportPlayerInfo:public CGRequest
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGRequest_ReportPlayerInfo);
    
    CG_CONSTRUCTION_COPY(CGRequest_ReportPlayerInfo);
    
public:
    CG_DESTROY_DEFAULT(CGRequest_ReportPlayerInfo);
    
    CG_OBJECT_CREATE(Request_ReportPlayerInfo);
    
    CG_OVERLOAD_COM
    
    CG_ACCESS_STR(PlayerUserID);
    
    CG_ACCESS_STR(Str5);
    
    CG_ACCESS_STR(Str1)
    
    CG_ACCESS_STR(Str2)
    CG_ACCESS_STR(Str3)
    CG_ACCESS_STR(Str4)
    
    CG_ACCESS_INT(Date1)
    CG_ACCESS_INT(Date2)
    CG_ACCESS_INT(Date3)
    CG_ACCESS_INT(Date4)
    CG_ACCESS_INT(Date5)
    CG_ACCESS_INT(Date6)
    CG_ACCESS_INT(Date8)
    CG_ACCESS_INT(Date7)

    CG_ACCESS_INT(Date9)
    CG_ACCESS_INT(Date10)

    CG_ACCESS_INT(PlayerAnimateState)
    CG_ACCESS_INT(CurrentItemID)
    CG_ACCESS_INT(IsDead)
    CG_ACCESS_INT(Rank)
    CG_ACCESS_INT(Buff)

bool EncapsulationProtocolPacket();
    
protected:
    std::string             m_sPlayerUserID;
    Point                   m_PlayerPosition;
    int                     m_iPlayerAnimateState;
    int                     m_iCurrentItemID;
    int                     m_iEvnetState;
    int                     m_iIsDead;
    int                     m_iRank;
    int                     m_iBuff;
    int                     m_iDate1;
    int                     m_iDate2;
    int                     m_iDate3;
    int                     m_iDate4;
    int                     m_iDate5;
    int                     m_iDate6;
    int                     m_iDate7;
    int                     m_iDate8;
    int                     m_iDate9;
    int                     m_iDate10;
    std::string             m_sStr1;
    std::string             m_sStr2;
    std::string             m_sStr3;
    std::string             m_sStr4;
    std::string             m_sStr5;


    
};


class CG_CLASS CGRequest_CreateBullet:public CGRequest
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGRequest_CreateBullet)
    
    CG_CONSTRUCTION_COPY(CGRequest_CreateBullet)
    
public:
    
    CG_DESTROY_DEFAULT(CGRequest_CreateBullet);
    
    CG_OVERLOAD_COM;
    
    CG_OBJECT_CREATE(Request_CreateBullet);

    CG_ACCESS_INT(BulletOriention);
    
    CG_ACCESS_STR(BulletOwnerUserName)
    
    CG_ACCESS_STR(BulletName)
    
    const Point& GetBulletPosition()const
    {
        return m_BulletPosition;
    }
    
    void SetBulletPosition(const Point& Position)
    {
        m_BulletPosition = Position;
    }
    
    virtual CG_RESULT_BOOL EncapsulationProtocolPacket();
    
protected:
    std::string             m_sBulletOwnerUserName;
    std::string             m_sBulletName;
    Point                   m_BulletPosition;
    int                     m_iBulletOriention;
    
};

#endif /* CGRequest_hpp */
