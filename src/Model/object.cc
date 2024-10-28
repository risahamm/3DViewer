#include "object.h"

void s21::Object::Parser(std::string path) {
  std::ifstream my_file;
  my_file.open(path);
  if (!my_file.is_open()) {
    std::cout << "File is not opened" << std::endl;  // TODO throw exception
  } else {
    //    std::cout << "MYPATH:" << path << std::endl;
    std::string str;
    while (!my_file.eof()) {
      std::getline(my_file, str, '\n');
      std::string::const_iterator ch = str.cbegin();
      while (ch != str.end()) {  // TODO starts_with
        if (*ch == 'v') {
          if (*(++ch) == ' ') {
            ReadVertex(str);
          }
        }
        break;
        if (*ch == 'f') {  // TODO starts_with
          if (*(++ch) == ' ') {
//              ReadFacet(str);
          }
        }
      }
//        break;
    }
  }  // file is opened
};

void s21::Object::ReadVertex(std::string &str) {
//  std::string::const_iterator ch = str.cbegin() + 2;
  //    const char *newstr = str.c_str();
  std::string sub2 = str.substr(2);
  std::istringstream iss(sub2);
  //    int i = 0; // счетчик элементов структуры Point
  Point point1;
  if (iss >> point1.x >> point1.y >> point1.z) {
    vertex_.push_back(point1);
  }



  for (Point i : vertex_) {
      int number = 0;
    std::cout << "VERTEX_ number:" << number << i.x << " " << i.y << " " << i.z << std::endl;
    number++;
  }
}