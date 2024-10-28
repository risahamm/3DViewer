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

 private:
  std::vector<Point> vertex_;
  //        std::vector<double> vertex_;
  std::vector<std::vector<double>> facet_;
};

}  // namespace s21

#endif  // OBJECT_H