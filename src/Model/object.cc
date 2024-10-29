#include "object.h"

void s21::Object::Parser(std::string path) {
  std::ifstream my_file;
  my_file.open(path);
  if (!my_file.is_open()) {
    std::cout << "File is not opened" << std::endl;  // TODO throw exception
  } else {
    std::string str;
    // while (!my_file.eof()) {
      while(std::getline(my_file, str, '\n')) {
      std::string::const_iterator ch = str.cbegin();
      // while (ch != str.end()) {  // TODO starts_with
        if (*ch == 'v') {
          if (*(++ch) == ' ') {
            ReadVertex(str);
          }
        }
        // break;
        if (*ch == 'f') {  // TODO starts_with
          if (*(++ch) == ' ') {
            ReadFacet(str);
          }
        }
        // break;
      // }
      // break;
    }
    my_file.close();
  }  // file is opened
};

void s21::Object::ReadVertex(std::string &str) {
  std::string sub2 = str.substr(2);
  std::istringstream iss(sub2);
  Point point;
  if (iss >> point.x >> point.y >> point.z) {
    vertex_.push_back(point);
    vertex_count_++;
  }
}

void s21::Object::ReadFacet(std::string &str) {
  std::string sub2 = str.substr(2);
  std::istringstream iss(sub2);
  std::vector<double> facet;
  double vertex_number;
  while (iss >> vertex_number) {
    facet.push_back(vertex_number);
  }
  facet_.push_back(facet);
}

void s21::Object::PrintVertices() {
    int number = 1;
    for (Point i : vertex_) {
        std::cout << "Vertex number " << number++ << ":" << "\t" << i.x << "\t" << i.y << "\t"
                  << i.z << std::endl;
    }
    std::cout << std::endl;
}

void s21::Object::PrintFacets() {
    int number = 1;
    for (std::vector<double> i : facet_) {
        std::cout << "Facet number " << number++ << ". Vertices:";
        for (double j : i) {
            std::cout << "\t" << j << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

