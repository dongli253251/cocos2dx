//
//  CGResManager.cpp
//  Game
//
//  Created by dongli on 2016/11/1.
//
//

#include "CGResManager.hpp"
#include <iostream>
#include <cocos2d.h>
#include "CGDataType.h"
#include "CGException.hpp"
using namespace cocos2d;



bool CGResManager::InitGObject()
{
    
    m_sAnimationRes = "AnimationRes/";
    m_sUIRes        = "UIRes/";
    m_sPhysicsFile  = "ShipPhysics.date";
    m_sPhysicsPath  = "Date/";
    m_sMapPath      = "MapRes/";
    m_sFontPath     = "fonts/";
    
    STRUCT_UI_TEXTURE t_UITexture;
    STRUCT_UI_SIZE    t_UISize;
    
    t_UITexture.iUIID        = UI_BUTTON_OK_NORMAL;
    t_UITexture.sUIString    = "Button_OK_Normal.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID        = UI_BUTTON_OK_DOWN;
    t_UITexture.sUIString    = "Button_OK_Down.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID        = UI_BUTTON_KNOW_NORMAL;
    t_UITexture.sUIString    = "Button_KNOW_Normal.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID        = UI_BUTTON_KNOW_DOWN;
    t_UITexture.sUIString    = "Button_KNOW_Down.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID        = UI_BUTTON_CANCEL_NORMAL;
    t_UITexture.sUIString    = "Button_CANCEL_Normal.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID        = UI_BUTTON_CANCEL_DOWN;
    t_UITexture.sUIString    = "Button_CANCEL_Down.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID        = UI_BUTTON_POWER_NORMAL;
    t_UITexture.sUIString    = "Button_Power_Normal.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID        = UI_BUTTON_POWER_DOWN;
    t_UITexture.sUIString    = "Button_Power_Down.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID       = UI_JOYSTICK_NORMAL;
    t_UITexture.sUIString   = "JoyStick_Normal.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID       = UI_JOYSTICK_BALL;
    t_UITexture.sUIString   = "JoyStick_Ball.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID       = UI_LIFE_BAR_NORMAL;
    t_UITexture.sUIString   = "ShengMing_Normal.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID       = UI_ARMOR_BAR_NORMAL;
    t_UITexture.sUIString   = "ZhuangJia_Normal.png";
    
    m_vUIStringVec.push_back(t_UITexture);

    t_UITexture.iUIID       = UI_TEMP_BAR_NORMAL;
    t_UITexture.sUIString   = "WenDu_Normal.png";
    
    m_vUIStringVec.push_back(t_UITexture);

    t_UITexture.iUIID       = UI_TEMP_BAR_DOWN;
    t_UITexture.sUIString   = "Progress_Down.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID       = UI_ARMOR_BAR_DOWN;
    t_UITexture.sUIString   = "Progress_Down.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UITexture.iUIID       = UI_LIFE_BAR_DOWN;
    t_UITexture.sUIString   = "Progress_Down.png";
    
    m_vUIStringVec.push_back(t_UITexture);
    
    t_UISize.iUIName         = UI_SIZE_POWER_WIDTH;
    t_UISize.iUISize         = 100;
    
    m_vUISizeVec.push_back(t_UISize);
    
    t_UISize.iUIName         = UI_SIZE_POWER_HEIGHT;
    t_UISize.iUISize         = 100;
    
    m_vUISizeVec.push_back(t_UISize);
    
    t_UISize.iUIName         = UI_SIZE_JOYSTICK_HEIGHT;
    t_UISize.iUISize         = 164;
    
    m_vUISizeVec.push_back(t_UISize);
    
    t_UISize.iUIName         = UI_SIZE_JOYSTICK_WIDTH;
    t_UISize.iUISize         = 169;
    
    m_vUISizeVec.push_back(t_UISize);

    //LoadPhysicsFromFile();
    
    //AnalysisString();
    
    t_UISize.iUIName        = UI_SIZE_SCREEN_WIDTH;
    t_UISize.iUISize        = 1334;
    
    m_vUISizeVec.push_back(t_UISize);
    
    t_UISize.iUIName        = UI_SIZE_SCREEN_HEIGHT;
    t_UISize.iUISize        = 750;
    
    m_vUISizeVec.push_back(t_UISize);

    t_UISize.iUIName        = UI_SIZE_BULLET_WIDTH;
    t_UISize.iUISize        = 100;
    
    m_vUISizeVec.push_back(t_UISize);
    
    t_UISize.iUIName        = UI_SIZE_BULLET_HEIGHT;
    t_UISize.iUISize        = 100;
    
    m_vUISizeVec.push_back(t_UISize);
    
    STRUCT_PHYSICS phy;
    
    phy.sShipName     = "RedAir";
    phy.iShipWidth    = 100;
    phy.iShipHeight   = 100;
    phy.iShipDensity  = 1;
    phy.iShipFriction = 0;
    
    m_vShipPhysics.push_back(phy);
    
    
    STRUCT_TEXTURE_SIZE size;
    
    size.sTextrueName = "BulletA";
    size.iHeight      = 35;
    size.iWidth       = 35;
    
    m_vTextrueSize.push_back(size);
    
    size.sTextrueName = "BulletB";
    size.iHeight      = 55;
    size.iWidth       = 55;
    
    m_vTextrueSize.push_back(size);
    
    size.sTextrueName = "FeiDanA";
    size.iHeight      = 100;
    size.iWidth       = 100;
    
    m_vTextrueSize.push_back(size);

    size.sTextrueName = "BackGroundA.png";
    size.iHeight      = 1350;
    size.iWidth       = 1734;
    
    m_vTextrueSize.push_back(size);
    
    STRUCT_MAP_INFO map;
    
    map.sMapName         = "Map1";
    map.iMapXScreenCount = 4;
    map.iMapYScreenCount = 8;
    map.iFarMoveScale    = 10;
    map.iNearMoveScale   = 5;
    map.sFarGroundName   = "BackGroundA.png";
    
    m_vMapVec.push_back(map);
    
    return true;
}

