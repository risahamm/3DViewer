#ifndef OBJECT_H
#define OBJECT_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <vector>

#include "Transformations/transformations.h"

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
  bool Parser(std::string path);
  void ReadVertex(std::string &str);
  bool ReadFacet(std::string &str);

  double getMaxX() const { return max_vertex_x_; };
  double getMinX() const { return min_vertex_x_; };
  double getMaxY() const { return max_vertex_y_; };
  double getMinY() const { return min_vertex_y_; };
  double getMaxZ() const { return max_vertex_z_; };
  double getMinZ() const { return min_vertex_z_; };

  std::vector<Point> getVertex() { return vertices_; }
  std::vector<Point>& getVertexRef() { return vertices_; }
  std::vector<std::vector<int>> getFacet() { return facets_; }

  int getVertexCount() const { return vertex_count_; }
  int getEdgeCount() const { return edge_count_; }

  void Modify(std::unique_ptr<TransformationsBaseClass> modify_class, double value_x, double value_y, double value_z);

  void Clear();

  /* служебные методы */
  void PrintVertices();
  void PrintFacets();

 private:
  std::vector<Point> vertices_;
  std::vector<std::vector<int>> facets_;
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
