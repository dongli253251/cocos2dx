//
//  CGDataType.h
//  Game
//
//  Created by dongli on 2016/10/26.
//
//

#ifndef CGDataType_h
#define CGDataType_h

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;

/*
 *
 
 DATE PACKET FORMAT:
 
 
 TYPE:RPOTOCOL_HEAD
 ENCRYPTION:1 || 0
 NAME:REQUEST_LOGIN || else
 SIZE:size of pakcet
 
 TYPE:PROTOCOL_BODY
 NAME:REQUEST_LOGIN || ELSE
 DATENAME:??????
 DATENAME:??????
 
 */


#define CG_CLASS

extern long GetMilliSecond();

#define CG_RESULT_BOOL          bool
#define CG_RESULT_INT           int
#define CG_RESULT_FLOAT         float
#define CG_RESULT_SIZE_CREF     const Size&
#define CG_RESULT_POINT_CREF    const Point&
#define CG_RESULT_STR_CREF      const std::string&
#define CG_RESULT_VOID          void
#define CG_RESULT_UINT          unsigned int
#define CG_RESULT_POINT         Point
#define CG_RESULT_LONG          long
/**
 *- mark all method
 */


#ifdef CC_PLATFORM_IOS 

#define UINT    unsigned int
#define ULONG   unsigned long
#define UFLOAT  unsigned float
#define UDOUBLE unsigned double
#define UCHAR   unsigned char


#endif





#define DEBUG_ENABLE    1
#define DEBUG_DISABLE   0

const bool DEBUG_STATE = DEBUG_ENABLE;


#define CG_DEBUG_PRINT(str)\
if(DEBUG_STATE)\
std::cout<<str<<std::endl;


#define CG_DEBUG_PRINT_1(str,var)\
if(DEBUG_STATE)\
{\
    std::cout<<str<<var<<std::endl;\
}\


#define CG_DEBUG_PRINT_2(str,var1,var2)\
if(DEBUG_STATE)\
{\
    std::cout<<str<<var1<<var2<<std::endl;\
}\



#define CG_CONSTRUCTION_DEFAULT(classType) \
\
    classType()\
    {\
        std::cout<<#classType<<"Is Create"<<std::endl; \
    }\
    
#define CG_CONSTRUCTION_COPY(classType)\
classType(const classType& rhs)\
{\
std::cout<<#classType<<"Is Create"<<std::endl;\
}\
\
classType& operator = (const classType& a)\
{\
    return *this;\
}\



#define CG_DESTROY_DEFAULT(classType) \
\
    virtual ~classType()\
    {\
        std::cout<<#classType<<"Is Destroy"<<std::endl;\
        CleareGObject();\
    }



#define CG_OVERLOAD_GRAPHICS \
virtual bool InitGObject();\
virtual bool CleareGObject();\
virtual bool DeleteGObject();\
virtual void DrawGObject();


#define CG_OVERLOAD_COM \
virtual bool InitGObject();\
virtual bool CleareGObject();\
virtual bool DeleteGObject();



#define CG_SINGLETON_CREATE(name)\
    inline static CG##name * shared##name()\
    {\
        static CG##name * t_pManager = nullptr;\
        if(t_pManager == nullptr)\
        {\
            t_pManager = new CG##name();\
            t_pManager->InitGObject();\
            return t_pManager;\
        }\
        else\
        {\
            return t_pManager;\
        }\
    }



#define CG_OBJECT_CREATE_INT_1(name, var)\
    static CG##name * Create##name(int var)\
    {\
        auto t_pObject = new CG##name(var);\
        if(t_pObject != nullptr)\
        {\
            t_pObject->InitGObject();\
            return t_pObject;\
        }\
        else\
        {\
            std::cout<<#name<<"Create Is Error"<<std::endl;\
            throw CGException("Create Is Error");    \
        }\
    }\



#define CG_OBJECT_CREATE(name)\
static CG##name * Create##name()\
{\
    auto object = new CG##name();\
    if( object != nullptr)\
    {\
        object->InitGObject();\
        return object;\
    }\
    else\
    {\
        CG_DEBUG_PRINT("Create Is Error");\
        throw CGException("Create Is error");\
    }\
}

