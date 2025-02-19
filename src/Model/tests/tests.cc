#include <gtest/gtest.h>

#include "../../Controller/controller.h"

/* MOVE TRANSFORMATIONS */

s21::Object obj;
s21::Controller controller(&obj);

TEST(Mytest, Move_right) {
  controller.OpenFile("object_files/cube.obj");
  controller.MoveXRight(2);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(2, 0, 0);
  s21::Point b(3, 1, -1);
  s21::Point c(3, -1, -1);
  s21::Point d(3, 1, 1);
  s21::Point e(3, -1, 1);
  s21::Point f(1, 1, -1);
  s21::Point g(1, -1, -1);
  s21::Point h(1, 1, 1);
  s21::Point i(1, -1, 1);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(move, move_left) {
  controller.OpenFile("object_files/cube.obj");
  controller.MoveXLeft(2);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(-2, 0, 0);
  s21::Point b(-1, 1, -1);
  s21::Point c(-1, -1, -1);
  s21::Point d(-1, 1, 1);
  s21::Point e(-1, -1, 1);
  s21::Point f(-3, 1, -1);
  s21::Point g(-3, -1, -1);
  s21::Point h(-3, 1, 1);
  s21::Point i(-3, -1, 1);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(move, move_up) {
  controller.OpenFile("object_files/cube.obj");
  controller.MoveYUp(5);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(0, 5, 0);
  s21::Point b(1, 6, -1);
  s21::Point c(1, 4, -1);
  s21::Point d(1, 6, 1);
  s21::Point e(1, 4, 1);
  s21::Point f(-1, 6, -1);
  s21::Point g(-1, 4, -1);
  s21::Point h(-1, 6, 1);
  s21::Point i(-1, 4, 1);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(move, move_down) {
  controller.OpenFile("object_files/cube.obj");
  controller.MoveYDown(5);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(0, -5, 0);
  s21::Point b(1, -4, -1);
  s21::Point c(1, -6, -1);
  s21::Point d(1, -4, 1);
  s21::Point e(1, -6, 1);
  s21::Point f(-1, -4, -1);
  s21::Point g(-1, -6, -1);
  s21::Point h(-1, -4, 1);
  s21::Point i(-1, -6, 1);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(move, move_front) {
  controller.OpenFile("object_files/cube.obj");
  controller.MoveZForward(5);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(0, 0, 5);
  s21::Point b(1, 1, 4);
  s21::Point c(1, -1, 4);
  s21::Point d(1, 1, 6);
  s21::Point e(1, -1, 6);
  s21::Point f(-1, 1, 4);
  s21::Point g(-1, -1, 4);
  s21::Point h(-1, 1, 6);
  s21::Point i(-1, -1, 6);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(move, move_back) {
  controller.OpenFile("object_files/cube.obj");
  controller.MoveZBackward(5);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(0, 0, -5);
  s21::Point b(1, 1, -6);
  s21::Point c(1, -1, -6);
  s21::Point d(1, 1, -4);
  s21::Point e(1, -1, -4);
  s21::Point f(-1, 1, -6);
  s21::Point g(-1, -1, -6);
  s21::Point h(-1, 1, -4);
  s21::Point i(-1, -1, -4);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

/* ZOOM TRANSFORMATIONS */

TEST(zoom, zoom_in) {
  controller.OpenFile("object_files/cube.obj");
  controller.Zoom(2);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(0, 0, 0);
  s21::Point b(2, 2, -2);
  s21::Point c(2, -2, -2);
  s21::Point d(2, 2, 2);
  s21::Point e(2, -2, 2);
  s21::Point f(-2, 2, -2);
  s21::Point g(-2, -2, -2);
  s21::Point h(-2, 2, 2);
  s21::Point i(-2, -2, 2);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(zoom, zoom_out_1) {
  controller.OpenFile("object_files/cube.obj");
  controller.Zoom(0.5);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(0, 0, 0);
  s21::Point b(0.5, 0.5, -0.5);
  s21::Point c(0.5, -0.5, -0.5);
  s21::Point d(0.5, 0.5, 0.5);
  s21::Point e(0.5, -0.5, 0.5);
  s21::Point f(-0.5, 0.5, -0.5);
  s21::Point g(-0.5, -0.5, -0.5);
  s21::Point h(-0.5, 0.5, 0.5);
  s21::Point i(-0.5, -0.5, 0.5);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(zoom, zoom_out_2) {
  controller.OpenFile("object_files/cube.obj");
  controller.Zoom(0);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(0, 0, 0);
  s21::Point b(1, 1, -1);
  s21::Point c(1, -1, -1);
  s21::Point d(1, 1, 1);
  s21::Point e(1, -1, 1);
  s21::Point f(-1, 1, -1);
  s21::Point g(-1, -1, -1);
  s21::Point h(-1, 1, 1);
  s21::Point i(-1, -1, 1);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}