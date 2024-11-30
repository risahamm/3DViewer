#include "object.h"

using namespace std;

int main() {
//  string str = "/Users/risahamm/projects/3DViewer/src/object_files/teapot.obj";
////  string str = "../../object_files/test_cube.obj";
//  s21::Object Obj;
//  Obj.Parser(str);
//  Obj.PrintFacets();

  string vertex_str = "8854/23";

  size_t pos = vertex_str.find('/'); // || vertex_str.find(' ');

  std::cout << "pos = " << pos << endl;

  return 0;
}

// clang-format -style=Google -i *.cc *.h