#define CG_OBJECT_CREATE_CSTR_1(name,var)\
static CG##name * Create##name(const std::string& var)\
{\
    auto t_pObject = new CG##name(var);\
    if(t_pObject != nullptr)\
    {\
        t_pObject->InitGObject();\
        return t_pObject;\
    }\
    else\
    {\
        CG_DEBUG_PRINT("Create Is Error");\
        throw CGException("Create Is Error");    \
    }\
}


#define CG_ACCESS_INT(name)\
int Get##name()const\
{\
    return m_i##name;\
}\
void Set##name(int var)\
{\
    m_i##name = var;\
}\

#define CG_ACCESS_BOOL(name)\
bool Get##name()\
{\
return m_b##name;\
}\
void Set##name(bool var)\
{\
m_b##name = var;\
}\

#define CG_ACCESS_STR(name)\
const std::string& Get##name()\
{\
    return m_s##name;\
}\
void Set##name(const std::string& var)\
{\
    m_s##name = var;\
}\




#define CG_ACCESS_FLOAT(name)\
int Get##name()const\
{\
return m_f##name;\
}\
void Set##name(float var)\
{\
m_f##name = var;\
}\




#define CG_NET_ACCESS_INT(name)\
\
inline void SetNetPlayer##name(const std::string& id, int var)\
{\
    bool t_bIsFind = false;\
    for(int i = 0; i != m_vNetPlayer.size(); i++)\
    {\
        if( m_vNetPlayer[i].sPlayerName == id)\
        {\
            m_vNetPlayer[i].iPlayer##name = var;\
            t_bIsFind = true;\
        }\
    }\
    if( !t_bIsFind )\
    {\
        std::cout<<"SetPlayerINT Error: "<<id<<std::endl;\
        throw CGException("SetNetPlayerINT Error");\
    }\
}\
\
inline int GetNetPlayer##name(const std::string& id)\
{\
    bool t_bIsFind = false;\
    for(auto i : m_vNetPlayer )\
    {\
        if(i.sPlayerName == id )\
        {\
            return i.iPlayer##name;\
        }\
    }\
    if( t_bIsFind == false)\
    {\
        std::cout<<"GetPlayerINT Error: "<<id<<std::endl;\
        throw CGException("GetNetPlayerINT Error");\
    }\
    return - 1;\
}


#define CG_NET_ACCESS_STR(name1)\
\
inline void SetNetPlayer##name1(const std::string& id,  const std::string& var)\
{\
    bool t_bIsFind = false;\
    \
    for(int i = 0; i != m_vNetPlayer.size();i ++)\
    {\
        if( m_vNetPlayer[i].sPlayerName == id)\
        {\
            m_vNetPlayer[i].sPlayer##name1 = var;\
            t_bIsFind = true;\
        }\
    }\
    if( !t_bIsFind )\
    {\
        std::cout<<"id: "<<id<<"var: "<<var<<std::endl;\
        throw CGException("SetNetPlayer Error");\
    }\
}\
\
inline const std::string& GetNetPlayer##name1(const std::string& id)\
{\
    bool t_bIsFind = false;\
    for(auto i:m_vNetPlayer)\
    {\
        if(i.sPlayerName == id)\
        {\
            return i.sPlayer##name1;\
            t_bIsFind = true;\
        }\
    }\
    if( !t_bIsFind )\
    {\
        std::cout<<"id: "<<id<<std::endl;\
        throw CGException("GetNetPlayer Error");\
    }\
}\


#define CG_ACCESS_PHYSICS_INT(name)\
inline void SetShip##name(const std::string& id,int var)\
{\
    bool t_bIsFind = false;\
    for(int i = 0; i != m_vShipPhysics.size(); i++)\
    {\
        if(m_vShipPhysics[i].sShipName == id)\
        {\
            m_vShipPhysics[i].iShip##name = var;\
            t_bIsFind = true;\
        }\
    }\
    if(t_bIsFind == false)\
    {\
        std::cout<<"SetShip Is Error: "<<id<<std::endl;\
        throw CGException("SetShip Is Error");\
    }\
}\
\
inline int GetShip##name(const std::string& id)\
{\
    bool t_bIsFind = false;\
    for(auto i : m_vShipPhysics)\
    {\
        if(i.sShipName == id)\
        {\
            return i.iShip##name;\
        }\
    }\
\
    if( t_bIsFind == false)\
    {\
        std::cout<<"GetShip Is Error: "<<id<<std::endl;\
        throw CGException("GetShip Is Error");\
    }\
}\


