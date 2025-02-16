#include "zoom_object.h"

void s21::ZoomObject::Modify(double x, double y, double z) {
  for (s21::Point &point : object_->getVerticesRef()) {
    point.x *= x;
    point.y *= y;
    point.z *= z;
  }
}
