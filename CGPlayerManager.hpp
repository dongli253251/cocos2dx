//
//  CGPlayerManager.hpp
//  Game
//
//  Created by dongli on 2016/11/21.
//
//

#ifndef CGPlayerManager_hpp
#define CGPlayerManager_hpp

#include <stdio.h>
#include <iostream>
#include "CGComObject.hpp"
#include "CGDataType.h"

class CGPlayer;
class CG_CLASS CGPlayerManager:public CGComObject
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGPlayerManager)
    
    CG_CONSTRUCTION_COPY(CGPlayerManager)
    
public:
    
    CG_DESTROY_DEFAULT(CGPlayerManager)
    
    CG_SINGLETON_CREATE(PlayerManager);
    
    CG_OVERLOAD_COM;
    
    CG_RESULT_VOID AddNetPlayerToList(CGPlayer * pPlayer);
    
    CG_RESULT_VOID DeleteNetPlayer(CGPlayer * pPlayer);
    
    CG_RESULT_VOID DeleteNetPlayerAll();
    
    CG_RESULT_VOID AddLocalPlayerToList(CGPlayer* pPlayer);
    
    CG_RESULT_VOID DeleteLocalPlayer(CGPlayer * pPlayer);
    
    CG_RESULT_VOID DeleteLocalPlayerAll();
    
    CG_RESULT_VOID ProcessPlayerTask();
    
    CGPlayer * GetLocalPlayer();
    
protected:
    
    std::vector<CGPlayer *>          m_vNetPlayerList;
    
    std::vector<CGPlayer *>          m_vLocalPlayerList;
    
};
#endif /* CGPlayerManager_hpp */
