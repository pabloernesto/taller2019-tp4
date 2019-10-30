#ifndef MKSTOPIXEL_H_
#define MKSTOPIXEL_H_

#include <Box2D/Box2D.h>

const float RADIANS_TO_DEGREES_FACTOR = (-1) * 360.0 / (2 * 3.1415);

typedef struct {
  int x;
  int y;
} pixel_vect_s;

pixel_vect_s MKStoPixelTransform(const b2Vec2& vector);

#endif //MKSTOPIXEL_H_
