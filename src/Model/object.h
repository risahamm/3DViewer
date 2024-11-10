#ifndef OBJECT_H
#define OBJECT_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

struct Point {
  double x;
  double y;
  double z;
};

class Object {
 public:
  Object() {
      Point point;
      point.x = 0;
      point.y = 0;
      point.z = 0;
      vertex_.push_back(point);
  };
  ~Object() = default;

  /**
   *
   * @param path путь к файлу
   */
  void Parser(std::string path);
  void ReadVertex(std::string &str);
  void ReadFacet(std::string &str);

  /* служебные методы */
  void PrintVertices();
  void PrintFacets();

 private:
  std::vector<Point> vertex_;
  std::vector<std::vector<int>> facet_;
  int vertex_count_ = 0;
  int edge_count_ = 0; // не реализован подсчет количества ребер
};

}  // namespace s21

#endif  // OBJECT_H