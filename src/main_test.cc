#include "Model/object.h"

using namespace std;

int main() {
//  string str = "/Users/risahamm/projects/3DViewer/src/object_files/teapot.obj";
////  string str = "../../object_files/test_cube.obj";
//  s21::Object Obj;
//  Obj.Parser(str);
//  Obj.PrintFacets();

  string vertex_str = "-dhjljlk";

  int vertex_number = stoi(vertex_str);

//  size_t pos = vertex_str.find('/'); // || vertex_str.find(' ');

//  size_t pos_slash = vertex_str.find('/');
//  size_t pos_space = vertex_str.find(' ');
//
//  // Находим первый разделитель
//  size_t pos = std::min(pos_slash, pos_space);
//
  std::cout << "vertex_number = " << vertex_number << endl;

  return 0;
}

// clang-format -style=Google -i *.cc *.h


