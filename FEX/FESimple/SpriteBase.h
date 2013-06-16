//
//  SpriteBase.h
//  FEX
//
//  Created by Fancyzero on 13-6-9.
//
//

#ifndef __FEX__SpriteBase__
#define __FEX__SpriteBase__

#include "FE.h"
#include "GameObjBase.h"
#include <vector>
#include <memory>
#include "Box2D.h"
#include "SpriteComponent.h"

FE_NS_BEGIN
class SpriteComponent;

class SpriteBase :public GameObjBase
{
public:
    SpriteBase();
    SpriteBase( const std::shared_ptr<sprite_desc> desc );
    ~SpriteBase();
    
    virtual void added_to_game( GameBase* game, const Name& to_layer );
    virtual void removed_from_game( GameBase* game );
    
    //components management
    void add_component( SpriteComponent* );
    void remove_component( SpriteComponent * );
    SpriteComponent* get_component( unsigned int index );
    
    
    
    //position , rotation, ect..
    void set_position( CCPoint pos );
    void set_rotation( float angle );
protected:
    std::vector< SpriteComponent* > components;
};
FE_NS_END

#endif /* defined(__FEX__SpriteBase__) */
