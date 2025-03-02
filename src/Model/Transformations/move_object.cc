#include "move_object.h"

void s21::MoveObject::Modify(double x, double y, double z) {
//  for (Point &point : object_->GetVerticesRef()) {
//    point.x += x;
//    point.y += y;
//    point.z += z;
//  }

  int size = object_->GetVertexCount();

  for (int i = 0; i <= size; i++) {
    object_->GetVerticesRef()[i].x += x;
    object_->GetVerticesRef()[i].y += y;
    object_->GetVerticesRef()[i].z += z;

    object_->GetInitialVeritcesRef()[i].x += x;
    object_->GetInitialVeritcesRef()[i].y += y;
    object_->GetInitialVeritcesRef()[i].z += z;
  }

  //  object_->setInitialVertices();
}