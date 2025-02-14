#include "Model/object.h"
#include "Controller/controller.h"
#include "Model/Transformations/move_object.h"
#include "Model/Transformations/transformations.h"
#include "Model/Transformations/zoom_object.h"

using namespace std;

int main() {

  s21::Object obj;
  s21::Controller controller(&obj);

  controller.OpenFile("../../object_files/cube.obj");
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

  if (correct == res) {
    cout << "true \n";
  } else {
    cout << "false \n";
  }

  return 0;
}

// clang-format -style=Google -i *.cc *.h


