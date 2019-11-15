#ifndef CONTACTLISTENER_H_
#define CONTACTLISTENER_H_

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener {

public:
  ContactListener();
  virtual void BeginContact(b2Contact* contact);
  virtual void EndContact(b2Contact* contact);
};

#endif    // CONTACTLISTENER_H_
