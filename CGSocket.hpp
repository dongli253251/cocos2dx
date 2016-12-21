//
//  CGSocket.hpp
//  Game
//
//  Created by dongli on 2016/10/26.
//
//

#ifndef CGSocket_hpp
#define CGSocket_hpp

/**************************************************************
 * - 2016.11.15
 * - www.dongli.com
 * -
 * - Represent a Socket Object.
 * -
 * - just you know.
 * -
 **************************************************************/

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "CGDataType.h"

class CG_CLASS CGSocket
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGSocket)
    /*
     * Disable Default Construction Function.
     */
    
    CGSocket(UINT iFamily, UINT iType, UINT iPro)
    {
        m_iSocketFamliy = iFamily;
        m_iSocketType   = iType;
        m_iSocketPro    = iPro;
        CG_DEBUG_PRINT("CGSocket Is Create.")
    }
    
    CG_CONSTRUCTION_COPY(CGSocket)
    
public:
    virtual ~CGSocket()
    {
        
    }
    //CG_DESTROY_DEFAULT(CGSocket)
    /*
     *- Disable Default Destruction Function.
     */
    
    static CGSocket * CreateGSoscket(int iFamliy, int iType, int iPro);
    /*
     *- Create a Socket Object By 3 Parameter
     **
     *@ iFamliy: Internet Famliy
     *@ iType: Socket Type,TCP or UDP
     *@ iType: Protocol Type.
     **
     */
    
    static CGSocket * CreateGSocket(int iType);
    /*
     *- Create a Socket Object by 1 parameter.
     **
     *@ iType:TCP or UDP.
     **
     */
    
    static CGSocket * CreateGSocket();
    /*
     ** Create Default Socket Object.
     */
    
    inline CG_RESULT_BOOL CreateSocket();
    /*
     ** Create Socket Descritpor.
     */
    
    inline CG_RESULT_BOOL BindSocketByOnlyPort(int iPort);
    /*
     *- Bind Socket Descriptor to Port. 
     *- Use Default Parameter.
     **
     *@ iPort: Port.
     **
     */
    
    inline CG_RESULT_BOOL BindSocket(const std::string& sIP, int iPort);
    /*
     *- Bind Socket Descriptor by specify ID and Port.
     *
     */
    
    inline CG_RESULT_BOOL ListenSocket(int iSequnce);
    /*
     *- Listen Socket.
     */
    
    CG_RESULT_INT SendSocketDate(const std::string& sDataBuffer);
    /*
     *- Send Date Buffer by string object.
     */
    
    CG_RESULT_INT SendSocketDate(const char * pBuffer);
    /*
     *- Send Date Buffer by a char pointer.
     */
    
    CG_RESULT_STR_CREF RecvSocketData();
    /*
     *- Recv Buffer And Return String Object.
     */
    
    
    inline CG_RESULT_BOOL ConnectSocket(const std::string& sConnectIP, int iPort);
    /*
     ** Connect Target IP
     */
    
    CGSocket * AcceptSocket();
    /*
     *- Wait Connection.
     */
    
    bool SetLocalSocketaddr(const sockaddr_in& pSocketaddr)
    {
        m_LocalSockaddr = pSocketaddr;
        return true;
    }
    
    
    bool SetLocalSocketIP(const std::string& sIP)
    {
        m_sLocalIP                      = sIP;
        m_LocalSockaddr.sin_addr.s_addr = inet_addr(sIP.c_str());
        return true;
    }
    /**
     *-
     */
    
    bool SetLocalSocketIPByin_addr_t(in_addr_t iIP)
    {
        m_LocalSockaddr.sin_addr.s_addr = iIP;
        return true;
    }
    /*
     *
     */
    const std::string& GetLocalSocketIP()const
    {
        return m_sLocalIP;
    }
    /*
     *
     */
    
    in_addr_t GetLocalSocketIPByin_addr_t()const
    {
        return m_LocalSockaddr.sin_addr.s_addr;
    }
    /*
     *
     */
    
    bool SetLocalSocketPort(int iPort)
    {
        m_iSocketLocalPort       = iPort;
        m_LocalSockaddr.sin_port = htons(iPort);
        return true;
    }
    /*
     *
     */
    
    int GetLocalSocketPort()const
    {
        return m_iSocketLocalPort;
    }
    /*
     *
     */
    
    in_port_t GetLocalSocketPortByin_port_t()const
    {
        return m_LocalSockaddr.sin_port;
    }
    /*
     *
     */
    bool SetLocalSocketFamliy(int iFamliy)
    {
        m_iSocketFamliy            = iFamliy;
        m_LocalSockaddr.sin_family = iFamliy;
        return true;
    }
    /*
     *
     */
    
    int GetLocalSocketFamliy()const
    {
        return m_iSocketFamliy;
    }
    /*
     *
     */
    
    bool SetLocalSocket(int iSocket)
    {
        m_iSocket = iSocket;
        return true;
    }
    /*
     *
     */
    
    int GetLocalSocket()const
    {
        return m_iSocket;
    }
    /*
     *
     */
    
   
    
    bool CloseSocket()
    {
        if(close(m_iSocket) != -1)
        {
            std::cout<<"Close Is Success"<<std::endl;
            return true;
        
        }
        else
        {
            return false;
        }
    };
    
protected:
    int                 m_iSocket;
    int                 m_iSequnce;
    int                 m_iSocketPro;
    int                 m_iSocketType;
    int                 m_iSocketLocalPort;
    int                 m_iSocketTargetPort;
    int                 m_iSocketFamliy;
    std::string         m_sRecvBufferString;
    std::string         m_sLocalIP;
    std::string         m_sTargetIP;
    sockaddr_in         m_LocalSockaddr;
    sockaddr_in         m_TargetSockaddr;
};

#endif /* CGSocket_hpp */