const std::string& CGResManager::GetMapFarGroundByName(const std::string &sName)
{
    bool t_bIsFind = false;
    
    if( ! m_vMapVec.empty() )
    {
        for( int i = 0 ; i != m_vMapVec.size() ; i++ )
        {
            if( m_vMapVec[i].sMapName == sName )
            {
                return m_vMapVec[i].sFarGroundName;
            }
        }
    }
    
    if( ! t_bIsFind )
    {
        CG_DEBUG_PRINT("Map Can Not Find:" + sName )
        
        throw CGException("Map Can Not Find");
    }

}

int CGResManager::GetMapFarScaleByName(const std::string &sName)
{
    bool t_bIsFind = false;
    
    if( ! m_vMapVec.empty() )
    {
        for( auto i : m_vMapVec )
        {
            if( i.sMapName == sName )
            {
                return i.iFarMoveScale;
            }
        }
    }
    
    if( ! t_bIsFind )
    {
        CG_DEBUG_PRINT("Map Can Not Find:" + sName )
        
        throw CGException("Map Can Not Find");
    }
    return 0;
}
int CGResManager::GetMapNearScaleByName(const std::string &sName)
{
    bool t_bIsFind = false;
    
    if( ! m_vMapVec.empty() )
    {
        for( auto i : m_vMapVec )
        {
            if( i.sMapName == sName )
            {
                return i.iNearMoveScale;
            }
        }
    }
    
    if( ! t_bIsFind )
    {
        CG_DEBUG_PRINT("Map Can Not Find:" + sName )
        
        throw CGException("Map Can Not Find");
    }
    return 0;
}

int CGResManager::GetMapWidthByName(const std::string &sName)
{
    bool t_bIsFind = false;
    
    if( ! m_vMapVec.empty() )
    {
        for( auto i : m_vMapVec )
        {
            if( i.sMapName == sName )
            {
                return i.iMapXScreenCount;
            }
        }
    }
    
    if( ! t_bIsFind )
    {
        CG_DEBUG_PRINT("Map Can Not Find:" + sName )
        
        throw CGException("Map Can Not Find");
    }
    return 0;
}

