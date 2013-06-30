//
//  CollisionListener.cpp
//  FEX
//
//  Created by Fancyzero on 13-6-29.
//
//

#include "CollisionListener.h"
#include "SpriteComponent.h"
#include "SpriteBase.h"
FE_NS_BEGIN

SpriteComponent* get_component( b2Fixture* fixture )
{
    if ( fixture and static_cast<FixtureUserData*>(fixture->GetUserData()) )
        return static_cast<FixtureUserData*> (fixture->GetUserData())->sprite_component;
}
SpriteComponent* get_componentB( b2Contact* contact );

void ContactListener::BeginContact(b2Contact* contact)
{
    SpriteComponent* c;
    c = get_component(contact->GetFixtureA());
    if ( c )
        c->begin_contact( contact );
    c = get_component(contact->GetFixtureB());
    if ( c )
        c->begin_contact( contact );
}

void ContactListener::EndContact(b2Contact* contact)
{
    SpriteComponent* c;
    c = get_component(contact->GetFixtureA());
    if ( c )
        c->end_contact( contact );
    c = get_component(contact->GetFixtureB());
    if ( c )
        c->end_contact( contact );
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}
FE_NS_END