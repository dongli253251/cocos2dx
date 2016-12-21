//
//  CGObject.hpp
//  Game
//
//  Created by dongli on 2016/10/27.
//
//

#ifndef CGObject_hpp
#define CGObject_hpp

#include <stdio.h>
#include <iostream>
#include "CGDataType.h"

/**************************************************************
 * - 2016.11.15
 * - www.dongli.com
 *
 * - CGObject is Root Class of All CG Class.
 * - this class must be pure virtual class.
 * - this class cannot alone instantiation and that must
 * - instantiation in subclass and make use of static createmethod.
 * - this class is an top class
 *
 **************************************************************/



static UINT g_uObjectOnlyID = 1;

class CG_CLASS CGObject
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGObject)
    /*
     *- disble default construction function.
     */
    
    CG_CONSTRUCTION_COPY(CGObject)
    /*
     *- Disable Default Copy Construction Function.
     */
    
public:
    
    CG_DESTROY_DEFAULT(CGObject)
    /*
     *- disble default destrution function.
     */
    
    virtual CG_RESULT_BOOL InitGObject()
    {
        return true;
    }
    /*
     *- Init Object.
     */

    virtual CG_RESULT_BOOL CleareGObject()
    {
        return true;
    }
    /*
     *- Cleare Object.
     */

    virtual CG_RESULT_BOOL DeleteGObject()
    {
        return true;
    }
    /*
     *- Destroy Object.
     */

    
    
    inline virtual CG_RESULT_UINT GetObjectOnlyID()const
    {
        return m_uObjectOnlyID;
    }
    /*
     *- Get Only Object ID.
     */

    inline CG_RESULT_VOID CreateObjectOnlyID()
    {
        m_uObjectOnlyID = g_uObjectOnlyID++;
    }
    /*
     * Make a Only Object ID by auto count.
     */

protected:
    UINT            m_uObjectOnlyID;
    ///             Identification a CGObject
    
};
#endif /* CGObject_hpp */
