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
  Object() = default;
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
  std::vector<std::vector<double>> facet_;
  int vertex_count_ = 0;
};

}  // namespace s21

#endif  // OBJECT_H