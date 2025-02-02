#include <gtest/gtest.h>
#include "../object.h"
#include "../Transformations/move_object.h"
#include "../Transformations/transformations.h"
#include "../Transformations/zoom_object.h"

/* MOVE TRANSFORMATIONS */

s21::Object obj;
s21::Controller controller(&obj);

TEST(move, move_right) {

  controller.OpenFile("../../object_files/cube.obj");
  controller.MoveXRight(2);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(2, 2, 0);
  s21::Point b(2, 0, 0);
  s21::Point c(2, 2, 2);
  s21::Point d(2, 0, 2);
  s21::Point e(0, 2, 0);
  s21::Point f(0, 0, 0);
  s21::Point g(0, 2, 2);
  s21::Point h(0, 0, 2);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h};
  EXPECT_EQ(res == correct);
}
