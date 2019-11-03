#include "ContactListener.h"

ContactListener::ContactListener() : b2ContactListener(){

}

void ContactListener::BeginContact(b2Contact* contact){
  //contact->GetFixtureA()->DecreaseLife();
}


void ContactListener::EndContact(b2Contact* contact){
  
}