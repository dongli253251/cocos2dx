//
//  CGComObject.cpp
//  Game
//
//  Created by dongli on 2016/10/28.
//
//

#include "CGComObject.hpp"

bool CGComObject::InitGObject()
{
    return true;
}

bool CGComObject::DeleteGObject()
{
    delete this;
    return true;
}

bool CGComObject::CleareGObject()
{
    return true;
}
