#include "zoom_object.h"

void s21::ZoomObject::Modify(double x, double y, double z) {
  int size = object_->getVertexCount();

  for (int i = 0; i <= size; i++) {
    object_->getVerticesRef()[i].x = object_->getInitialVeritcesRef()[i].x * x;
    object_->getVerticesRef()[i].y = object_->getInitialVeritcesRef()[i].y * y;
    object_->getVerticesRef()[i].z = object_->getInitialVeritcesRef()[i].z * z;
  }
}
