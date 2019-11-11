#include "MKStoPixel.h"

#include <Box2D/Box2D.h>

static const int PIXELS_PER_METER = 30;

std::vector<float> MKStoPixelTransform(const std::vector<float>& vector) {
  std::vector<float> vectorPixel;
  vectorPixel.push_back(vector[0] * PIXELS_PER_METER);
  vectorPixel.push_back(vector[1] * PIXELS_PER_METER);
  return vectorPixel;
}
