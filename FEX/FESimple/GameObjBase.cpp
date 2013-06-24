//
//  GameObjBase.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-6.
//
//
#include "FE.h"
#include "GameObjBase.h"
FE_NS_BEGIN

GameObjBase::GameObjBase( const std::map<Name, std::string>& params )
{
}

GameObjBase::GameObjBase()
{
}

GameObjBase::~GameObjBase()
{

    logger("obj lifetime") << "object: " << name << "( " << this << " ) destoryed" << endl;
}

void GameObjBase::update( float delta_time )
{
}

FE_NS_END