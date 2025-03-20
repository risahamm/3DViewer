#include "zoom_object.h"

void s21::ZoomObject::Modify(double x, double y, double z) {
  for (Point &point : object_->GetVerticesRef()) {
    point.x *= x;
    point.y *= y;
    point.z *= z;
  }
}
