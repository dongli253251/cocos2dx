//
//  CGProtocolManager.hpp
//  Game
//
//  Created by dongli on 2016/10/28.
//
//

#ifndef CGProtocolManager_hpp
#define CGProtocolManager_hpp

#include <stdio.h>
#include <iostream>
#include "CGComObject.hpp"
#include "CGSocket.hpp"
#include "CGRequest.hpp"



class CGProtocolManager:public CGComObject
{
protected:
    CGProtocolManager()
    {
        std::cout<<"CGProtocolManager Is Create"<<std::endl;
    }
    CGProtocolManager(const CGProtocolManager& rhs)
    {
        std::cout<<"CGProtocolManager Is Create"<<std::endl;
    }
public:
    virtual ~CGProtocolManager()
    {
        std::cout<<"CGProtocolManager Is Destroy"<<std::endl;
        CleareGObject();
    }

    static CGProtocolManager * sharedProtocolManager();
    /**
     *
     */
    virtual bool InitGObject();
    /**
     *
     */

    virtual bool CleareGObject();
    /**
     *
     */
    
    virtual bool DeleteGObject();
    
    

    bool RecvProtocolPacket();
    /**
     *
     */

    bool PushRequestToSendStack(CGRequest * pRequst);
    /**
     *
     */
    void SendProtocolThread();
    /**
     *
     */

    
    void RecvProtocolThread();
    /**
     *
     */

    
    bool ProcessProtocolPakcet();
    /**
     *
     */

protected:
    std::vector<CGRequest *>        m_vSendRequestVec;
    std::vector<CGRequest *>        m_vRecvRequestVec;
    CGSocket *                      m_pSocket;
    
    
};


#endif /* CGProtocolManager_hpp */
