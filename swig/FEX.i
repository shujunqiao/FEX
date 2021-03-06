%module (directors="1") FEX
%{
#include "FE.h"
#include "FEUtility.h"
#include "ClassInfo.h"
#include "GameObjBase.h"
#include "SpriteBase.h"
#include "GameBase.h"
#include "LevelBase.h"
#include "SpriteComponent.h"
#include "ControllerBase.h"
#include "TouchController.h"
#include "cocos2d.h"
#include "ResourceManager.h"

%}

%feature("director:except") {
    if( $error != NULL ) {
        fprintf(stderr,"director exception:");
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch( &ptype, &pvalue, &ptraceback );
        PyErr_Restore( ptype, pvalue, ptraceback );
        PyErr_Print();
        Py_Exit(1);
    }
}

%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"
%ignore FESimple::SharedReourceMap;

namespace std
{
    template<typename T>
    class shared_ptr
    {
    };
    template<typename T>
    class weak_ptr
    {
    };
    template<typename T>
    class unique_ptr
    {
    };
    
}

%template(vector_sprite_components) std::vector<FESimple::SpriteComponent*>;
%template(map_string_string) std::map<std::string, std::string>;
%template(vector_controller) std::vector<FESimple::ControllerBase*>;
%template(gameobj_ptr)  std::shared_ptr<FESimple::GameObjBase>;
%template(sprite_component_desc_ptr) std::shared_ptr<FESimple::sprite_component_desc>;
%template(spritebase_ptr) std::shared_ptr< FESimple::SpriteBase >;
%template(spritebase_weak_ptr) std::weak_ptr< FESimple::SpriteBase >;


%feature("director") FESimple::GameBase;
%feature("director") FESimple::GameObjBase;
%feature("director") FESimple::SpriteBase;
%feature("director") FESimple::LevelBase;
%feature("director") FESimple::TouchController;
%feature("ref") FESimple::SpriteComponent "$this->retain (); // unref for SpriteComponent"
%feature("unref") FESimple::SpriteComponent "$this->release(); // unref for SpriteComponent"
//
///* Convert from C --> Python */
//%typemap(out) FESimple::GameObjBase*
//{
//    //nimei start
//    Swig::Director* director;
//    if ( (director = dynamic_cast<Swig::Director*>($1)) )
//    {
//        printf("this is directored gob\n");
// 
//        $result = director->swig_get_self();
//    }
//    else
//    {
//        $result = SWIG_NewPointerObj( SWIG_as_voidptr($1), SWIGTYPE_p_FESimple__GameObjBase, 0 );
//    }
//    //nimei end
//}
//
%typemap(out) std::weak_ptr<FESimple::SpriteBase>
{
    //nimei start
    Swig::Director* director;
    FESimple::SpriteBase* p = ($1).lock().get();
    if ( (director = dynamic_cast<Swig::Director*>(p)) )
    {
        printf("this is directored SpriteBase weakptr\n");
        $result = director->swig_get_self();
    }
    else
    {
        $result = SWIG_NewPointerObj( SWIG_as_voidptr(($1).lock().get()), SWIGTYPE_p_FESimple__SpriteBase, SWIG_POINTER_OWN | 0 );
    }
    //nimei end
}

%typemap(out) std::shared_ptr<FESimple::SpriteBase>
{
    //nimei start
    Swig::Director* director;
    FESimple::SpriteBase* p = ($1).get();
    if ( (director = dynamic_cast<Swig::Director*>(p)) )
    {
        printf("this is directored SpriteBase sharedptr\n");        
        $result = director->swig_get_self();
    }
    else
    {
        $result = SWIG_NewPointerObj( SWIG_as_voidptr(($1).get()), SWIGTYPE_p_FESimple__SpriteBase, SWIG_POINTER_OWN | 0 );
    }
    //nimei end
}

namespace cocos2d
{
    
    class  CCPoint
    {
    public:
        float x;
        float y;
        
    public:
        CCPoint();
        CCPoint(float x, float y);
        CCPoint(const CCPoint& other);
//ignored by swig        CCPoint& operator= (const CCPoint& other);
        void setPoint(float x, float y);
        bool equals(const CCPoint& target) const;
    };
    
    class  CCSize
    {
    public:
        float width;
        float height;
        
    public:
        CCSize();
        CCSize(float width, float height);
        CCSize(const CCSize& other);
//ignored by swig        CCSize& operator= (const CCSize& other);
        void setSize(float width, float height);
        bool equals(const CCSize& target) const;
    };
    
    class  CCRect
    {
    public:
        CCPoint origin;
        CCSize  size;
        
    public:
        CCRect();
        CCRect(float x, float y, float width, float height);
        CCRect(const CCRect& other);
//ignored by swig        CCRect& operator= (const CCRect& other);
        void setRect(float x, float y, float width, float height);
        float getMinX() const; /// return the leftmost x-value of current rect
        float getMidX() const; /// return the midpoint x-value of current rect
        float getMaxX() const; /// return the rightmost x-value of current rect
        float getMinY() const; /// return the bottommost y-value of current rect
        float getMidY() const; /// return the midpoint y-value of current rect
        float getMaxY() const; /// return the topmost y-value of current rect
        bool equals(const CCRect& rect) const;
        bool containsPoint(const CCPoint& point) const;
        bool intersectsRect(const CCRect& rect) const;
    };
    
    
    
    class CCTouch : public CCObject
    {
    public:
        CCTouch()
        : m_nId(0),
        m_startPointCaptured(false)
        {}
        
        /** returns the current touch location in OpenGL coordinates */
        CCPoint getLocation() const;
        /** returns the previous touch location in OpenGL coordinates */
        CCPoint getPreviousLocation() const;
        /** returns the start touch location in OpenGL coordinates */
        CCPoint getStartLocation() const;
        /** returns the delta of 2 current touches locations in screen coordinates */
        CCPoint getDelta() const;
        /** returns the current touch location in screen coordinates */
        CCPoint getLocationInView() const;
        /** returns the previous touch location in screen coordinates */
        CCPoint getPreviousLocationInView() const;
        /** returns the start touch location in screen coordinates */
        CCPoint getStartLocationInView() const;
        
        void setTouchInfo(int id, float x, float y)
        {
            m_nId = id;
            m_prevPoint = m_point;
            m_point.x   = x;
            m_point.y   = y;
            if (!m_startPointCaptured)
            {
                m_startPoint = m_point;
                m_startPointCaptured = true;
            }
        }
        
        int getID() const
        {
            return m_nId;
        }
        
    private:
        int m_nId;
        bool m_startPointCaptured;
        CCPoint m_startPoint;
        CCPoint m_point;
        CCPoint m_prevPoint;
    };
}

%extend cocos2d::CCPoint
{
    cocos2d::CCPoint operator - (const cocos2d::CCPoint& other )
    {
        return cocos2d::CCPoint( $self->x - other.x, $self->y - other.y);
    }
    cocos2d::CCPoint operator + (const cocos2d::CCPoint& other )
    {
        return cocos2d::CCPoint( $self->x + other.x, $self->y + other.y);
    }
    
}



%include "../FEX/FE.h"
%include "../FEX/ClassInfo.h"
%include "../FEX/GameObjBase.h"
%include "../FEX/SpriteBase.h"
%include "../FEX/GameBase.h"
%include "../FEX/LevelBase.h"
%include "../FEX/FEUtility.h"
%include "../FEX/GameObjFactory.h"
%include "../FEX/ControllerBase.h"
%include "../FEX/TouchController.h"
%include "../FEX/SpriteComponent.h"
%include "../FEX/ResourceManager.h"

