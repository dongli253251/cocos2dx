//
//  CGMonsterAI.hpp
//  Game
//
//  Created by dongli on 2016/12/15.
//
//

#ifndef CGMonsterAI_hpp
#define CGMonsterAI_hpp

#include <iostream>
#include <CGDataType.h>
#include <CGComObject.hpp>

class CGMonsterBase;
class CG_CLASS CGMonsterAI:public CGComObject
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGMonsterAI)
    
    CG_CONSTRUCTION_COPY(CGMonsterAI)
public:
    CG_DESTROY_DEFAULT(CGMonsterAI)
    
    CG_OVERLOAD_COM;
    
    virtual CG_RESULT_VOID SetDirveObject(CGMonsterBase * pMonster)
    {
        m_pMonster = pMonster;
    }
    
    virtual CG_RESULT_VOID ProcessAITask()
    {
        
    }
    
protected:
    CGMonsterBase * m_pMonster;
}
;
#endif /* CGMonsterAI_hpp */