int CGResManager::GetMapHeightByName(const std::string &sName)
{
    bool t_bIsFind = false;
    
    if( ! m_vMapVec.empty() )
    {
        for( auto i : m_vMapVec )
        {
            if( i.sMapName == sName )
            {
                return i.iMapYScreenCount;
            }
        }
    }
    
    if( ! t_bIsFind )
    {
        CG_DEBUG_PRINT("Map Can Not Find:" + sName )
        
        throw CGException("Map Can Not Find");
    }
    
    return 0;

}

int CGResManager::GetTextureHeightByName(const std::string &sName)
{
    if( ! m_vTextrueSize.empty() )
    {
        bool t_bIsFind = false;
        
        for(auto i : m_vTextrueSize)
        {
            if( i.sTextrueName == sName )
            {
                return i.iHeight;
            }
        }
        
        if( !t_bIsFind )
        {
            CG_DEBUG_PRINT("CGResManager::GetTextureHeightByName Is Can Not Find: " + sName);
            throw CGException("CGResManager Is Error");
        }
    }
    else
    {
        CG_DEBUG_PRINT("CGResManager TextureSizeVec Is Empty");
        throw CGException("CGResManager Is Error");
    }
    return 0;
}

int CGResManager::GetTextureWidthByName(const std::string &sName)
{
    if( ! m_vTextrueSize.empty() )
    {
        bool t_bIsFind = false;
        
        for(auto i : m_vTextrueSize)
        {
            if( i.sTextrueName == sName )
            {
                return i.iWidth;
            }
        }
        
        if( !t_bIsFind )
        {
            CG_DEBUG_PRINT("CGResManager::GetTextureWidthByName Is Can Not Find: " + sName);
            throw CGException("CGResManager Is Error");
        }
    }
    else
    {
        CG_DEBUG_PRINT("CGResManager TextureSizeVec Is Empty");
        throw CGException("CGResManager Is Error");
    }
    return 0;
}

void CGResManager::AddNewShipPhysics(const std::string &sID)
{
    bool t_bIsFind = false;
    
    for(auto i : m_vShipPhysics)
    {
        if( i.sShipName == sID )
        {
            t_bIsFind = true;
            CG_DEBUG_PRINT("AddNewShipPhysics Is Rep: ");
            CG_DEBUG_PRINT(sID);
        }
    }
    
    if( !t_bIsFind )
    {
        STRUCT_PHYSICS physics;
        physics.sShipName = sID;
        m_vShipPhysics.push_back(physics);
    }
}


void CGResManager::LoadPhysicsFromFile()
{
    FileUtils * File = FileUtils::getInstance();
    
    auto t_sFullPath = File->fullPathForFilename(m_sPhysicsPath + m_sPhysicsFile);
    m_sPhysicsString = File->getStringFromFile(t_sFullPath);
    
}

void CGResManager::AnalysisString()
{
    
    if( !m_sPhysicsString.empty() )
    {
        std::vector<std::string> t_vString;
        std::vector<std::string> t_vCleanString;
        int t_iNope = 0;
        int t_iPos  = 0;
        
        while( (t_iNope = m_sPhysicsString.find(';', t_iPos)) != -1 )
        {
            auto t_sStringLine = m_sPhysicsString.substr(t_iPos, t_iNope - t_iPos);
            t_iPos             = ++ t_iNope;
            
            CG_DEBUG_PRINT("Line: " + t_sStringLine);
            t_vString.push_back(t_sStringLine);
        }

        
        for(auto i : t_vString)
        {
            auto it = i.begin();
            
            if( (*it) == ';')
            {
                i.erase(it);
                continue;
            }
            else
            {
                it++;
            }
        }
        


        
        STRUCT_PHYSICS phy;
        for(auto i : t_vString)
        {
            CG_DEBUG_PRINT(i);
            auto iPos             = i.find(':');
            auto iSize            = i.size();
            std::string sStrKey   = i.substr(0,iPos);
            std::string sStrValue = i.substr(iPos + 1, iSize - iPos);
            
            CG_DEBUG_PRINT(sStrKey);
            CG_DEBUG_PRINT(sStrValue);
            
            
            
            if( sStrKey == "ShipName" )
            {
                phy.sShipName = sStrValue;
            }
            
            else if( sStrKey == "ShipHeight" )
            {
                phy.iShipHeight  = atoi(sStrValue.c_str());
            }
            
            else if( sStrKey == "ShipWidth" )
            {
                phy.iShipWidth = atoi(sStrValue.c_str());
            }
            
            else if( sStrKey == "ShipFriction" )
            {
                phy.iShipFriction = atoi(sStrValue.c_str());
            }
            
            else if( sStrKey == "ShipDensity" )
            {
                phy.iShipDensity = atoi(sStrValue.c_str());
            }
            
            else
            {
                //CG_DEBUG_PRINT("Ship Physics Date Error");
            }
            
        }
        
        m_vShipPhysics.push_back(phy);
    }
}

