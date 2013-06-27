//
//  CCPhysicDebugNode.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-19.
//
//

#include "CCPhyDebugNode.h"
#include "FE.h"
#include "FEUtility.h"
#include "GameBase.h"
using namespace FESimple;

void CCPhyDebugNode::draw()
{
    get_game()->get_phy_world()->DrawDebugData();
}