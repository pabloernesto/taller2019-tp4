#include "ContactListener.h"

ContactListener::ContactListener() : b2ContactListener(){

}

void ContactListener::BeginContact(b2Contact* contact){
  //auto data = contact->GetFixtureA()->GetBody()->GetUserData();
  
}


void ContactListener::EndContact(b2Contact* contact){
  
}