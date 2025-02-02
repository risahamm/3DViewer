#ifndef VIEWER_ZOOM_OBJECT_H
#define VIEWER_ZOOM_OBJECT_H

#include "transformations.h"

class ZoomObject : public TransformationsBaseClass {

 public:

  ZoomObject(s21::Object *obj) : TransformationsBaseClass(obj) {};

  void Modify(double x, double y, double z) override;

};

#endif  // VIEWER_ZOOM_OBJECT_H
