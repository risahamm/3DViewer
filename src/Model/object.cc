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
      std::cout << "before " << std::endl;
      SetMaxCoordinates();
      PrintVertices();
      CenterObject();
      std::cout << "after " << std::endl;
      PrintVertices();
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
  }

}

void s21::Object::ReadFacet(std::string &str) { //TODO обработка отрицательных номеров facets
    // TODO например, если позиций всего три, то позиция "-1" - это позиция 3. позиция "-2" - это позиция 2. Позиции "-4" быть не может.
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
//    double center_z;

    center_x = 0 - ((max_vertex_x_ + min_vertex_x_) / 2);
    center_y = 0 - ((max_vertex_y_ + min_vertex_y_) / 2);
//    center_z = 0 - ((max_vertex_z_.second + min_vertex_z_.second) / 2);

    for (Point i : vertex_) {
        i.x + center_x;
        i.y + center_y;
//        i.z + center_z;
    }

    SetMaxCoordinates();
}

void s21::Object::SetMaxCoordinates() {

    max_vertex_x_ = -INFINITY;
    min_vertex_x_ = INFINITY;
    max_vertex_y_ = -INFINITY;
    min_vertex_y_ = INFINITY;
    max_vertex_z_ = -INFINITY;
    min_vertex_z_ = INFINITY;



//    for(Point point : vertex_) {
      for(int i = 1; i < vertex_.size(); i++) {

        if (vertex_[i].x > max_vertex_x_) {
          max_vertex_x_ = vertex_[i].x;
        }

        if (vertex_[i].x < min_vertex_x_) {
          min_vertex_x_= vertex_[i].x;
        }

        if (vertex_[i].y > max_vertex_y_) {
          max_vertex_y_ = vertex_[i].y;
        }

        if (vertex_[i].y < min_vertex_y_) {
          min_vertex_y_ = vertex_[i].y;
        }

        if (vertex_[i].z > max_vertex_z_) {
          max_vertex_z_ = vertex_[i].z;
        }

        if (vertex_[i].z < min_vertex_z_) {
          min_vertex_z_ = vertex_[i].z;
        }
    }
}
/*----------------------------------------------------------------------------*/

void s21::Object::PrintVertices() {
  int number = 0;
//  for (Point i : vertex_) {
//    std::cout << "Vertex number " << number++ << ":"
//              << "\t" << i.x << "\t" << i.y << "\t" << i.z << std::endl;
//  }

  std::cout << "max X vertex :" << max_vertex_x_ << std::endl;
  std::cout << "max Y vertex :" << max_vertex_y_ << std::endl;
  std::cout << "max Z vertex :" << max_vertex_z_ << std::endl;
  std::cout << "min X vertex :" << min_vertex_x_ << std::endl;
  std::cout << "min Y vertex :" << min_vertex_y_ << std::endl;
  std::cout << "min Z vertex :" << min_vertex_z_ << std::endl;
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
