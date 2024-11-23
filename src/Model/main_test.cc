#include "object.h"

using namespace std;

int main() {
  string str = "/Users/risahamm/projects/3DViewer/src/object_files/teapot.obj";
//  string str = "../../object_files/test_cube.obj";
  s21::Object Obj;
  Obj.Parser(str);
//  Obj.PrintFacets();

  return 0;
}

// clang-format -style=Google -i *.cc *.h


