//
//  CGRequest.cpp
//  Game
//
//  Created by dongli on 2016/10/30.
//
//

#include "CGRequest.hpp"
#include <iostream>
#include "stdio.h"
#include "stdlib.h"


bool CGRequest::InitGObject()
{
    m_bIsSendOver   = false;
    m_bIsEncryption = false;
    return true;
}

bool CGRequest::CleareGObject()
{
    return true;
}

bool CGRequest::DeleteGObject()
{
    delete this;
    return true;
}

void CGRequest::CreateProtocolPacket()
{
    std::string sBodyLine    = "TYPE:BODY;";
    std::string sBodyName    = "NAME:" + m_sRequestName + ";";
    
    std::string sProtocolStr = sBodyLine + sBodyName;
    
    if( ! m_vProtocol.empty() )
    {
        for( auto i : m_vProtocol )
        {
            if( i.iType == DATE_TYPE_INT )
            {
                int iDate =  i.uDate.iDate;
                
                char sStr[10];
                
                sprintf(sStr, "%d",iDate);
                
                std::string sLine = i.sDateName + ":" + sStr + ";";
                
                sProtocolStr += sLine;
            }
            
            if( i.iType == DATE_TYPE_FLOAT )
            {
                float fDate =  i.uDate.fDate;
                
                char sStr[10];
                
                sprintf(sStr, "%f",fDate);
                
                std::string sLine = i.sDateName + ":" + sStr + ";";
                
                sProtocolStr += sLine;
            }
            
            if( i.iType == DATE_TYPE_LONG )
            {
                long lDate =  i.uDate.lDate;
                
                char sStr[10];
                
                sprintf(sStr, "%ld",lDate);
                
                std::string sLine = i.sDateName + ":" + sStr + ";";
                
                sProtocolStr += sLine;
            }
            
            if( i.iType == DATE_TYPE_DOUBLE )
            {
                double dDate =  i.uDate.dDate;
                
                char sStr[10];
                
                sprintf(sStr, "%lf",dDate);
                
                std::string sLine = i.sDateName + ":" + sStr + ";";
                
                sProtocolStr += sLine;
            }
            
            if( i.iType == DATE_TYPE_STR )
            {
                std::string sDate = i.sDate;
                
                std::string sLine = i.sDateName + ":" + sDate + ";";
                
                sProtocolStr += sLine;
            }
            
        }
        
        m_sPacketString   = sProtocolStr;
        
        char sStr[10];
        
        sprintf(sStr, "%d",(int)m_bIsEncryption);
        
        std::string sEncryption(sStr);
        std::string sHead = "TYPE:HEAD;";
        sHead += "ENCRYPTION:" + sEncryption + ";";
        
        auto iBodySize = m_sPacketString.length();
        
        char sStrSize[10];
        
        sprintf(sStrSize, "%ld",iBodySize);
        
        sHead += "SIZE:";
        sHead += sStrSize;
        sHead += ";";
        
        m_sPacketHeadString = sHead;
        std::cout<<m_sPacketString.size() * 6<<std::endl;;
        std::cout<<m_sPacketHeadString.size() * 6<<std::endl;
        
        CG_DEBUG_PRINT(m_sPacketHeadString);
        CG_DEBUG_PRINT(m_sPacketString);
    }
    
    
}



void CGRequest::PushProtocolDate_Int(const std::string &sName, int iData)
{
    STRUCT_PROTOCOL_PACKET packet;
    
    packet.sDateName    = sName;
    packet.uDate.iDate  = iData;
    packet.iType        = DATE_TYPE_INT;
    
    m_vProtocol.push_back(packet);
}

void CGRequest::PushProtocolDate_Str(const std::string &sName, const std::string sDate)
{
    STRUCT_PROTOCOL_PACKET packet;
    
    packet.sDateName    = sName;
    packet.sDate        = sDate;
    packet.iType        = DATE_TYPE_STR;
    
    m_vProtocol.push_back(packet);

}

void CGRequest::PushProtocolDate_Long(const std::string &sName, long lDate)
{
    STRUCT_PROTOCOL_PACKET packet;
    
    packet.sDateName    = sName;
    packet.uDate.lDate  = lDate;
    packet.iType        = DATE_TYPE_LONG;
    
    m_vProtocol.push_back(packet);

}

void CGRequest::PushProtocolDate_Float(const std::string &sName, int fDate)
{
    STRUCT_PROTOCOL_PACKET packet;
    
    packet.sDateName    = sName;
    packet.uDate.fDate  = fDate;
    packet.iType        = DATE_TYPE_FLOAT;
    
    m_vProtocol.push_back(packet);

}

