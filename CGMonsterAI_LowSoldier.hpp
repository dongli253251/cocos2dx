//
//  CGMonsterAI_LowSoldier.hpp
//  Game
//
//  Created by dongli on 2016/12/15.
//
//

/** 
 *- 
 * low Level Soldier AI.
 *
 *
 */

#ifndef CGMonsterAI_LowSoldier_hpp
#define CGMonsterAI_LowSoldier_hpp

#include <iostream>
#include <CGMonsterAI.hpp>
#include <CGDataType.h>
#include <CGException.hpp>
#include <CGPirateSoldier.hpp>

class CG_CLASS CGMonsterAI_LowSoldier:public CGMonsterAI
{
protected:
    CG_CONSTRUCTION_DEFAULT(CGMonsterAI_LowSoldier)
    
    CG_CONSTRUCTION_COPY(CGMonsterAI_LowSoldier)
    
    CGMonsterAI_LowSoldier(CGMonsterBase * pMonster)
    {
        m_pSoldier = dynamic_cast<CGPirateSoldier *>(pMonster);
    }
public:
    CG_OVERLOAD_COM


    enum 
    {
    	AI_EVENT_MOVE = 1,
    	AI_EVENT_STAND,
    	AI_EVENT_ATTACK_NORMAL,
    	AI_EVENT_ATTACK_WEAPON,
    	AI_EVENT_ATTACK_CRUSH,
    	EVENT_TYPE_NOW,
    	EVENT_TYPE_SEQUNCE
    };

    typedef struct tagAIEvent
    {
    	int   iEventName;
    	float fPointX;
    	float fPointY;
    	int  iRange;
    	int  iStandTime;
    	int  iOrient;
    	int  iIndex;
    	bool bIsRuning;
    	bool bIsOver;

        tagAIEvent()
        {
            
        }
        
    	tagAIEvent(int Event, int Range, int Orient, int Index)
    	{
    		iEventName = Event;
    		iRange     = Range;
    		iOrient    = Orient;
    		iIndex     = Index;
    		bIsRuning  = false;
    		bIsOver    = false;
        };

    }STRUCT_AI_EVENT;
    
    CG_RESULT_VOID AddEventToList(int iName,float fPointX, float fPointY, int iRange, int iOrient, int iType);


    CG_RESULT_VOID AddMoveEventToList(float fX,float fY,int iType);
    
    static CGMonsterAI_LowSoldier * CreateLowSoldierAI(CGMonsterBase * pMonster);
    
    //static CGMonsterAI_LowSoldier * CreateLowSoldierAI();
    
    //CG_RESULT_VOID SetDirveObject(CGPirateSoldier * pMonster);
    
    CG_RESULT_VOID SetDirveObject(CGMonsterBase * pMonster);
    
    CG_RESULT_VOID ProcessAITask();

    CG_RESULT_VOID ProcessPoint(STRUCT_AI_EVENT & Event);

    CG_RESULT_VOID ProcessMoveEvent(STRUCT_AI_EVENT & Event);

    CG_RESULT_VOID ProcessStandEvent(STRUCT_AI_EVENT & Event);

    
protected:
	std::vector<STRUCT_AI_EVENT>		m_vEventList;
    CGPirateSoldier *                   m_pSoldier;
    int                                 m_iAIState;
    int 								m_iCurrentEventIndex;
    int 								m_iInterval;
    int 								m_iEventCount;
    int 								m_iMoveSpeed;
    Point 								m_TargetPoint;
    ULONG 								m_iLastTime;
    float								m_fXRange;
    float 								m_fXMovedCount;
    float 								m_fYMovedCount;
    float 								m_fYRange;
    float 								m_fXSetup;
    float 								m_fYSetup;
    bool 								m_bIsProcessPoint;
    bool								m_bIsBreakEvent;
    bool								m_bIsRunEvent;
    
    std::vector<STRUCT_AI_EVENT>::iterator m_it;
};

#endif /* CGMonsterAI_LowSoldier_hpp */
