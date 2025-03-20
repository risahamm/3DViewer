#include "rotate_object.h"

void s21::RotateObject::Modify(double x, double y, double z) {
  double angle = (x == 0 ? y : x);
  angle = angle * M_PI / 180;

  for (Point &point : object_->GetVerticesRef()) {
    /* вращение вокруг оси X */
    if (x == 0) {
      RotateAxis(angle, point.y, point.z);

      /* вращение вокруг оси Y */
    } else if (y == 0) {
      RotateAxis(angle, point.x, point.z);

      /* вращение вокруг оси Z */
    } else if (z == 0) {
      RotateAxis(angle, point.x, point.y);
    }
  }
}

void s21::RotateObject::RotateAxis(double angle, double &coord_a,
                                   double &coord_b) {
  double temp_a = coord_a;
  double temp_b = coord_b;

  coord_a = (temp_a * cos(angle)) + (temp_b * (-(sin(angle))));
  coord_b = (temp_a * sin(angle)) + (temp_b * cos(angle));
}
