#ifndef VIEWER_SRC_MODEL_TRANSFORMATIONS_ROTATE_OBJECT_H
#define VIEWER_SRC_MODEL_TRANSFORMATIONS_ROTATE_OBJECT_H

#include "transformations.h"

namespace s21 {
  class RotateObject : public TransformationsBaseClass {

  public:

    RotateObject(s21::Object *obj) : TransformationsBaseClass(obj) {};
    ~RotateObject() = default;

    void Modify(double x, double y, double z) override;

  };

} // s21

#endif // VIEWER_SRC_MODEL_TRANSFORMATIONS_ROTATE_OBJECT_H
