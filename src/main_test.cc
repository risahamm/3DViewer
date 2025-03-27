#include "Controller/controller.h"

using namespace std;

int main() {

  s21::Object obj;
  s21::Controller controller(&obj);

  bool result = controller.OpenFile("../../object_files/cube.obj");
  controller.RoateZCClckWs(90);
//   controller.MoveXRight(2);
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

//  obj.PrintVertices();
//  obj.PrintFacets();

//  cout << "ver 1 z = " << obj.GetVerticesRef().at(1).z << endl;

   if (correct == res) {
     cout << "true \n";
   } else {
     cout << "false \n";
   }

//  cout << "result = " << result;
  return 0;
}

// clang-format -style=Google -i *.cc *.h


