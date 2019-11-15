#include "ContactListener.h"
#include "Contactable.h"

ContactListener::ContactListener() : b2ContactListener(){

}

void ContactListener::BeginContact(b2Contact* contact){
  auto contactableA = (Contactable*) contact->GetFixtureA()->GetBody()->GetUserData();
  auto contactableB = (Contactable*) contact->GetFixtureB()->GetBody()->GetUserData();
  contactableA->Contact(contactableB);
  contactableB->Contact(contactableA);
}


void ContactListener::EndContact(b2Contact* contact){}
