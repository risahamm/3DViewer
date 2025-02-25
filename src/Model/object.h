#ifndef OBJECT_H
#define OBJECT_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {

class TransformationsBaseClass;

/**
 * @brief Структура для описания координат точки в 3D пространстве.
 */
struct Point {
  double x;
  double y;
  double z;

  Point() : x(0), y(0), z(0) {};
  Point(double x_val, double y_val, double z_val)
      : x(x_val), y(y_val), z(z_val) {};

  bool operator==(const Point &other) const {
    return (x == other.x && y == other.y && z == other.z);
  }
};

/**
 * @brief Класс для описания 3D объекта.
 * @details Класс предоставляет функциональность для парсинга данных
 * 3D объекта из файла, управления его вершинами и гранями,
 * а также методы для чтения данных о вершинах и гранях.
 */
class Object {
 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  Object() = default;

  /**
   * @brief Деструктор по умолчанию.
   */
  ~Object() = default;

  /**
   * @brief Открывает файл по указанному пути и считывает содержимое построчно.
   * Обрабатывает строки, начинающиеся с "v " для чтения вершин и "f " для
   * чтения граней. Если файл не удается открыть, выбрасывается исключение с
   * соответствующим сообщением об ошибке.
   * @param path Путь к файлу.
   * @return true Если парсинг выполнен успешно, иначе false.
   */
  bool Parse(std::string path);
  void ReadVertex(std::string &str);
  bool ReadFacet(std::string &str);

  double getMaxX() const { return max_vertex_x_; };
  double getMinX() const { return min_vertex_x_; };
  double getMaxY() const { return max_vertex_y_; };
  double getMinY() const { return min_vertex_y_; };
  double getMaxZ() const { return max_vertex_z_; };
  double getMinZ() const { return min_vertex_z_; };

  std::vector<Point> getVertices() { return vertices_; }
  std::vector<Point> &getInitialVeritcesRef() { return initial_vertices_; }
  std::vector<Point> &getVerticesRef() { return vertices_; }
  std::vector<std::vector<int>> getFacets() { return facets_; }

  void setInitialVertices() { initial_vertices_ = vertices_; }

  int getVertexCount() const { return vertex_count_; }
  int getEdgeCount() const { return edge_count_; }

  void Modify(std::unique_ptr<TransformationsBaseClass> modify_class,
              double value_x, double value_y, double value_z);

  void Clear();

 private:
  std::vector<Point> vertices_; ///< текущие вершины объекта
  std::vector<Point>
      initial_vertices_;  ///< начальные значения вершин (до zoom)
  std::vector<std::vector<int>> facets_; ///< полигоны
  int vertex_count_ = 0; ///< количество вершин
  int edge_count_ = 0; ///< количество рёбер

  double max_vertex_x_; ///< максимальное значение по оси X
  double min_vertex_x_; ///< минимальное значение по оси X
  double max_vertex_y_; ///< максимальное значение по оси Y
  double min_vertex_y_; ///< минимальное значение по оси Y
  double max_vertex_z_; ///< максимальное значение по оси Z
  double min_vertex_z_; ///< минимальное значение по оси Z

  void CenterObject();
  void setMaxCoordinates();

  /* служебные методы */
  void PrintVertices();
  void PrintFacets();
};

}  // namespace s21

#endif  // OBJECT_H
