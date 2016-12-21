//
//  CGAnimateManger.cpp
//  Game
//
//  Created by dongli on 2016/11/1.
//
//

#include "CGAnimateManger.hpp"
#include <cocos2d.h>
#include <iostream>
#include "CGDataType.h"
#include "CGException.hpp"
using namespace cocos2d;

static CGAnimateManager * g_pAnimateManager = nullptr;
/*
 * Global object of singleton
 */


/*
 * shared or create singleton object.
 */


bool CGAnimateManager::InitGObject()
{
    m_sXMLFilePath = "AnimationRes/";
    
    
    return true;
}

bool CGAnimateManager::CleareGObject()
{
    return false;
}

bool CGAnimateManager::DeleteGObject()
{
    delete this;
    return true;
}




/*

 */

void CGAnimateManager::AnalysisXML()
{
    if( ! m_vXMLFileVec.empty() )
    {
        std::vector<std::string>::iterator it = m_vXMLFileVec.begin();
        for(; it != m_vXMLFileVec.end(); it++ )
        {
            FileUtils * t_pFile     = FileUtils::getInstance();
            std::string t_sFileName = m_sXMLFilePath + (*it);
            std::string t_sContent  = t_pFile->getStringFromFile(t_sFileName);
            
            m_vFileContent.push_back(t_sContent);
            
            std::cout<<t_sFileName<<std::endl;
            std::cout<<t_sContent<<std::endl;
        }
    }
    
    if( !m_vFileContent.empty() )
    {
        std::vector<std::string>::iterator i = m_vFileContent.begin();
        for(; i != m_vFileContent.end(); i++ )
        {
            std::vector<std::string> m_vNoPngString;
            std::vector<std::string> m_vStringLine;
            std::vector<std::string> m_vPngString;
            std::string::size_type   t_iStartPos            = 0;
            std::string::size_type   t_iNope                = 0;
            
            while( (t_iNope = (*i).find('\n', t_iStartPos) )!= std::string::npos )
            {
                auto t_sStringLine = (*i).substr(t_iStartPos, t_iNope - t_iStartPos);
                std::cout<<"Substring: "<<t_sStringLine<<std::endl;
                
                m_vStringLine.push_back(t_sStringLine);
                t_iStartPos = ++ t_iNope;
                
                auto t_iFind = t_sStringLine.find(".png");
                
                if( t_iFind != -1 )
                {
                    std::cout<<"PngString: "<<t_sStringLine<<std::endl;
                    
                    int t_iStart       = 0;
                    int t_iEnd         = 0;
                    bool t_bIsSetStart = false;
                    
                    for( int i = 0; i != t_sStringLine.size(); i++ )
                    {
                        if( t_sStringLine[i] != 0x20 )
                        {
                            if( t_bIsSetStart == false )
                            {
                                t_iStart      = i;
                                t_bIsSetStart = true;
                            }
                        }
                    }
                    
                    for( auto i = t_sStringLine.size() - 1; i >= 0; i-- )
                    {
                        if( t_sStringLine[i] != 0x20 )
                        {
                            t_iEnd = i;
                            std::cout<<"iEnd:  "<<t_iEnd<<std::endl;
                            break;
                        }
                    }
                    
                    std::string t_sCleanStr = t_sStringLine.substr(t_iStart, (++t_iEnd) - t_iStart);
                    std::cout<<"Clean String: "<<t_sCleanStr<<std::endl;
                    
                    std::string::size_type iFindPos = t_sCleanStr.find('>');
                    std::string::size_type iEndPos  = t_sCleanStr.find('<', iFindPos + 1);
                    std::string t_sFinalStr         = t_sCleanStr.substr(iFindPos + 1, iEndPos - iFindPos - 1);
                    
                    std::cout<<"Final String: "<<t_sFinalStr<<std::endl;
                    
                    m_vPngString.push_back(t_sFinalStr);
                }
            }
            
            std::string        t_sMinString;
            auto i           = m_vPngString.begin();
            auto t_iMinSize  = m_vPngString[0].size();
            
            for(; i != m_vPngString.end(); i++ )
            {
                if( t_iMinSize > (*i).size() )
                {
                    t_sMinString = (*i);
                    t_iMinSize   = (*i).size();
                }
            }
            
            auto iPos            = t_sMinString.find('.');
            auto t_sObjectName   = t_sMinString.substr(0, iPos );
            
            std::cout<<"ObjectName: "<<t_sObjectName<<std::endl;
            
            
            for(int i = 0; i != m_vPngString.size(); i++)
            {
                EraseSpeicalChar(m_vPngString[i], '-');
                EraseNumber(m_vPngString[i]);
            }
            
            for(int i = 0; i != m_vPngString.size(); i++)
            {
                auto iPos   = m_vPngString[i].find('.');
                auto t_str  = m_vPngString[i].substr(0, iPos);
                m_vNoPngString.push_back(t_str);
            }
            
            
            STRUCT_FLAGS   Flags;
            STRUCT_ANIMATE Animate;
            
            Animate.sObjectName          = t_sObjectName;
            Animate.sPngName             = t_sObjectName + std::string(".png");
            Animate.sPlistName           = t_sObjectName + std::string(".plist");
            int t_iCount                 = 0;
            
            std::string t_sCurrentString = m_vNoPngString[0];
            bool t_bIsOnlyOne            = true;
            
            for( int i = 0; i != m_vNoPngString.size(); i++ )
            {
                if( m_vNoPngString[i] != t_sCurrentString )
                {
                    auto t_iPos              = t_sCurrentString.find('_');
                    auto t_iSize             = t_sCurrentString.size();
                    std::string t_sFlagStr   = t_sCurrentString.substr(t_iPos + 1, t_iSize - t_iPos);
                    Flags.m_sFlagsName       = t_sFlagStr;
                    Flags.m_iFrameCount      = t_iCount;
                    t_sCurrentString         = m_vNoPngString[i];
                    t_iCount                 = 1;
                    t_bIsOnlyOne             = false;
                    Animate.vFlags.push_back(Flags);
                }
                else
                {
                    t_iCount ++;
                }
                
            }
            
            if( t_bIsOnlyOne == true )
            {
                auto t_iPos              = t_sCurrentString.find('_');
                auto t_iSize             = t_sCurrentString.size();
                std::string t_sFlagStr   = t_sCurrentString.substr(t_iPos + 1, t_iSize - t_iPos);
                Flags.m_sFlagsName       = t_sFlagStr;
                Flags.m_iFrameCount      = t_iCount;
                Animate.vFlags.push_back(Flags);

            }
            
            for(int i = 0 ; i != Animate.vFlags.size(); i++)
            {
                STRUCT_A_NAME t_AN;

                std::string t_sFlagStr = Animate.vFlags[i].m_sFlagsName;
                std::string t_sFinName = Animate.sObjectName + "_" + t_sFlagStr;
                t_AN.m_sAnimateName    = t_sFinName;
                t_AN.m_iFrameCount     = Animate.vFlags[i].m_iFrameCount;
                
                Animate.vAnimateName.push_back(t_AN);
            }
            m_vAnimate.push_back(Animate);
            
            
        }
    }
    
    if( ! m_vAnimate.empty() )
    {
        CG_DEBUG_PRINT("Current Aniamte Data: ");
        
        for( auto i : m_vAnimate )
        {
            CG_DEBUG_PRINT(i.sObjectName);
            
            for( auto j : i.vAnimateName )
            {
                CG_DEBUG_PRINT(j.m_sAnimateName);
            }
        }
    }
}

