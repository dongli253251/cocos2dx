//
//  CGDamegeSystem.hpp
//  Game
//
//  Created by dongli on 2016/11/30.
//
//

#ifndef CGDamegeSystem_hpp
#define CGDamegeSystem_hpp

#include <stdio.h>
#include <iostream>
#include <CGDataType.h>
#include <CGComObject.hpp>

class CGDamegeNumber;
class CG_CLASS CGDamegeSystem:public CGComObject
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGDamegeSystem)
    
    CG_CONSTRUCTION_COPY(CGDamegeSystem)
public:
    CG_DESTROY_DEFAULT(CGDamegeSystem)
    
    CG_SINGLETON_CREATE(DamegeSystem)
    
    CG_OVERLOAD_COM
    
    CG_RESULT_VOID ShowDamegeNumber(int iNumber,int iType,const Point& Position);
    
    CG_RESULT_VOID ProcessDamegeTask();
    
    BezierTo * CreateBezier(float fTime, const Point& Start, const Point& End, float fAngle);
    
    CG_ACCESS_STR(DamegeFont)
    
    CG_ACCESS_STR(FontPath)
    
    CG_ACCESS_INT(NormalFontSize)
    
    CG_ACCESS_INT(CrushFontSize)
    
    Color3B GetNormalColor()const
    {
        return m_NormalColor;
    }
    
    Color3B GetCrushColor()const
    {
        return m_CrushColor;
    }
    
protected:
    std::vector<CGDamegeNumber *>           m_vNumber;
    std::string                             m_sDamegeFont;
    std::string                             m_sFontPath;
    int                                     m_iNormalFontSize;
    int                                     m_iCrushFontSize;
    Color3B                                 m_NormalColor;
    Color3B                                 m_CrushColor;
    
};


#endif /* CGDamegeSystem_hpp */
