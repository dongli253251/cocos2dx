//
//  CGException.hpp
//  Game
//
//  Created by dongli on 2016/11/11.
//
//

#ifndef CGException_hpp
#define CGException_hpp

#include <stdio.h>
#include <iostream>
#include "CGDataType.h"

class CG_CLASS CGException
{
public:
    CGException(const std::string& p_sString)
    {
        m_pExcString = p_sString;
    }
    void PrintError()
    {
        std::cout<<m_pExcString<<std::endl;
    }
protected:
    std::string       m_pExcString;
    
}
;


#endif /* CGException_hpp */
