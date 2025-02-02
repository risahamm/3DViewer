#ifndef VIEWER_TRANSFORMATIONS_H
#define VIEWER_TRANSFORMATIONS_H

#include "../object.h"

namespace s21 {

  class TransformationsBaseClass {

   public:

    TransformationsBaseClass(s21::Object *obj = nullptr) : object_(obj) {};
    virtual ~TransformationsBaseClass() = default;

    virtual void Modify(double x, double y, double z) = 0;

   protected:

    s21::Object *object_;

  };

} // namespace s21

#endif  // VIEWER_TRANSFORMATIONS_H

