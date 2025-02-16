#include "object.h"

#include "Transformations/transformations.h"

bool s21::Object::Parse(std::string path) {
  bool ret_code = true;
  std::ifstream my_file;

  /* обнулим данные объекта */
  Clear();

  my_file.open(path);

  try {
    if (!my_file.is_open()) {
      throw std::runtime_error("Failed to open file " + path);

    } else {
      std::string str;

      /* считываем построчно */
      while (std::getline(my_file, str, '\n') && ret_code) {
        if (str.find("v ") != std::string::npos) {
          ReadVertex(str);
        }
        if (str.find("f ") != std::string::npos) {
          ret_code = ReadFacet(str);
        }
      }

      my_file.close();

      SetMaxCoordinates();
      CenterObject();
    }

  } catch (const std::runtime_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return false;
  }

  return ret_code;
}

void s21::Object::ReadVertex(std::string &str) {
  /* сдвигаем строку на 2 */
  std::string begin = str.substr(2);

  /* создаем поток для считывания */
  std::istringstream iss(begin);
  Point point;

  /* считываем по разделителю ' ' и кладем в Point */
  if (iss >> point.x >> point.y >> point.z) {
    vertices_.push_back(point);
    vertex_count_++;
  }
}

bool s21::Object::ReadFacet(std::string &str) {
  /* сдвигаем строку на 2 */
  std::string begin = str.substr(2);

  /* создаем поток для считывания */
  std::istringstream iss(begin);

  std::vector<int> facet;  ///< один полигон
  int vertex_number;       ///< номер вершины
  std::string vertex_str;  ///< номер вершины, записанный в строку

  /* пока есть данные для считывания */
  while (iss >> vertex_str) {
    /* если в строке находится число */
    if (std::isdigit(vertex_str.at(0)) ||
        (vertex_str.at(0) == '-' && std::isdigit(vertex_str.at(1)))) {
      vertex_number = stoi(vertex_str);

      try {
        /* проевряем, что не индекс вершины не превышает кол-во вершин */
        if (vertex_number == 0 || vertex_number > vertex_count_) {
          throw std::out_of_range("Error: invalid object file");

        } else {
          /* обработка отрицательных вершин */
          if (vertex_number < 0) {
            /* узнаем кол-во вершин */
            int last_idx = vertices_.size();

            /* т.к. vertex_ хранит кол-во вершин + 1, получится корректное
             * значение */
            vertex_number = last_idx + vertex_number;
          }

          facet.push_back(vertex_number);
          edge_count_++;
        }

      } catch (const std::out_of_range &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
      }
    }
  }

  facets_.push_back(facet);
  return true;
}

void s21::Object::CenterObject() {
  double center_x = 0 - ((max_vertex_x_ + min_vertex_x_) / 2);
  double center_y = 0 - ((max_vertex_y_ + min_vertex_y_) / 2);
  double center_z = 0 - ((max_vertex_z_ + min_vertex_z_) / 2);

  for (Point &i : vertices_) {
    i.x += center_x;
    i.y += center_y;
    i.z += center_z;
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

  for (Point &point : vertices_) {
    if (point.x > max_vertex_x_) {
      max_vertex_x_ = point.x;
    }

    if (point.x < min_vertex_x_) {
      min_vertex_x_ = point.x;
    }

    if (point.y > max_vertex_y_) {
      max_vertex_y_ = point.y;
    }

    if (point.y < min_vertex_y_) {
      min_vertex_y_ = point.y;
    }

    if (point.z > max_vertex_z_) {
      max_vertex_z_ = point.z;
    }

    if (point.z < min_vertex_z_) {
      min_vertex_z_ = point.z;
    }
  }
}

void s21::Object::Modify(std::unique_ptr<TransformationsBaseClass> modify_class,
                         double value_x, double value_y, double value_z) {
  modify_class->Modify(value_x, value_y, value_z);
}

void s21::Object::Clear() {
  /* очистим vertex_ и добавим нулевую вершину */
  vertices_.clear();

  Point zero_point;  ///< нулевая вершина-заглушка
  vertices_.push_back(zero_point);

  facets_.clear();
  vertex_count_ = 0;
  edge_count_ = 0;

  max_vertex_x_ = 0;
  min_vertex_x_ = 0;
  max_vertex_y_ = 0;
  min_vertex_y_ = 0;
  max_vertex_z_ = 0;
  min_vertex_z_ = 0;
}
/*----------------------------------------------------------------------------*/

void s21::Object::PrintVertices() {
  //  int number = 0;
  //  for (Point &i : vertices_) {
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
  for (std::vector<int> &i : facets_) {
    std::cout << "Facet number " << number++ << ". Vertices:";
    for (int &j : i) {
      std::cout << "\t" << j << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "Total number of edges: " << edge_count_ << std::endl;
}
