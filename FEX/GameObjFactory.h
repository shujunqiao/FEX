//
//  GameObjFactory.h
//  FEX
//
//  Created by Fancyzero on 13-6-23.
//
//

#ifndef __FEX__GameObjFactory__
#define __FEX__GameObjFactory__

#include "FE.h"

FE_NS_BEGIN

void register_FEX_classes();
std::map<std::string,const ClassInfo*>& get_classes_map();

class GameObjFactory
{
public:
    static GameObjPtr construct_obj( const Name& classname, const SpawnParams& params );
    static const std::map<std::string, const ClassInfo*>& get_all_classes();
    static void add_class_info(const ClassInfo* info);
};
FE_NS_END
#endif /* defined(__FEX__GameObjFactory__) */