const STRUCT_ANIMATE& CGAnimateManager::GetAnimateStructByID(const std::string &sID)
{
    bool t_bIsFind = false;
    
    for(int i = 0; i != m_vAnimate.size(); i++)
    {
        if(m_vAnimate[i].sObjectName == sID)
        {
            t_bIsFind = true;
            return m_vAnimate[i];
        }
    }
    
    if( t_bIsFind == false )
    {
        std::cout<<"GetAnimateByID Is Error,Can Not Find ID: "<<sID<<std::endl;
        throw CGException("GetAnimateByID Is Error");
    }
}

const std::string & CGAnimateManager::GetPlistNameByID(const std::string &sID)
{
    bool t_bIsFind    = false;
    
    for(int i = 0; i != m_vAnimate.size(); i++)
    {
        for(int j = 0; j != m_vAnimate[i].vAnimateName.size(); j++)
        {
            if( sID == m_vAnimate[i].vAnimateName[j].m_sAnimateName )
            {
                t_bIsFind = true;
                return m_vAnimate[i].sPlistName;
            }
        }
    }
    
    if( t_bIsFind == false )
    {
        std::cout<<"GetPlistName Is Can Not Find ID: "<<sID<<std::endl;
        throw CGException("GetPlistName Is Error");
    }
    
}

const std::string & CGAnimateManager::GetObjectNameByID(const std::string &sID)
{
    bool t_bIsFind    = false;
    
    for(int i = 0; i != m_vAnimate.size(); i++)
    {
        for(int j = 0; j != m_vAnimate[i].vAnimateName.size(); j++)
        {
            if( sID == m_vAnimate[i].vAnimateName[j].m_sAnimateName )
            {
                t_bIsFind = true;
                return m_vAnimate[i].sObjectName;
            }
        }
    }
    
    if( t_bIsFind == false )
    {
        std::cout<<"GetObjectName Is Can Not Find ID: "<<sID<<std::endl;
        throw CGException("GetObjectName Is Error");
    }

}

