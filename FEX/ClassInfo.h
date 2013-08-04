//
//  ClassInfo.h
//  FEX
//
//  Created by Fancyzero on 13-6-23.
//
//

#ifndef FEX_ClassInfo_h
#define FEX_ClassInfo_h
#include "FE.h"
#include <string>
#include <vector>
#include <functional>

namespace FESimple
{

class ClassInfo
{
public:
//    ClassInfo(const Name& name, const std::vector<ClassInfo*> parents, const std::function<void*(const SpawnParams&)>& con )
//    :name(name), parent_classes(parents),constructor(con)
//    {
//        fe_classes.push_back(this);
//    }
    bool is_kind_of( const ClassInfo* another )
    {
        if ( this == another )
            return true;
        else
            for ( auto i : parent_classes )
                if ( i->is_kind_of( another ) )
                    return true;
        return false;
    }
    
    Name                                            name;
    std::vector<ClassInfo*>                         parent_classes;
    std::function<void*(const SpawnParams&)>        constructor;
};
}
#define CLASS_INFO_OF(classname) (&classname::classinfo)

#define DECLARE_CLASS_INFO(classname)\
static ClassInfo  classinfo;\
virtual ClassInfo* get_class_info(){ return &classname::classinfo; };

#define IMPLEMENT_CLASS_INFO(classname,parent_classes) ClassInfo classname::classinfo = {#classname,parent_classes,[](const SpawnParams& p){return new classname(p);}};



#endif
