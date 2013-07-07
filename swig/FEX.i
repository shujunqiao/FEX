%module FEX
%{
#include "FE.h"
#include "FEUtility.h"
#include "ClassInfo.h"
#include "GameObjBase.h"
#include "SpriteBase.h"
#include "GameBase.h"
#include "LevelBase.h"
%}
%define SWIG_ING
%enddef
%include "std_string.i"
%include "std_map.i"
%include "std_shared_ptr.i"
%template(map_string_string) std::map<std::string, std::string>;

%include "../FEX/FE.h"
%include "../FEX/ClassInfo.h"
%include "../FEX/GameObjBase.h"
%include "../FEX/SpriteBase.h"
%include "../FEX/GameBase.h"
%include "../FEX/LevelBase.h"
%include "../FEX/FEUtility.h"
%include "../FEX/GameObjFactory.h"
