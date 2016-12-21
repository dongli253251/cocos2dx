//
//  CGMonsterBase.cpp
//  Game
//
//  Created by dongli on 2016/12/13.
//
//

#include "CGMonsterBase.hpp"

bool CGMonsterBase::InitGObject()
{
    return true;
}

bool CGMonsterBase::CleareGObject()
{
    return true;
}

void CGMonsterBase::DrawGObject()
{

}

bool CGMonsterBase::DeleteGObject()
{
    delete this;
    return true;
}
