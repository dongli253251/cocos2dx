//
//  CGInstanceBase.hpp
//  Game
//
//  Created by dongli on 2016/10/26.
//
//

#ifndef CGInstanceBase_hpp
#define CGInstanceBase_hpp



#include "CGDataType.h"
#include <iostream>

/**************************************************************
 *
 * - this virtual abstract class provide a abstract interface to 
 * - runing on different platform.
 * - this class must be pure virtual class.
 * - this class cannot alone instantiation and that must 
 * - instantiation in subclass and make use of static createmethod.
 * - this class is an top class
 *
 **************************************************************/


class CG_CLASS CGInstanceBase
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGInstanceBase)
    /*
     * disable default construction function
     */
    CG_CONSTRUCTION_COPY(CGInstanceBase)
    /*
     * disable default copy construction function
     */
    
public:
    
    virtual ~CGInstanceBase()
    {
        
    }
    
    //CG_DESTROY_DEFAULT(CGInstanceBase)
    /*
     * default polymorphism destroy function.
     */
    
public:
    
    
    inline virtual CG_RESULT_BOOL InitGameInstance()
    {
        return true;
    }
    /*
     * initialization method.
     */
    inline virtual CG_RESULT_BOOL InitGameSetting()
    {
    
    }
    /*
     * initialization method.
     * if initialization success return true, else return false;
     */
    
    inline virtual CG_RESULT_VOID SetGameStateValue(int iValue)
    {
        m_iGameStateValue = iValue;
    }
    /*
     * set game state value on runing
     */
    
    inline virtual CG_RESULT_INT GetGameStateValue()const
    {
        return m_iGameStateValue;
    }
    /*
     * get game state value on runing
     */
    
    inline virtual CG_RESULT_BOOL DeleteGameInstance()
    {
        return true;
    }
    /*
     * cleare instance
     */
    
    inline virtual CG_RESULT_BOOL StartRunGame()
    {
        return true;
    }
    /*
     * start run game logic
     */
    
    
protected:
    UINT     m_iGameStateValue;
};
#endif /* CGInstanceBase_hpp */
