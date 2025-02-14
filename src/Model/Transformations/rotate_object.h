#ifndef ROTATEOBJECT_H
#define ROTATEOBJECT_H

#include "transformations.h"

namespace s21 {
  class RotateObject : public TransformationsBaseClass {

  public:

    RotateObject(s21::Object *obj) : TransformationsBaseClass(obj) {};
    ~RotateObject() = default;

    void Modify(double x, double y, double z) override;

  };

} // s21

#endif // ROTATEOBJECT_H
