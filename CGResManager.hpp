//
//  CGResManager.hpp
//  Game
//
//  Created by dongli on 2016/11/1.
//
//

#ifndef CGResManager_hpp
#define CGResManager_hpp



/**************************************************************
 * - 2016.11.15
 * - www.dongli.com
 * -
 * - This Manager is Manage All Resrouce: Plist and Png File.
 * - Load Specify Res File.
 * - UnLoad Specify Res File.
 * - Manage Textrue descriptor Infomation.
 * -
 * - singleton class.
 * -
 **************************************************************/



#include <stdio.h>
#include <iostream>
#include "CGComObject.hpp"
#include "CGDataType.h"
#include "CGException.hpp"

class CG_CLASS CGResManager:public CGComObject
{
protected:
    
    CG_CONSTRUCTION_DEFAULT(CGResManager)
    
    CG_CONSTRUCTION_COPY(CGResManager)
    
public:
    
    CG_DESTROY_DEFAULT(CGResManager)
    /**
     *- Destroy function.
     */
    CG_SINGLETON_CREATE(ResManager)
    /**
     *- Create Or Shared Singleton Object.
     */
    
    CG_OVERLOAD_COM
    /**
     *- Init and Cleare and Delete.
     */
    
    typedef struct tagUITextureStruct
    {
        std::string     sUIString;
        int             iUIID;
    }STRUCT_UI_TEXTURE;
    
    /*
     *- Get UI Texture flie Name by Specify ID.
     **
     *@sUIString: UI Texture file Name .png
     *@iUIID:     UI int ID,Like BUTTON_POWER_NORMAL
     **
     */
    
    typedef struct tagUISizeStruct
    {
        int             iUIName;
        int             iUISize;
    }STRUCT_UI_SIZE;
    /**
     *- Get UI Texture Size by ID
     */

    inline CG_RESULT_STR_CREF GetAnimationPath()const
    {
        return m_sAnimationRes;
    }
    /**
     *- Get Animation File Path.
     */

    inline CG_RESULT_VOID SetAnimationPath(const std::string& sPath)
    {
        m_sAnimationRes = sPath;
    }
    /**
     *- Set Animation File Path.
     */

    inline CG_RESULT_STR_CREF GetUIResPath()const
    {
        return m_sUIRes;
    }
    /**
     *- Get UI File Path.
     */

    inline CG_RESULT_VOID SetUIResPath(const std::string& sUIPath)
    {
        m_sUIRes = sUIPath;
    }
    /**
     *- Set UI File Path.
     */

    CG_RESULT_VOID LoadSpeciaPlistByName(const std::string & sName);
    /**
     *- Load Plist File By String. String dont Include Res Path.
     */

    CG_RESULT_VOID AutoLoadAnimationPath();
    /**
     *- Auto enum and load Plist file in Res Path.
     */

    CG_RESULT_INT GetUISizeByName(int iUIName);
    /**
     *- Get UI Size By int ID.
     */

    CG_RESULT_VOID LoadAnimationRes();
    /**
     *- Load Plist File All.
     */
    
    CG_RESULT_STR_CREF GetUITextureString(int iUIID);
    /**
     *- Get UI Texture Flie Name by ID.
     */

    CG_ACCESS_PHYSICS_INT(Width)
    
    CG_ACCESS_PHYSICS_INT(Height)
    
    CG_ACCESS_PHYSICS_INT(Friction)
    
    CG_ACCESS_PHYSICS_INT(Density)
    
    CG_RESULT_VOID AnalysisString();
    
    CG_RESULT_VOID AddNewShipPhysics(const std::string& sID);
    
    CG_RESULT_VOID LoadPhysicsFromFile();
    
    CG_RESULT_VOID SetPhysicsFileName(const std::string& sName)
    {
        m_sPhysicsFile = sName;
    }
    
    CG_RESULT_VOID SetPhysicsPath(const std::string& sPath)
    {
        m_sPhysicsPath = sPath;
    }
    
    CG_RESULT_STR_CREF GetPhysicsPath()const
    {
        return m_sPhysicsPath;
    }
    
    CG_RESULT_STR_CREF GetPhysicsFile()const
    {
        return m_sPhysicsFile;
    }
    
    CG_RESULT_INT GetTextureHeightByName(const std::string& sName);
    
    CG_RESULT_INT GetTextureWidthByName(const std::string& sName);
    
    CG_RESULT_INT GetMapHeightByName(const std::string& sName);
    
    CG_RESULT_INT GetMapWidthByName(const std::string& sName);
    
    CG_RESULT_INT GetMapFarScaleByName(const std::string& sName);
    
    CG_RESULT_INT GetMapNearScaleByName(const std::string& sName);

    CG_RESULT_STR_CREF GetMapFarGroundByName(const std::string& sName);
    
    CG_RESULT_STR_CREF GetFontPath()const
    {
        return m_sFontPath;
    }

    CG_RESULT_STR_CREF GetMapPath()const
    {
        return m_sMapPath;
    }
    
protected:
    std::string                         m_sAnimationRes;
    //////////////////////////////////  Animation File Path.
    
    std::string                         m_sPhysicsPath;
    
    std::string                         m_sMapPath;
    
    std::string                         m_sFontPath;
    
    std::string                         m_sPhysicsFile;
    
    std::string                         m_sPhysicsString;
    
    std::string                         m_sUIRes;
    //////////////////////////////////  UI File Path.
    
    std::vector<STRUCT_UI_SIZE>         m_vUISizeVec;
    //////////////////////////////////  UI Size Date Vector.
    
    std::vector<STRUCT_UI_TEXTURE>      m_vUIStringVec;
    //////////////////////////////////  UI String and ID Vector
    
    std::vector<std::string>            m_vPlistVec;
    ////////////////////////////////// Storge Plist File Name.
    
    std::vector<STRUCT_PHYSICS>         m_vShipPhysics;
    
    std::vector<STRUCT_TEXTURE_SIZE>    m_vTextrueSize;
    
    std::vector<STRUCT_MAP_INFO>        m_vMapVec;
    
};

#endif /* CGResManager_hpp */
