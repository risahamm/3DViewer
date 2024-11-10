#include "object.h"

void s21::Object::Parser(std::string path) {
    std::ifstream my_file;
    try {
        my_file.open(path);
        if (!my_file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл " + path);
        } else {
            std::string str;
            while (std::getline(my_file, str, '\n')) {
                std::string::const_iterator ch = str.cbegin();
                if (*ch == 'v') {
                    if (*(++ch) == ' ') {
                        ReadVertex(str);
                    }
                }
                if (*ch == 'f') {  // TODO starts_with
                    if (*(++ch) == ' ') {
                        ReadFacet(str);
                    }
                }
            }
            my_file.close();
        }

    } catch (const std::runtime_error &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return;
    }
}

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
    std::vector<int> facet;
    int vertex_number;
    std::string single_vertex;
    while (iss >> single_vertex) {
        size_t pos = single_vertex.find('/') || single_vertex.find(' '); // находим первый разделитель '/'
        if (pos != std::string::npos) {
            vertex_number = stoi(single_vertex.substr(0, pos));
            facet.push_back(vertex_number);
        }
    }
    facet_.push_back(facet);
}


/*--------------------------------------------------------------------------------------------*/

void s21::Object::PrintVertices() {
  int number = 0;
  for (Point i : vertex_) {
    std::cout << "Vertex number " << number++ << ":"
              << "\t" << i.x << "\t" << i.y << "\t" << i.z << std::endl;
  }
  std::cout << std::endl;
}

void s21::Object::PrintFacets() {
  int number = 1;
  for (std::vector<int> i : facet_) {
    std::cout << "Facet number " << number++ << ". Vertices:";
    for (int j : i) {
      std::cout << "\t" << j << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
