#include <gtest/gtest.h>

#include "../../Controller/controller.h"

#define LIMIT 1e-7

/* FLAWED DATA HANDLING */

s21::Object obj;
s21::Controller controller(&obj);

TEST(open_file, non_existent_file) {
  EXPECT_FALSE(controller.OpenFile("nonexistent_file.obj"));
}

TEST(read_obj, non_centered) {
  controller.OpenFile("object_files/non_central_cube.obj");
  std::vector<s21::Point> res = controller.GetVertices();
  s21::Point a(-1, -3, 5);
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

TEST(read_facet, negative_vertices) {
  controller.OpenFile("object_files/neg_cube.obj");
  std::vector<s21::Point> res = controller.GetVertices();
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

// TEST(read_facet, no_such_pos_idx) {
//   EXPECT_FALSE(controller.OpenFile("object_files/no_such_pos_index.obj"));
// }

TEST(read_facet, no_such_neg_idx) {
  EXPECT_TRUE(controller.OpenFile("object_files/no_such_neg_index.obj"));
}

TEST(read_facet, many_indexes) {
  EXPECT_TRUE(controller.OpenFile("object_files/many_indexes.obj"));
}

// TEST(read_facet, no_vertex) {
//   EXPECT_FALSE(controller.OpenFile("object_files/no_vertex.obj"));
// }

TEST(read_facet, flawed_facet) {
  controller.OpenFile("object_files/no_facet.obj");
  std::vector<s21::Point> res = controller.GetVertices();
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

/* MOVE TRANSFORMATIONS */

TEST(move, move_right) {
  controller.OpenFile("object_files/cube.obj");
  controller.MoveXRight(2);
  std::vector<s21::Point> res = controller.GetVertices();
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
  std::vector<s21::Point> res = controller.GetVertices();
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
  std::vector<s21::Point> res = controller.GetVertices();
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
  std::vector<s21::Point> res = controller.GetVertices();
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
  std::vector<s21::Point> res = controller.GetVertices();
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
  std::vector<s21::Point> res = controller.GetVertices();
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

TEST(move, move_and_zoom) {
  controller.OpenFile("object_files/cube.obj");
  controller.MoveXRight(5);
  controller.Zoom(0.5);
  std::vector<s21::Point> res = controller.GetVertices();
  s21::Point a(2.5, 0, 0);
  s21::Point b(3, 0.5, -0.5);
  s21::Point c(3, -0.5, -0.5);
  s21::Point d(3, 0.5, 0.5);
  s21::Point e(3, -0.5, 0.5);
  s21::Point f(2, 0.5, -0.5);
  s21::Point g(2, -0.5, -0.5);
  s21::Point h(2, 0.5, 0.5);
  s21::Point i(2, -0.5, 0.5);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

/* ZOOM TRANSFORMATIONS */

TEST(zoom, zoom_in) {
  controller.OpenFile("object_files/cube.obj");
  controller.Zoom(2);
  std::vector<s21::Point> res = controller.GetVertices();
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
  std::vector<s21::Point> res = controller.GetVertices();
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

TEST(zoom, zoom_by_zero) {
  controller.OpenFile("object_files/cube.obj");
  controller.Zoom(0);
  std::vector<s21::Point> res = controller.GetVertices();
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

TEST(zoom, zoom_and_move) {
  controller.OpenFile("object_files/cube.obj");
  controller.Zoom(0.5);
  controller.MoveXRight(2);
  std::vector<s21::Point> res = controller.GetVertices();
  s21::Point a(2, 0, 0);
  s21::Point b(2.5, 0.5, -0.5);
  s21::Point c(2.5, -0.5, -0.5);
  s21::Point d(2.5, 0.5, 0.5);
  s21::Point e(2.5, -0.5, 0.5);
  s21::Point f(1.5, 0.5, -0.5);
  s21::Point g(1.5, -0.5, -0.5);
  s21::Point h(1.5, 0.5, 0.5);
  s21::Point i(1.5, -0.5, 0.5);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(rotate, rotate_left) {
  controller.OpenFile("object_files/cube.obj");
  controller.RoateYLeft(90);
  std::vector<s21::Point> res = controller.GetVertices();
  s21::Point a(0, 0, 0);
  s21::Point b(1, 1, 0.99999999999999988);
  s21::Point c(1, -1, 0.99999999999999988);
  s21::Point d(-0.99999999999999988, 1, 1);
  s21::Point e(-0.99999999999999988, -1, 1);
  s21::Point f(0.99999999999999988, 1, -1);
  s21::Point g(0.99999999999999988, -1, -1);
  s21::Point h(-1, 1, -0.99999999999999988);
  s21::Point i(-1, -1, -0.99999999999999988);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(rotate, rotate_right) {
  controller.OpenFile("object_files/cube.obj");
  controller.RoateYRight(90);
  std::vector<s21::Point> res = controller.GetVertices();
  s21::Point a(0, 0, 0);
  s21::Point b(-0.99999999999999988, 1, -1);
  s21::Point c(-0.99999999999999988, -1, -1);
  s21::Point d(1, 1, -0.99999999999999988);
  s21::Point e(1, -1, -0.99999999999999988);
  s21::Point f(-1, 1, 0.99999999999999988);
  s21::Point g(-1, -1, 0.99999999999999988);
  s21::Point h(0.99999999999999988, 1, 1);
  s21::Point i(0.99999999999999988, -1, 1);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(rotate, rotate_up) {
  controller.OpenFile("object_files/cube.obj");
  controller.RoateXUp(90);
  std::vector<s21::Point> res = controller.GetVertices();
  s21::Point a(0, 0, 0);
  s21::Point b(1, -0.99999999999999988, -1);
  s21::Point c(1, -1, 0.99999999999999988);
  s21::Point d(1, 1, -0.99999999999999988);
  s21::Point e(1, 0.99999999999999988, 1);
  s21::Point f(-1, -0.99999999999999988, -1);
  s21::Point g(-1, -1, 0.99999999999999988);
  s21::Point h(-1, 1, -0.99999999999999988);
  s21::Point i(-1, 0.99999999999999988, 1);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(rotate, rotate_down) {
  controller.OpenFile("object_files/cube.obj");
  controller.RoateXDown(90);
  std::vector<s21::Point> res = controller.GetVertices();
  s21::Point a(0, 0, 0);
  s21::Point b(1, 1, 0.99999999999999988);
  s21::Point c(1, 0.99999999999999988, -1);
  s21::Point d(1, -0.99999999999999988, 1);
  s21::Point e(1, -1, -0.99999999999999988);
  s21::Point f(-1, 1, 0.99999999999999988);
  s21::Point g(-1, 0.99999999999999988, -1);
  s21::Point h(-1, -0.99999999999999988, 1);
  s21::Point i(-1, -1, -0.99999999999999988);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(rotate, rotate_clockwise) {
  controller.OpenFile("object_files/cube.obj");
  controller.RoateZClckWs(90);
  std::vector<s21::Point> res = controller.GetVertices();
  s21::Point a(0, 0, 0);
  s21::Point b(1, -0.99999999999999988, -1);
  s21::Point c(-0.99999999999999988, -1, -1);
  s21::Point d(1, -0.99999999999999988, 1);
  s21::Point e(-0.99999999999999988, -1, 1);
  s21::Point f(0.99999999999999988, 1, -1);
  s21::Point g(-1, 0.99999999999999988, -1);
  s21::Point h(0.99999999999999988, 1, 1);
  s21::Point i(-1, 0.99999999999999988, 1);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}

TEST(rotate, rotate_counter_clockwise) {
  controller.OpenFile("object_files/cube.obj");
  controller.RoateZCClckWs(90);
  std::vector<s21::Point> res = controller.GetVertices();
  s21::Point a(0, 0, 0);
  s21::Point b(-0.99999999999999988, 1, -1);
  s21::Point c(1, 0.99999999999999988, -1);
  s21::Point d(-0.99999999999999988, 1, 1);
  s21::Point e(1, 0.99999999999999988, 1);
  s21::Point f(-1, -0.99999999999999988, -1);
  s21::Point g(0.99999999999999988, -1, -1);
  s21::Point h(-1, -0.99999999999999988, 1);
  s21::Point i(0.99999999999999988, -1, 1);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};
  EXPECT_TRUE(res == correct);
}