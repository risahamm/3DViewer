#include "Controller/controller.h"

using namespace std;

int main() {

  s21::Object obj;
  s21::Controller controller(&obj);

  /*bool result = */controller.OpenFile("../../object_files/cube.obj");
   controller.Zoom(0.5);
   controller.MoveXRight(2);
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

  obj.PrintVertices();
  obj.PrintFacets();

   if (correct == res) {
     cout << "true \n";
   } else {
     cout << "false \n";
   }

//  cout << "result = " << result;
  return 0;
}

// clang-format -style=Google -i *.cc *.h


