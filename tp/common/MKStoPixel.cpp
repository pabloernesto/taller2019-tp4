#include "MKStoPixel.h"

#include <Box2D/Box2D.h>

static const int PIXELS_PER_METER = 50;

b2Vec2 MKStoPixelTransform(const b2Vec2& vector) {
  return PIXELS_PER_METER * vector;
}