extern ULONG GetTouchOnlyCount();

const int       GAME_STATE_LOGO             = 1;
const int       GAME_STATE_OPTION           = 2;
const int       GAME_STATE_SELECT           = 3;
const int       GAME_STATE_LOGIC            = 4;
const int       GAME_STATE_PAUSE            = 5;
const int       GAME_STATE_MAIN             = 9;
const int       GAME_STATE_RESUME           = 6;
const int       GAME_STATE_END              = 7;
const int       GAME_STATE_TITLE            = 8;

const int       SOCKET_TYPE_TCP             = 1;
const int       SOCKET_TYPE_UDP             = 2;

const int       PLAYER_ORIENTATION_LEFT     = 1;
const int       PLAYER_ORIENTATION_RIGHT    = 2;

const int       ANIMATION_LOOP_INFINTE      = -1;
const int       ANIMATION_LOOP_ONECE        = 1;
const int       ANIMATION_STATE_MOVE        = 1;
const int       ANIMATION_STATE_STAND       = 2;
const int       ANIMATION_STATE_ATTACK      = 3;
const int       ANIMATION_STATE_HIT         = 4;
const int       ANIMATION_STATE_DIE         = 5;
const float     ANIMATION_DELAY_DEFAULT     = 0.1f;

const float     GAME_INTERVAL               = 1.0f / 60.0f;

const int       DEEP_UI_DEFAULT             = 100;
const int       DEEP_UI_NUMBER              = 110;
const int       DEEP_MONSTER_DEFAULT        = 80;
const int       DEEP_BULLET_DEFAULT         = 90;
const int       DEEP_PLAYER_DEFAULT         = 80;
const int       DEEP_FARGROUND_DEFAULT      = 50;

const int       UI_NORMAL_BUTTON            = 1;


const int       UI_ONLY_ID_POWER_BUTTON    = 10;
const int       UI_ONLY_ID_JOYSTICK        = 11;
const int       UI_ONLY_ID_BULLET          = 12;

const int       PHYSICS_PLAYER_SCALE       = 10;


const int       BULLET_ORIENTAION_LEFT     =1;
const int       BULLET_ORIENTAION_RIGHT    = 2;

#define PHYSICS_SCALE  10

const long      MAX_COUNT                  = 9999999999L;

enum ENUM_BULLET_OWNER
{
    BULLET_OWNER_LOCAL,
    BULLET_OWNER_NET
};

enum ENUM_PHYSICS_TYPE
{
    PHYSICS_TYPE_STATIC = 1,
    PHYSICS_TYPE_DYNAMIC,
};

enum ENUM_PLAYER_PHYSICS_STATE
{
    PLAYER_PHYSICS_LEFT  = 1,
    PLAYER_PHYSICS_RIGHT,
    PLAYER_PHYSICS_DOWN,
    PLAYER_PHYSICS_UP,
    PLAYER_PHYSICS_LEFT_UP,
    PLAYER_PHYSICS_RIGHT_UP,
    PLAYER_PHYSICS_LEFT_DOWN,
    PLAYER_PHYSICS_RIGHT_DOWN
};

enum ENUM_MOSNTER_ORIENTATION
{
    MONSTER_ORIENTATION_LEFT = 1,
    MONSTER_ORIENTATION_RIGHT,
    MONSTER_ORIENTATION_UP,
    MONSTER_ORIENTATION_DOWN,
};

enum ENUM_JOYSTICK_VALUE
{
    JOYSTICK_ORIENTATION_RIGHT_1 = 1,
    JOYSTICK_ORIENTATION_RIGHT_2,
    JOYSTICK_ORIENTATION_LEFT_1,
    JOYSTICK_ORIENTATION_LEFT_2,
    JOYSTICK_ORIENTATION_UP,
    JOYSTICK_ORIENTATION_DOWN,
    JOYSTICK_ORIENTATION_LEFT_UP,
    JOYSTICK_ORIENTATION_RIGHT_UP,
    JOYSTICK_ORIENTATION_RIGHT_DOWN,
    JOYSTICK_ORIENTATION_LEFT_DOWN
};

