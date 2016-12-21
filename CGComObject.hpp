//
//  CGComObject.hpp
//  Game
//
//  Created by dongli on 2016/10/28.
//
//

#ifndef CGComObject_hpp
#define CGComObject_hpp

#include <stdio.h>
#include <iostream>

#include "CGObject.hpp"
#include "CGDataType.h"

/**************************************************************
 * - 2016.11.15
 * - www.dongli.com
 *
 * - Represent a No Rendering Object.
 * - this class must be pure virtual class.
 * - this class cannot alone instantiation and that must
 * - instantiation in subclass and make use of static createmethod.
 *
 **************************************************************/



class CG_CLASS CGComObject:public CGObject
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGComObject)
    /*
     *- disable default construction function.
     *- and copy construction function.
     */
    CG_CONSTRUCTION_COPY(CGComObject)
    
public:
    CG_DESTROY_DEFAULT(CGComObject)
    /*
     *- disable default destruction function.
     */
    
public:
    
    virtual CG_RESULT_BOOL InitGObject();
    
    virtual CG_RESULT_BOOL CleareGObject();
    
    virtual CG_RESULT_BOOL DeleteGObject();
    /*
     *- Init Object.
     *- Cleare Object.
     *- Destroy Object.
     */
    
};


#endif /* CGComObject_hpp */
