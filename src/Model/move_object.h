#ifndef VIEWER_MOVE_OBJECT_H
#define VIEWER_MOVE_OBJECT_H

#include "transformations.h"

class MoveObject : public TransformationsBaseClass {

 public:

  MoveObject(s21::Object *obj) : TransformationsBaseClass(obj) {};

  void Modify(double x, double y, double z) override;

};

#endif  // VIEWER_MOVE_OBJECT_H
