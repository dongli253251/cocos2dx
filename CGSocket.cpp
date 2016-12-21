//
//  CGSocket.cpp
//  Game
//
//  Created by dongli on 2016/10/26.
//
//

#include "CGSocket.hpp"
#include "CGDataType.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>


CGSocket * CGSocket::CreateGSocket()
{
    CGSocket * t_pSocket = new CGSocket();
    
    if(t_pSocket != NULL)
    {
        return t_pSocket;
    }
    else
    {
        return NULL;
    }
}

CGSocket * CGSocket::CreateGSocket(int iType)
{
    if(iType == SOCKET_TYPE_TCP)
    {
        CGSocket * t_pGSocket = new CGSocket(AF_INET, SOCK_STREAM, 0);
        
        if(t_pGSocket != NULL)
        {
            
            t_pGSocket->CreateSocket();
            return t_pGSocket;
        }
        else
        {
            std::cout<<"Socket Create Error"<<std::endl;
            return NULL;
        }
    }
    else if(iType == SOCKET_TYPE_UDP)
    {
        CGSocket * t_pGSocket = new CGSocket(AF_INET, SOCK_DGRAM, 0);
        
        if(t_pGSocket != NULL)
        {
            t_pGSocket->CreateSocket();
            return t_pGSocket;
        }
        else
        {
            std::cout<<"Socket Create Error"<<std::endl;
            return NULL;
        }
    }
    else
    {
        std::cout<<"CreateGSocket Is Error"<<std::endl;
        return NULL;
    }
}

CGSocket * CGSocket::CreateGSoscket(int iFamliy, int iType, int iPro)
{
    CGSocket * t_pGSocket = new CGSocket(iFamliy, iType, iPro);
    if(t_pGSocket != NULL)
    {
        t_pGSocket->CreateSocket();
        return t_pGSocket;
    }
    else
    {
        std::cout<<"Socket Create Error"<<std::endl;
        return NULL;
    }

}

bool CGSocket::CreateSocket()
{
    
    int t_iResult = socket(m_iSocketFamliy, m_iSocketType, m_iSocketPro);
    
    if(t_iResult == -1)
    {
        std::cout<<"Socket calling Error "<<std::endl;
        return false;
    }
    else
    {
        std::cout<<"Socket calling Success"<<std::endl;
        m_iSocket = t_iResult;
    }
    return true;
}

bool CGSocket::BindSocket(const std::string &sIP, int iPort)
{
    m_iSocketLocalPort              = iPort;
    m_sLocalIP                      = sIP;
    m_LocalSockaddr.sin_port        = htons(iPort);
    m_LocalSockaddr.sin_family      = m_iSocketFamliy;
    m_LocalSockaddr.sin_addr.s_addr = inet_addr(sIP.c_str());
    
    std::cout<<"Bind IP: "<<m_sLocalIP<<std::endl;
    std::cout<<"Bind Port: "<<m_iSocketLocalPort<<std::endl;
    
    if(bind(m_iSocket,(sockaddr *)&m_LocalSockaddr, sizeof m_LocalSockaddr))
    {
        std::cout<<"Bind Is Success"<<std::endl;
        return true;
    }
    else
    {
        std::cout<<"Bind Is Error"<<std::endl;
        return false;
    }
}

bool CGSocket::BindSocketByOnlyPort(int iPort)
{
    m_iSocketLocalPort = iPort;
    m_LocalSockaddr.sin_addr.s_addr = INADDR_ANY;
    m_LocalSockaddr.sin_port        = htons(iPort);
    m_LocalSockaddr.sin_family      = AF_INET;
    m_sLocalIP                      = std::string("127.0.0.1");
    std::cout<<"Bind IP: "<<m_sLocalIP<<std::endl;
    std::cout<<"Bind Port: "<<m_iSocketLocalPort<<std::endl;
    
    int iRes = bind(m_iSocket, (sockaddr *)&m_LocalSockaddr, sizeof m_LocalSockaddr);
    
    if(iRes != -1)
    {
        std::cout<<"Bind Is Success"<<std::endl;
        return true;
    }
    else
    {
        std::cout<<"Bind Is Error"<<std::endl;
        return false;
    }

}

