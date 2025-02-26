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
   * @details Обрабатывает строки, начинающиеся с "v " для чтения вершин и "f "
   * для чтения граней. Если файл не удается открыть, выбрасывается исключение с
   * соответствующим сообщением об ошибке.
   * @param path Путь к файлу.
   * @return true если парсинг выполнен успешно, иначе false.
   */
  bool Parse(std::string path);

  /**
   * @brief Читает координаты вершины из строки и добавляет её в список вершин.
   * @details Если считывание прошло успешно, вершина добавляется
   * в вектор вершин объекта, и увеличивается счетчик вершин.
   * @param str Ссылка на строку, содержащую данные о вершине,
   * начинающиеся с "v ".
   */
  void ReadVertex(std::string &str);

  /**
   * @brief Читает данные о грани из строки и добавляет её в список граней.
   * @details Если индекс превышает количество вершин или является недопустимым,
   * выбрасывается исключение. Если индекс отрицательный, он преобразуется
   * в положительный, основываясь на количестве вершин в объекте.
   * После успешного считывания, грань добавляется в вектор граней,
   * а счетчик рёбер увеличивается.
   * @param str Ссылка на строку, содержащую данные о грани,
   * начинающиеся с "f ".
   * @return true если чтение грани прошло успешно, иначе false.
   */
  bool ReadFacet(std::string &str);

  double GetMaxX() const { return max_vertex_x_; };
  double GetMinX() const { return min_vertex_x_; };
  double GetMaxY() const { return max_vertex_y_; };
  double GetMinY() const { return min_vertex_y_; };
  double GetMaxZ() const { return max_vertex_z_; };
  double GetMinZ() const { return min_vertex_z_; };

  std::vector<Point> GetVertices() { return vertices_; }
  std::vector<Point> &GetInitialVeritcesRef() { return initial_vertices_; }
  std::vector<Point> &GetVerticesRef() { return vertices_; }
  std::vector<std::vector<int>> GetFacets() { return facets_; }

  void SetInitialVertices() { initial_vertices_ = vertices_; }

  int GetVertexCount() const { return vertex_count_; }
  int GetEdgeCount() const { return edge_count_; }

  void Modify(std::unique_ptr<TransformationsBaseClass> modify_class,
              double value_x, double value_y, double value_z);

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
  void SetMaxCoordinates();

  void Clear();

  /* служебные методы */
  void PrintVertices();
  void PrintFacets();
};

}  // namespace s21

#endif  // OBJECT_H
