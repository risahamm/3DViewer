#include "object.h"
#include <iostream>
using namespace std;

int main() {
    string str = "../object_files/cube.obj";
    s21::Object Obj;
    Obj.Parser(str);
}