enum ENUM_PLAYER_TYPE
{
    PLAYER_TYPE_LOCAL = 1,
    PLAYER_TYPE_NET,
    PLAYER_TYPE_AI
}

;

enum ENUM_JOYSTICK_TYPE
{
    JOYSTICK_TYPE_NORMAL = 1,
};

enum ENUM_BUTTON_TYPE
{
    BUTTON_TYPE_OK  = 1,
    BUTTON_TYPE_KNOW,
    BUTTON_TYPE_CANCEL,
    BUTTON_TYPE_POWER
};


enum ENUM_BUTTON_STATE
{
    BUTTON_STATE_PUSH = 1,
    BUTTON_STATE_POP
};


enum ENUM_UI_STRING
{
    UI_BUTTON_OK_NORMAL = 1,
    UI_BUTTON_OK_DOWN,
    UI_BUTTON_CANCEL_NORMAL,
    UI_BUTTON_CANCEL_DOWN,
    UI_BUTTON_KNOW_NORMAL,
    UI_BUTTON_KNOW_DOWN,
    UI_BUTTON_POWER_NORMAL,
    UI_BUTTON_POWER_DOWN,
    UI_JOYSTICK_NORMAL,
    UI_JOYSTICK_BALL,
    UI_LIFE_BAR_NORMAL,
    UI_LIFE_BAR_DOWN,
    UI_ARMOR_BAR_NORMAL,
    UI_ARMOR_BAR_DOWN,
    UI_TEMP_BAR_NORMAL,
    UI_TEMP_BAR_DOWN,
};

enum ENUM_UI_SIZE
{
    UI_SIZE_POWER_WIDTH = 1,
    UI_SIZE_POWER_HEIGHT,
    UI_SIZE_JOYSTICK_HEIGHT,
    UI_SIZE_JOYSTICK_WIDTH,
    UI_SIZE_SCREEN_WIDTH,
    UI_SIZE_SCREEN_HEIGHT,
    UI_SIZE_BULLET_WIDTH,
    UI_SIZE_BULLET_HEIGHT
};

enum ENUM_DATE_TYPE
{
    DATE_TYPE_INT = 1,
    DATE_TYPE_LONG,
    DATE_TYPE_FLOAT,
    DATE_TYPE_DOUBLE,
    DATE_TYPE_STR
};

typedef enum tagFarID
{
    RECT_ID_LEFT_DOWN__LEFT_DOWN = 1,
    RECT_ID_LEFT_DOWN__LEFT_UP,
    RECT_ID_LEFT_DOWN__RIGHT_DOWN,
    
    RECT_ID_LEFT_UP__LEFT_DOWN,
    RECT_ID_LEFT_UP__LEFT_UP,
    RECT_ID_LEFT_UP__RIGHT_UP,
    
    RECT_ID_RIGHT_DOWN__LEFT_DOWN,
    RECT_ID_RIGHT_DOWN__RIGHT_UP,
    RECT_ID_RIGHT_DOWN__RIGHT_DOWN,
    
    RECT_ID_RIGHT_UP__LEFT_UP,
    RECT_ID_RIGHT_UP__RIGHT_UP,
    RECT_ID_RIGHT_UP__RIGHT_DOWN,
    
    RECT_ID_RIGHT,
    RECT_ID_LEFT,
    RECT_ID_UP,
    RECT_ID_DOWN,
    
    RECT_ID_CENTER,
    
    RECT_ID_LEFT_DOWN_LEFT,
    RECT_ID_LEFT_DOWN_RIGHT,
    RECT_ID_LEFT_DOWN_UP,
    RECT_ID_LEFT_DOWN_DOWN,
    
    RECT_ID_LEFT_UP_LEFT,
    RECT_ID_LEFT_UP_RIGHT,
    RECT_ID_LEFT_UP_UP,
    RECT_ID_LEFT_UP_DOWN,
    
    RECT_ID_RIGHT_UP_LEFT,
    RECT_ID_RIGHT_UP_RIGHT,
    RECT_ID_RIGHT_UP_UP,
    RECT_ID_RIGHT_UP_DOWN,
    
    RECT_ID_RIGHT_DOWN_DOWN,
    RECT_ID_RIGHT_DOWN_UP,
    RECT_ID_RIGHT_DOWN_LEFT,
    RECT_ID_RIGHT_DOWN_RIGHT,
    
}ENUM_FAR_ID;