const std::string & CGResManager::GetUITextureString(int iUIID)
{
    bool t_bIsFind = false;
    for( int i = 0; i != m_vUIStringVec.size(); i++ )
    {
        if(m_vUIStringVec[i].iUIID == iUIID)
        {
            t_bIsFind = true;
            return m_vUIStringVec[i].sUIString;
        }
    }
    
    if( t_bIsFind == false )
    {
        throw CGException("GetUITextureString Is Can Not Find");
        //use exp;
    }
    
}

int CGResManager::GetUISizeByName(int iUIName)
{
    
    bool t_bIsFind = false;
    
    if( m_vUISizeVec.empty() == false )
    {
        for(int i = 0; i != m_vUISizeVec.size(); i++)
        {
            if( m_vUISizeVec[i].iUIName == iUIName )
            {
                return m_vUISizeVec[i].iUISize;
            }
        }
    }
    
    if( t_bIsFind == false )
    {
        std::cout<<"GetUISizeByName Is Can Not Find: "<<iUIName<<std::endl;
        
        throw CGException("GetUISizeByName Is Can Not Find");
    }
}

bool CGResManager::CleareGObject()
{
    return true;
}

bool CGResManager::DeleteGObject()
{
    delete this;
    return true;
}

void CGResManager::AutoLoadAnimationPath()
{
    NSBundle      * t_pBundle        = [NSBundle mainBundle];
    NSString      * t_pPathTemp      = t_pBundle.resourcePath;
    NSString      * t_pPath          = [t_pPathTemp stringByAppendingString:@"/"];
    NSString      * t_pAnimatePath   = [NSString stringWithUTF8String:m_sAnimationRes.c_str()];
    NSString      * t_pAbsPath       = [t_pPath stringByAppendingString:t_pAnimatePath];
    NSFileManager * t_pFile          = [NSFileManager defaultManager];
    NSEnumerator  * t_pEnum          = [t_pFile enumeratorAtPath:t_pAbsPath];
    NSString      * t_pNextFile;
    
    while( t_pNextFile = [t_pEnum nextObject] )
    {
        std::string t_sString = std::string([t_pNextFile UTF8String]);
        int t_iSize           = t_sString.find('.');
        
        if( t_sString.size() - t_iSize == 6 )
        {
            std::cout<<"Load Plist Name: "<<t_sString<<std::endl;
            m_vPlistVec.push_back(t_sString);
            LoadSpeciaPlistByName(t_sString);
        }
        else
        {
            std::cout<<"Current String Is Not XMF File: "<<t_sString<<std::endl;
        }
    }

}



void CGResManager::LoadSpeciaPlistByName(const std::string &sName)
{
    bool t_bIsLoad      = false;
    auto t_pFrameCache  = SpriteFrameCache::getInstance();
    auto t_sPlistName   = m_sAnimationRes + sName;
    
    if( !t_pFrameCache->isSpriteFramesWithFileLoaded(t_sPlistName.c_str()) )
    {
        t_pFrameCache->addSpriteFramesWithFile(t_sPlistName.c_str());
        
        std::cout<<"Plist Is Load: "<<t_sPlistName<<std::endl;
    }
    else
    {
        std::cout<<"Plist Name Load Repley: "<<sName<<std::endl;
    }
}

void CGResManager::LoadAnimationRes()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AnimationRes/RedAir.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AnimationRes/FeiDanA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AnimationRes/BeHitA.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AnimationRes/XiaoBing.plist");

}
