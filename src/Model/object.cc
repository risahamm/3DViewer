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
        if (str.find("v ") != std::string::npos) {
          ReadVertex(str);
        }
        if (str.find("f ") != std::string::npos) {
          ReadFacet(str);
        }
      }
      my_file.close();
        CenterObject();
    }

  } catch (const std::runtime_error &e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
    return;
  }
}

void s21::Object::ReadVertex(std::string &str) {
  /* сдвигаем строку на 2 */
  std::string sub2 = str.substr(2);
  std::istringstream iss(sub2);
  Point point;

  if (iss >> point.x >> point.y >> point.z) {
    vertex_.push_back(point);
    vertex_count_++;

    if (point.x > max_vertex_x_.second) {
      max_vertex_x_.first = vertex_count_;
      max_vertex_x_.second = point.x;
    }

    if (point.x < min_vertex_x_.second) {
      min_vertex_x_.first = vertex_count_;
      min_vertex_x_.second = point.x;
    }

    if (point.y > max_vertex_y_.second) {
      max_vertex_y_.first = vertex_count_;
      max_vertex_y_.second = point.y;
    }

    if (point.y < min_vertex_y_.second) {
      min_vertex_y_.first = vertex_count_;
      min_vertex_y_.second = point.y;
    }

    if (point.z > max_vertex_z_.second) {
      max_vertex_z_.first = vertex_count_;
      max_vertex_z_.second = point.z;
    }

    if (point.z < min_vertex_z_.second) {
      min_vertex_z_.first = vertex_count_;
      min_vertex_z_.second = point.z;
    }

  }
}

void s21::Object::ReadFacet(std::string &str) {
  /* сдвигаем строку на 2 */
  std::string sub2 = str.substr(2);
  std::istringstream iss(sub2);
  std::vector<int> facet;
  int vertex_number;  ///< номер вершины
  std::string single_vertex;  ///< номер вершины, записанный в строку
  while (iss >> single_vertex) {
    /* находим первый разделитель '/' или ' ' */
    size_t pos = single_vertex.find('/') || single_vertex.find(' ');
    if (pos != std::string::npos) {
      vertex_number = stoi(single_vertex.substr(0, pos));
      facet.push_back(vertex_number);
      edge_count_++;
    }
  }
  facet_.push_back(facet);
}

void s21::Object::CenterObject() {

    double center_x;
    double center_y;
    double center_z;

    center_x = 0 - ((max_vertex_x_.second + min_vertex_x_.second) / 2);
    center_y = 0 - ((max_vertex_y_.second + min_vertex_y_.second) / 2);
    center_z = 0 - ((max_vertex_z_.second + min_vertex_z_.second) / 2);

    for (Point i : vertex_) {
        i.x + center_x;
        i.y + center_y;
        i.z + center_z;
    }
}

/*----------------------------------------------------------------------------*/

void s21::Object::PrintVertices() {
  int number = 0;
  for (Point i : vertex_) {
    std::cout << "Vertex number " << number++ << ":"
              << "\t" << i.x << "\t" << i.y << "\t" << i.z << std::endl;
  }

  std::cout << "max X vertex number " << max_vertex_x_.first << ": " << max_vertex_x_.second << std::endl;
  std::cout << "Total number of vertices: " << vertex_count_ << std::endl
            << std::endl;
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
  std::cout << "Total number of edges: " << edge_count_ << std::endl;
}