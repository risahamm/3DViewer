#include "zoom_object.h"

void s21::ZoomObject::Modify(double x, double y, double z) {
  int size = object_->GetVertexCount();

  for (int i = 0; i <= size; i++) {
//    object_->GetVerticesRef()[i].x = object_->GetInitialVeritcesRef()[i].x * x;
//    object_->GetVerticesRef()[i].y = object_->GetInitialVeritcesRef()[i].y * y;
//    object_->GetVerticesRef()[i].z = object_->GetInitialVeritcesRef()[i].z * z;

    object_->GetVerticesRef()[i].x *= x;
    object_->GetVerticesRef()[i].y *= y;
    object_->GetVerticesRef()[i].z *= z;
  }
}