void CGRequest::PushProtocolDate_Double(const std::string &sName, double dDate)
{
    STRUCT_PROTOCOL_PACKET packet;
    
    packet.sDateName    = sName;
    packet.uDate.dDate  = dDate;
    packet.iType        = DATE_TYPE_DOUBLE;
    
    m_vProtocol.push_back(packet);

}

bool CGRequest_CreateBullet::InitGObject()
{
    m_sRequestName = "Request_CreateBullet";

    return true;
}

bool CGRequest_CreateBullet::CleareGObject()
{
    return true;
}

bool CGRequest_CreateBullet::DeleteGObject()
{
    delete this;
    return true;
}

bool CGRequest_CreateBullet::EncapsulationProtocolPacket()
{
    PushProtocolDate_Str("OWNER", m_sBulletOwnerUserName);
    PushProtocolDate_Str("NAME", m_sBulletName);
    PushProtocolDate_Float("POSITION_X", m_BulletPosition.x);
    PushProtocolDate_Float("POSITION_Y", m_BulletPosition.y);
    PushProtocolDate_Int("ORIENTION", m_iBulletOriention);
    
    CreateProtocolPacket();
    
    
    
    return true;
}





bool CGRequest_ReportPlayerInfo::InitGObject()
{
    m_sRequestName = "Request_ReportPlayerInfo";
    return true;
}

bool CGRequest_ReportPlayerInfo::CleareGObject()
{
    return true;
}

bool CGRequest_ReportPlayerInfo::DeleteGObject()
{
    delete this;
    return true;
}

bool CGRequest_ReportPlayerInfo:: EncapsulationProtocolPacket()
{
    PushProtocolDate_Str("OWNER_NAME", m_sPlayerUserID);
    PushProtocolDate_Str("BUwLLET_NAME", m_sStr1);
    PushProtocolDate_Str("s", m_sStr2);
    PushProtocolDate_Str("BULLsET_NAME", m_sStr3);
    PushProtocolDate_Str("BULLqET_NAME", m_sStr4);
    PushProtocolDate_Str("BUdLLET_NAME", m_sStr5);
    PushProtocolDate_Int("sdasddsd", m_iDate1);
    PushProtocolDate_Int("sdfasdsd", m_iDate2);
    PushProtocolDate_Int("sdasdxsd", m_iDate3);
    PushProtocolDate_Int("sdxasdsd", m_iDate4);
    PushProtocolDate_Int("sdaxsdsd", m_iDate5);
    PushProtocolDate_Int("sdasdxsd", m_iDate6);
    PushProtocolDate_Int("sdaxsdsd", m_iDate7);
    PushProtocolDate_Int("sdaxsdsd", m_iDate8);
    PushProtocolDate_Int("sdxasdsd", m_iDate9);

    CreateProtocolPacket();
    
}




bool CGRequest_Login::EncapsulationProtocolPacket()
{
    std::string t_sProtocolTypeLine  = "PROTOCOL_TYPE:PROTOCOL_BODY;";
    std::string t_sProtocolBodyLine  = "PROTOCOL_NAME:LOGIN;";
    std::string t_sProtocolBodyLine1 = "USER_NAME:" + m_sUserName + ";";
    std::string t_sProtocolBodyLine2 = "PASS_WORD:" + m_sPassWord + ";";
    
    std::string t_sPacket = t_sProtocolTypeLine +
    t_sProtocolBodyLine +
    t_sProtocolBodyLine1 +
    t_sProtocolBodyLine2;
    
    std::cout<<t_sPacket<<std::endl;
    
    auto t_iProtocolSize = t_sPacket.size();
    
    
    char t_sStr1[10];
    char t_sStr2[10];
    int t_iEncytpotion = m_bIsEncryption;
    sprintf(t_sStr2,"%d",t_iEncytpotion);
    sprintf(t_sStr1,"%d",t_iProtocolSize);
    
    std::string t_sSize       = std::string(t_sStr1);
    std::string t_sEncryption = t_sStr2;
    std::string t_sHeadLine1  = "PROTOCOL_TYPE:PROTOCOL_HEAD;";
    std::string t_sHeadLine   = "PROTOCOL_ENCYRPTION:" + t_sEncryption + ";";
    std::string t_sHeadLine2  = "PROTOCOL_NAME:REQUEST_LOGIN;";
    std::string t_sHeadLine3  = "PROTOCOL_SIZE:" + t_sSize + ";";
    
    std::string t_sHead = t_sHeadLine1 +
    t_sHeadLine +
    t_sHeadLine2 +
    t_sHeadLine3;
    
    m_sPacketHeadString = t_sHead;
    
    std::cout<<m_sPacketHeadString<<std::endl;
    
    if(m_bIsEncryption == true)
    {
        
    }
    else
    {
        m_sPacketString = t_sPacket;
    }
    
    
    
    return true;
    
}

