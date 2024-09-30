#include "object.h"

void s21::Object::Parser(std::string path) {
std::ifstream my_file;
my_file.open(path);
std::cout<<"MYPATH:"<<path<<std::endl;
};