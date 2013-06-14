//
//  ResourceManager.h
//  FEX
//
//  Created by Fancyzero on 13-6-10.
//
//

#ifndef __FEX__ResourceManager__
#define __FEX__ResourceManager__

#include "FE.h"
#include <map>
#include "SpriteComponent.h"
FE_NS_BEGIN
template<class T>
class SharedReourceMap : public std::map<Name,std::shared_ptr<T>>
{
public:
    std::shared_ptr<T> item(const Name& name)
    {
        auto it = this->find(name);
        if ( it != this->end() )
            return it->second;
        else
            return std::shared_ptr<T>();
    }
};

class ResourceManager
{
public:
    static const std::shared_ptr<sprite_desc> get_sprite_desc( const Name& name );
    static const std::shared_ptr<physic_desc> get_physic_desc( const Name& name );
    static const std::shared_ptr<sprite_component_desc> get_sprite_component_desc( const Name& name );
    static const std::shared_ptr<animation> get_animation( const Name& name );
    static void load_sprite_desc( const std::string& filename );
    static void load_physic_desc( const std::string& filename );
    static void load_sprite_component_desc( const std::string& filename );

    static SharedReourceMap<sprite_desc>              m_sprite_descs;
    static SharedReourceMap<physic_desc>              m_physic_descs;
    static SharedReourceMap<sprite_component_desc>    m_sprite_components;
    static SharedReourceMap<animation>                m_animations;
};
FE_NS_END

#endif /* defined(__FEX__ResourceManager__) */
