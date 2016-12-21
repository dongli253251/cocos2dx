//
//  CGInstanceIOS.hpp
//  Game
//
//  Created by dongli on 2016/10/26.
//
//

#ifndef CGInstanceIOS_hpp
#define CGInstanceIOS_hpp

#include <stdio.h>
#include "CGInstanceBase.hpp"
#include <iostream>



class CGInstanceIOS:public CGInstanceBase
{
protected:
    CGInstanceIOS()
    {
        std::cout<<"CGInstanceIOS Is Create"<<std::endl;
    }
    CGInstanceIOS(const CGInstanceIOS & rhs)
    {
        std::cout<<"CGInstanceIOS Is Create"<<std::endl;
    }
public:
    virtual ~CGInstanceIOS()
    {
        std::cout<<"CGInstance Is Destroy"<<std::endl;
    }
public:
    
    static CGInstanceIOS * sharedInstanceIOS();
    /*
     * This Static Method Create Or Return an Singleton Object Pointer;
     */
    
    virtual bool InitGameInstance();
    /*
     *
     */
    
    virtual bool InitGameSetting();
    /*
     *
     */
    
    virtual void SetGameStateValue(int iValue)
    {
        m_iGameStateValue = iValue;
    }
    /*
     *
     */
    
    virtual int GetGameStateValue()const
    {
        return m_iGameStateValue;
    }
    /*
     *
     */
    
    virtual bool StartRunGame();
    /*
     * Start Game Logic;
     */
    
    virtual bool DeleteGameInstance();
    
};

#endif /* CGInstanceIOS_hpp */
