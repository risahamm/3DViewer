#include "object.h"

using namespace std;

int main() {
//  string str = "/Users/kattiede/CLionProjects/3DViewer/src/object_files/test_cube.obj";
  string str = "../../object_files/test_cube.obj";
  s21::Object Obj;
  Obj.Parser(str);
  Obj.PrintVertices();
  Obj.PrintFacets();

  return 0;
}

// clang-format -style=Google -i *.cc *.h


