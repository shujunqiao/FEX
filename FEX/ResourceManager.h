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

struct LevelData;
template<class T>
class SharedReourceMap : public std::map<Name,std::shared_ptr<T> >
{
public:
    std::shared_ptr<T> item(const Name& name)
    {
        auto it = this->find(name);
        if ( it != this->end() )
            return it->second;
        else
        {
            cout << "item: \"" << name << "\" not found.!" << endl;
            return std::shared_ptr<T>();
        }
    }
};

class ResourceManager
{
public:
    static ResourceManager* instance();
    
    void load_sprite_desc( const std::string& filename );
    void load_physic_desc( const std::string& filename );
    void load_sprite_component_desc( const std::string& filename );
    std::shared_ptr<LevelData> get_level_data( const std::string& filename );
    
    SharedReourceMap<sprite_desc>              sprite_descs;
    SharedReourceMap<physic_desc>              physic_descs;
    SharedReourceMap<sprite_component_desc>    sprite_components;
    SharedReourceMap<animation>                animations;
    SharedReourceMap<LevelData>                levels;
};
FE_NS_END

#endif /* defined(__FEX__ResourceManager__) */
