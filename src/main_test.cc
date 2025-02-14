#include "Model/object.h"
#include "Controller/controller.h"

using namespace std;

int main() {

  s21::Object obj;
  s21::Controller controller(&obj);

  controller.OpenFile("../../object_files/cube.obj");
  controller.ZoomOut(2);
  std::vector<s21::Point> res = controller.getVertices();
  s21::Point a(0, 0, 0);
  s21::Point b(0.5, 0.5,-0.5);
  s21::Point c(0.5, -0.5, -0.5);
  s21::Point d(0.5, 0.5, 0.5);
  s21::Point e(0.5, -0.5, 0.5);
  s21::Point f(-0.5, 0.5, -0.5);
  s21::Point g(-0.5, -0.5, -0.5);
  s21::Point h(-0.5, 0.5, 0.5);
  s21::Point i(-0.5, -0.5, 0.5);
  std::vector<s21::Point> correct = {a, b, c, d, e, f, g, h, i};

  if (correct == res) {
    cout << "true \n";
  } else {
    cout << "false \n";
  }

  return 0;
}

// clang-format -style=Google -i *.cc *.h


