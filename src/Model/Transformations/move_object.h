#ifndef VIEWER_MOVE_OBJECT_H
#define VIEWER_MOVE_OBJECT_H

#include "transformations.h"

namespace s21 {
  class MoveObject : public TransformationsBaseClass {

  public:

    MoveObject(s21::Object *obj) : TransformationsBaseClass(obj) {};
    ~MoveObject() = default;

    void Modify(double x, double y, double z) override;

  };

} // namespace s21

#endif  // VIEWER_MOVE_OBJECT_H
