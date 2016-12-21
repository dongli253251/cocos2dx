//
//  CGAnimateManger.hpp
//  Game
//
//  Created by dongli on 2016/11/1.
//
//

#ifndef CGAnimateManger_hpp
#define CGAnimateManger_hpp

/**************************************************************
 * - 2016.11.15
 * - www.dongli.com
 * -
 * - analysis animation xml file by texturepakcer maked and fill
 * - date struct for animation.
 * - generate cocos2d animation object by animation name.
 * -
 * - singleton class.
 * -
 **************************************************************/


#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "CGComObject.hpp"
#include "CGDataType.h"
using namespace cocos2d;

class CG_CLASS CGAnimateManager:public CGComObject
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGAnimateManager)
    
    /**
     * - disable default construction function.
     */

    /**
     * - disable default copy construction function.
     */

public:
    
    CG_DESTROY_DEFAULT(CGAnimateManager)
    /**
     *- Disable Default Destruction Function.
     */
    
    
    CG_SINGLETON_CREATE(AnimateManager)
    /**
     *- create or get a singleton object .
     */

    CG_OVERLOAD_COM
    
    /**
     *- init game object.
     */
    
    /**
     *- cleare game object.
     */
    
    CG_RESULT_VOID AnalysisXML();
    /**
     *- used by analaysis xml files, that xml file maked by texturepacker
     */

    CG_RESULT_VOID SetXMLFilePath(const std::string& sPaht)
    {
        m_sXMLFilePath = sPaht;
    }
    /**
     *- set animation xml file path.
     */
    
    CG_RESULT_STR_CREF GetXMLFilePath()const
    {
        return m_sXMLFilePath;
    }
    /**
     * - get animation xml file path.
     */
    
    CG_RESULT_STR_CREF GetPlistNameByID(const std::string& sID);
    
    CG_RESULT_STR_CREF GetObjectNameByID(const std::string& sID);
    
    CG_RESULT_VOID EnumXMLFolder();
    /**
     * - enum all file by specify path.
     */
    
    CG_RESULT_VOID EraseNumber(std::string& sString);
    /**
     * erase number in vector.
     */
    
    CG_RESULT_VOID EraseSpeicalChar(std::string& sString, char sChar);
    /**
     * erase speical char.
     */
    
    const std::vector<STRUCT_FLAGS>& GetFlagStructVecByID(const std::string& sID);
    /**
     * - get animation flags vector by animation id.
     */
    
    const STRUCT_ANIMATE& GetAnimateStructByID(const std::string& sID);
    /**
     * get animation struct by animation id.
     */
    
    Animation * GetAnimationByID(const std::string& sID);
    /**
     *- Get Cococs2d Animation Object by Animate ID.
     */
    
    const std::vector<std::string>& GetAnimationNameByObject(const std::string & sObject);
    
protected:
    
    std::string                     m_sXMLFilePath;
    /////////////////////////////   Animate File Path.
    
    std::vector<STRUCT_ANIMATE>     m_vAnimate;
    /////////////////////////////   Animate Struct Vector.
    
    std::vector<std::string>        m_vXMLFileVec;
    /////////////////////////////   Plist File Name Vector
    
    std::vector<std::string>        m_vFileContent;
    /////////////////////////////   File Content String.
    
    std::vector<std::string>        m_vAnimateName;
};


#endif /* CGAnimateManger_hpp */
