#include "move_object.h"

void s21::MoveObject::Modify(double x, double y, double z) {
//  for (Point &point : object_->getVerticesRef()) {
//    point.x += x;
//    point.y += y;
//    point.z += z;
//  }

  int size = object_->getVertexCount();

  for (int i = 0; i <= size; i++) {
    object_->getVerticesRef()[i].x += x;
    object_->getVerticesRef()[i].y += y;
    object_->getVerticesRef()[i].z += z;

    object_->getInitialVeritcesRef()[i].x += x;
    object_->getInitialVeritcesRef()[i].y += y;
    object_->getInitialVeritcesRef()[i].z += z;
  }

  //  object_->setInitialVertices();
}