bool CGSocket::ListenSocket(int iSequnce)
{
    m_iSequnce = iSequnce;
    
    if(listen(m_iSocket, iSequnce) == -1)
    {
        std::cout<<"Listen is Error"<<std::endl;
        return false;
    }
    else
    {
        std::cout<<"Listen Is Success"<<std::endl;
        return true;
    }
}

bool CGSocket::ConnectSocket(const std::string &sConnectIP, int iPort)
{
    m_sTargetIP         = sConnectIP;
    m_iSocketTargetPort = iPort;
    
    m_TargetSockaddr.sin_addr.s_addr = inet_addr(sConnectIP.c_str());
    m_TargetSockaddr.sin_port        = htons(iPort);
    m_TargetSockaddr.sin_family      = AF_INET;
    
    if((connect(m_iSocket, (sockaddr *)&m_TargetSockaddr, sizeof m_TargetSockaddr)) != 0)
    {
        std::cout<<"Connect Is Error: "<<errno<<std::endl;
        return false;
    }
    else
    {
        std::cout<<"Connect Is Success"<<std::endl;
        return true;
    }
}

CGSocket * CGSocket::AcceptSocket()
{
    sockaddr_in Client;
    socklen_t iLenght = sizeof Client;
    //bzero(&Client, sizeof Client);
    
    std::cout<<"Accept..."<<std::endl;
    int t_iSocket = accept(m_iSocket, (sockaddr*)&Client, &iLenght);
    
    if(t_iSocket > 0)
    {
        std::cout<<"Accept Is Success: "<<t_iSocket<<std::endl;
        
        CGSocket * t_pClientSocket = CGSocket::CreateGSocket();
        
        t_pClientSocket->SetLocalSocket(t_iSocket);
        t_pClientSocket->SetLocalSocketPort(ntohs(Client.sin_port));
        t_pClientSocket->SetLocalSocketIP(inet_ntoa((Client.sin_addr)));
        t_pClientSocket->SetLocalSocketFamliy(Client.sin_family);
        t_pClientSocket->SetLocalSocketaddr(Client);
        
        return t_pClientSocket;
    }
    else if(t_iSocket == 0)
    {
        std::cout<<"Internet Is Break"<<std::endl;
        return NULL;
    }
    else
    {
        std::cout<<"Accept Is Error : -1"<<std::endl;
        return NULL;
    }
}

int CGSocket::SendSocketDate(const std::string &sDataBuffer)
{
    ssize_t iResult = send(m_iSocket, sDataBuffer.c_str(), sDataBuffer.length(), 0);
    
    if(iResult > 0)
    {
        std::cout<<"Send Success: "<<sDataBuffer.length()<<std::endl;
        return iResult;
    }
    else
    {
        std::cout<<"Send Error: "<<iResult<<std::endl;
        return -1;
    }
}

int CGSocket::SendSocketDate(const char *pBuffer)
{
    ssize_t iResult = send(m_iSocket, pBuffer, sizeof pBuffer, 0);
    
    if(iResult > 0)
    {
        std::cout<<"Send Success: "<<sizeof pBuffer<<std::endl;
        return iResult;
    }
    else
    {
        std::cout<<"Send Error: "<<iResult<<std::endl;
        return -1;
    }
}

const std::string& CGSocket::RecvSocketData()
{
    char Buffer[1024];
    
    ssize_t iResult = recv(m_iSocket, Buffer, sizeof Buffer, 0);
    
    if(iResult < 0)
    {
        std::cout<<"Recv Is Error"<<std::endl;
        return NULL;
    }
    else if(iResult == 0)
    {
        std::cout<<"Recv Is Break"<<std::endl;
        return NULL;
    }
    else
    {
        m_sRecvBufferString = Buffer;
        return m_sRecvBufferString;
    }
    
}


