//
//  CGMapManager.hpp
//  Game
//
//  Created by dongli on 2016/11/27.
//
//

#ifndef CGMapManager_hpp
#define CGMapManager_hpp

#include <stdio.h>
#include "CGMapScene.hpp"
#include "CGDataType.h"
#include <iostream>
#include "CGComObject.hpp"
#include "CGException.hpp"
class CGMapScene;
class CG_CLASS CGMapManager:public CGComObject
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGMapManager)
    
    CG_CONSTRUCTION_COPY(CGMapManager)
public:
    CG_DESTROY_DEFAULT(CGMapManager)
    
    CG_OVERLOAD_COM;
    
    CG_SINGLETON_CREATE(MapManager)
    
    CGMapScene * GetMapScene()
    {
        if( ! m_vMapList.empty() )
        {
            return m_vMapList[0];
        }
        else
        {
            throw CGException("GetMapScene Is Empty");
            return nullptr;
        }
    }
    
    CG_RESULT_VOID ProcessMapScene();
    
    CG_RESULT_VOID AddMapSceneToList(CGMapScene * pMap);
    
    CG_RESULT_POINT_CREF GetFarRectZeroPoint(int iID);
    
protected:
    std::vector<CGMapScene *>       m_vMapList;
};
#endif /* CGMapManager_hpp */
