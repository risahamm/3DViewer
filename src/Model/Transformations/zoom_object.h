#ifndef VIEWER_SRC_MODEL_TRANSFORMATIONS_ZOOM_OBJECT_H
#define VIEWER_SRC_MODEL_TRANSFORMATIONS_ZOOM_OBJECT_H

#include "transformations.h"

namespace s21 {
  class ZoomObject : public TransformationsBaseClass {

  public:

    ZoomObject(s21::Object *obj) : TransformationsBaseClass(obj) {};
    ~ZoomObject() = default;

    void Modify(double x, double y, double z) override;

  };
} // namespace s21

#endif  // VIEWER_SRC_MODEL_TRANSFORMATIONS_ZOOM_OBJECT_H
