#ifndef MKSTOPIXEL_H_
#define MKSTOPIXEL_H_

#include <Box2D/Box2D.h>

// Box2D measures angles counter-clockwise, and SDL does it clockwise
// Shove in a -1 factor to account for that
const float RADIANS_TO_DEGREES_FACTOR = (-1) * 360.0 / (2 * 3.1415);

b2Vec2 MKStoPixelTransform(const b2Vec2& vector);

#endif //MKSTOPIXEL_H_
