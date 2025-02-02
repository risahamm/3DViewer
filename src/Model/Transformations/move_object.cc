#include "move_object.h"

void MoveObject::Modify(double x, double y, double z) {

  for (s21::Point &point : object_->getVertexRef()) {

    point.x += x;
    point.y += y;
    point.z += z;
  }
}