enum 
{
    NUMBER_TYPE_NORMAL_DAMEGE = 1,
    NUMBER_TYPE_CRUSH_DAMEGE,
    NUMBER_TYPE_NORMAL_RECOVERY,
    NUMBER_TYPE_CRUSH_RECOVERY
};


typedef union tagProtocolType
{
    float           fDate;
    int             iDate;
    double          dDate;
    long            lDate;
    
}UNION_PROTOCOL_DATE;

typedef struct tagProtocolPakcet
{
    std::string         sDateName;
    std::string         sDate;
    int                 iType;
    UNION_PROTOCOL_DATE uDate;
    
}STRUCT_PROTOCOL_PACKET;


typedef struct tagTextureSize
{
    std::string     sTextrueName;
    int             iHeight;
    int             iWidth;
    
}STRUCT_TEXTURE_SIZE;

typedef union tagPlayerDateType
{
    int             Int_Type;
    bool            Bool_Type;
    float           Float_Type;
    double          Double_Type;
    char            Char_Type;
    long            Long_Type;
}UNION_PLAYER_DATE_TYPE;

typedef struct tagFarRect
{
    int                  iRectID;
    cocos2d::Rect        Rect;
    
}STRUCT_FARRECT;



typedef struct tagAnimateFlags
{
    std::string         m_sFlagsName;
    int                 m_iFrameCount;
    
}STRUCT_FLAGS, * STRUCT_FLAGSP;

typedef struct tagNetPlayer
{
    std::string     sPlayerID;
    std::string     sPlayerName;
    int             iPlayerRank;
    int             iPlayerAttack;
    int             iPlayerDefense;
    int             iPlayerLife;
    int             iPlayerEnergy;
    int             iPlayerItem;
    int             iPlayerBulletSpeed;
    
}STRUCT_NET_PLAYER;


typedef struct tagMapElementInfo
{
    std::string         sElementName;
    int                 iElementHeight;
    int                 iElementWidht;
    
}STRUCT_ELEMENT_INFO;

typedef struct tagMapInfo
{
    std::string                         sMapName;
    std::string                         sFarGroundName;
    int                                 iMapXScreenCount;
    int                                 iMapYScreenCount;
    int                                 iFarMoveScale;
    int                                 iNearMoveScale;
    std::vector<STRUCT_ELEMENT_INFO>    vElementList;
}STRUCT_MAP_INFO;

typedef struct tagAnimateName
{
    std::string         m_sAnimateName;
    int                 m_iFrameCount;
    
}STRUCT_A_NAME,* STRUCT_A_NAMEP;

typedef struct tagAnimateStruct
{
    std::string                         sObjectName;
    //////////////////////////////////  Animate Front Name.like Frank_Solider.
    
    std::string                         sPlistName;
    //////////////////////////////////  Animate Texture in This Plist.
    
    std::string                         sPngName;
    //////////////////////////////////  Aniamte Png File.
    
    std::vector<STRUCT_FLAGS>           vFlags;
    //////////////////////////////////  Animate Type Name and Frame Amount.
    
    std::vector<STRUCT_A_NAME>          vAnimateName;
    //////////////////////////////////  Animate Name and Frame Amount.
}STRUCT_ANIMATE, * STRUCT_ANIMATEP;

/**
 *- This Struct Represent a Animate .
 *
 */




typedef struct tagPhysicsInfo
{
    std::string         sShipName;
    int                 iShipWidth;
    int                 iShipHeight;
    int                 iShipDensity;
    int                 iShipFriction;
    
}STRUCT_PHYSICS;

typedef struct tagTouchPointInfo
{
    
    bool                         bIsEnd;
    UINT                         uTouchID;
    ULONG                        uOnlyCount;
    cocos2d::Point               BeganPoint;
    cocos2d::Point               MovePoint;
    cocos2d::Point               EndPoint;
    
}STRUCT_TOUCH_INFO;

#endif /* CGDataType_h */
