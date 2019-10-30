#include "MKStoPixel.h"

#include <Box2D/Box2D.h>

static const int PIXELS_PER_METER = 100;
// Box2D measures angles counter-clockwise, and SDL does it clockwise
// Shove in a -1 factor to account for that

pixel_vect_s MKStoPixelTransform(const b2Vec2& vector) {
  pixel_vect_s v {
    (int)(PIXELS_PER_METER * vector.x),
    (int)(PIXELS_PER_METER * vector.y)
  };
  return v;
}
