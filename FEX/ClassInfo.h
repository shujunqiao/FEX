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
FE_NS_BEGIN

typedef void* ( *CONSTRUCTOR_FUNC )();
class ClassInfo
{
public:
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
    
    Name                    name;
    std::vector<ClassInfo*>	parent_classes;
    CONSTRUCTOR_FUNC		construct;
};

//static std::map<std::string, ClassInfo> Factory;
//
//template<typename c >
//class ClassRegister
//{
//public:
//    void reg( const std::string& name )
//    {
//        Factory[name] = c::static_classinfo;
//    }
//};

#define DEFINE_PARENT_CLASS( childclass, parentclass ) childclass::get_classinfo()->parent_classes.push_back(parentclass::get_classinfo());
#define DECLAR_CLASS( classname )\
static std::shared_ptr<classname> construct( const SpawnParams& params){ return std::shared_ptr(new classname( params )); }\
static ClassInfo	static_classinfo;
//void bind_classinfo() { classinfo = &classname::static_classinfo; }\


#define DECLAR_ABSTRACTL_CLASS( classname )\
public:\
static classinfo*	get_classinfo(){ return &classname::static_classinfo; }\
void bind_classinfo() { classinfo = &classname::static_classinfo; }\
private:\
static classinfo	static_classinfo;

#define CLASS_CONSTRUCTOR_INCLUDE( classname )\
bind_classinfo();\
m_id = classname::static_classinfo.name;

#define	REGISTER_CLASS( classname )\
classname::get_classinfo()->name = _T(#classname);\
classname::get_classinfo()->construct = ((CONSTRUCTOR_FUNC)(classname::constructor));

#define DEFINE_PTR(classname)	typedef std::shared_ptr<classname> classname##_ptr;

#define IMPLEMENT_CLASS( classname ) classinfo classname::static_classinfo;

FE_NS_END

#endif
