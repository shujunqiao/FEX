//
//  FECommon.h
//  FEX
//
//  Created by Fancyzero on 13-6-8.
//
//

#ifndef __FEX__FECommon__
#define __FEX__FECommon__

#include <memory>
#include <map>
#include <string>
#include <vector>
#define FE_NS_BEGIN namespace FESimple{
#define FE_NS_END }
#define FE_NS_USING using namespace FESimple;
FE_NS_BEGIN

class GameObjBase;
class SpriteBase;

typedef std::shared_ptr<GameObjBase> GameObjPtr;
typedef std::shared_ptr<SpriteBase> SpritePtr;
typedef std::string Name;
typedef std::map<Name, std::string> SpawnParams;

FE_NS_END
#include "cocos2d.h"
#include "ClassInfo.h"

#include "GameObjFactory.h"

#include "FEUtility.h"
#include "GameBase.h"
#include "GameObjBase.h"
#endif /* defined(__FEX__FECommon__) */