Animation * CGAnimateManager::GetAnimationByID(const std::string &sID)
{
    
    Animation * t_pAN   = nullptr;
    auto t_sPlitName    = GetPlistNameByID(sID);
    auto t_pFrameCahe   = SpriteFrameCache::getInstance();
    auto t_sObjectName  = GetObjectNameByID(sID);
    auto t_sPlistPath   = m_sXMLFilePath + t_sObjectName + ".plist";
    auto t_bIsLoad      = t_pFrameCahe->isSpriteFramesWithFileLoaded(t_sPlistPath);
    
    if( !t_bIsLoad )
    {
        t_pFrameCahe->addSpriteFramesWithFile(t_sPlistPath);
    }
    else
    {
        Vector<SpriteFrame *> t_vFrame;
        bool t_bIsFind = false;
        
        for(int i = 0; i != m_vAnimate.size(); i++)
        {
            for(int j = 0; j != m_vAnimate[i].vAnimateName.size(); j++)
            {
                if( sID == m_vAnimate[i].vAnimateName[j].m_sAnimateName )
                {
                    
                    auto t_iFrameCount  = m_vAnimate[i].vAnimateName[j].m_iFrameCount;
                    auto t_sFrame       = m_vAnimate[i].vAnimateName[j].m_sAnimateName;
                    t_bIsFind           = true;
                    
                    for(int k = 0; k != t_iFrameCount; k++)
                    {
                        std::string t_sFinStr = t_sFrame + "-";
                        
                        char t_sBuffer[5];
                        
                        if( k < 10 )
                        {
                            sprintf(t_sBuffer, "0%d",k);
                        }
                        else
                        {
                            sprintf(t_sBuffer, "%d",k);
                        }
                        
                        std::string t_sFrameName = t_sFinStr + t_sBuffer + ".png";
                        SpriteFrame * t_pFrame   = t_pFrameCahe->getSpriteFrameByName(t_sFrameName);
                        
                        std::cout<<"FrameName: "<<t_sFrameName<<std::endl;

                        t_vFrame.pushBack(t_pFrame);
                        
                    }
                }
            }
        }
        
        t_pAN = Animation::createWithSpriteFrames(t_vFrame);
        t_pAN->retain();
        
        if( t_bIsFind == false )
        {
            std::cout<<"GetAnimationByName Is Can Not Find ID: "<<sID<<std::endl;
            throw CGException("GetAnimationByName Is Error");
        }
    }
    return t_pAN;
}

const std::vector<std::string>& CGAnimateManager::GetAnimationNameByObject(const std::string &sObject)
{

    m_vAnimateName.clear();
    
    for(auto i : m_vAnimate)
    {
        if( i.sObjectName == sObject )
        {
            for(auto j : i.vAnimateName)
            {
                m_vAnimateName.push_back(j.m_sAnimateName);
            }
            
            return m_vAnimateName;

        }
    }
    
    throw CGException("Can Not Find Animation Name:" + sObject);
}

const std::vector<STRUCT_FLAGS>& CGAnimateManager::GetFlagStructVecByID(const std::string &sID)
{
    bool t_bIsFind = false;
    
    for(int i = 0; i != m_vAnimate.size(); i++)
    {
        if( sID == m_vAnimate[i].sObjectName )
        {
            return m_vAnimate[i].vFlags;
        }
    }
    
    if( t_bIsFind == false )
    {
        std::cout<<"GetFLagsVecByID Is Error,Can Not Find ID: "<<sID<<std::endl;
        throw CGException("GetFLagsVecByID Is Error");
    }
}

void CGAnimateManager::EraseSpeicalChar(std::string& sString, char sChar)
{
    auto i   = sString.begin();
    
    for(; i != sString.end(); i++ )
    {
        if( (*i) == sChar )
        {
            sString.erase(i);
        }
    }

}

void CGAnimateManager::EraseNumber(std::string& sString)
{
    auto i   = sString.begin();
    
    for(; i != sString.end(); i++ )
    {
        if( isdigit((*i)) )
        {
            sString.erase(i);
        }
    }
    
    i = sString.begin();
    
    for(; i != sString.end(); i++ )
    {
        if( isdigit((*i)) )
        {
            sString.erase(i);
        }
    }
}

void CGAnimateManager::EnumXMLFolder()
{

    NSBundle      * t_pBundle        = [NSBundle mainBundle];
    NSString      * t_pPathTemp      = t_pBundle.resourcePath;
    NSString      * t_pPath          = [t_pPathTemp stringByAppendingString:@"/"];
    NSString      * t_pAnimatePath   = [NSString stringWithUTF8String:m_sXMLFilePath.c_str()];
    NSString      * t_pAbsPath       = [t_pPath stringByAppendingString:t_pAnimatePath];
    NSFileManager * t_pFile          = [NSFileManager defaultManager];
    NSEnumerator  * t_pEnum          = [t_pFile enumeratorAtPath:t_pAbsPath];
    NSString      * t_pNextFile;
    
    while( t_pNextFile = [t_pEnum nextObject] )
    {
        auto t_sString  = std::string([t_pNextFile UTF8String]);
        auto t_iSize    = t_sString.find('.');
        
        if( t_sString.size() - t_iSize == 6 )
        {
            m_vXMLFileVec.push_back(t_sString);
            std::cout<<"Push XML String: "<<t_sString<<std::endl;
        }
        else
        {
            std::cout<<"Current String Is Not XMF File: "<<t_sString<<std::endl;
        }
    }
}
/*
 * use objective-c ,enum all file in resrouce path.
 */


