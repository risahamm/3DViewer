#include "object.h"

using namespace std;

int main() {
  string str = "/Users/kattiede/CLionProjects/3DViewer/src/object_files/test21.obj";
  s21::Object Obj;
  Obj.Parser(str);
  Obj.PrintVertices();
  Obj.PrintFacets();

  return 0;
}

// clang-format -style=Google -i *.cc *.h


