#ifndef OBJECT_H
#define OBJECT_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

namespace s21 {

struct Point {
  double x;
  double y;
  double z;
};

class Object {
 public:
  Object() {
    Point point;  ///< нулевая вершина-заглушка
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
  double getMaxX() { return max_vertex_x_; };
  double getMinX() { return min_vertex_x_; };
  double getMaxY() { return max_vertex_y_; };
  double getMinY() { return min_vertex_y_; };
  double getMaxZ() { return max_vertex_z_; };
  double getMinZ() { return min_vertex_z_; };

  std::vector<Point> getVertex() { return vertex_; }
  std::vector<std::vector<int>> getFacet() { return facet_; }

  int getVertexCount() { return vertex_count_; }

  int getEdgeCount() { return edge_count_; }

  /* служебные методы */
  void PrintVertices();
  void PrintFacets();

 private:
  std::vector<Point> vertex_;
  std::vector<std::vector<int>> facet_;
  int vertex_count_ = 0;
  int edge_count_ = 0;

  double max_vertex_x_;
  double min_vertex_x_;
  double max_vertex_y_;
  double min_vertex_y_;
  double max_vertex_z_;
  double min_vertex_z_;

  void CenterObject();
  void SetMaxCoordinates();
};

}  // namespace s21

#endif  // OBJECT_H
