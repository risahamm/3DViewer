#ifndef VIEWER_SRC_MODEL_OBJECT_H
#define VIEWER_SRC_MODEL_OBJECT_H

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

  /**
   * @brief Возвращает значение максимальной координаты по оси X.
   * @return Максимальная координата по оси X.
   */
  double GetMaxX() const { return max_vertex_x_; };

  /**
   * @brief Возвращает значение минимальной координаты по оси X.
   * @return Минимальная координата по оси X.
   */
  double GetMinX() const { return min_vertex_x_; };

  /**
   * @brief Возвращает значение максимальной координаты по оси Y.
   * @return Максимальная координата по оси Y.
   */
  double GetMaxY() const { return max_vertex_y_; };

  /**
   * @brief Возвращает значение минимальной координаты по оси Y.
   * @return Минимальная координата по оси Y.
   */
  double GetMinY() const { return min_vertex_y_; };

  /**
   * @brief Возвращает значение максимальной координаты по оси Z.
   * @return Максимальная координата по оси Z.
   */
  double GetMaxZ() const { return max_vertex_z_; };

  /**
   * @brief Возвращает значение минимальной координаты по оси Z.
   * @return Минимальная координата по оси Z.
   */
  double GetMinZ() const { return min_vertex_z_; };

  /**
   * @brief Возвращает копию вектора вершин объекта.
   * @return Копия вектора вершин объекта.
   */
  std::vector<Point> GetVertices() { return vertices_; }


  /**
   * @brief Возвращет ссылку на вектор вершин объекта.
   * @return Ссылка на вектор вершин объекта.
   */
  std::vector<Point> &GetVerticesRef() { return vertices_; }

  /**
   * @brief Возвращает копию вектора полигонов объекта.
   * @return Копия вектора полигонов объекта.
   */
  std::vector<std::vector<int>> GetFacets() { return facets_; }


  /**
   * @brief Возвращает количество вершин в объекте.
   * @return Количество вершин в объекте.
   */
  int GetVertexCount() const { return vertex_count_; }

  /**
   * @brief Возвращает количество граней объекта.
   * @return Количество граней объекта.
   */
  int GetEdgeCount() const { return edge_count_; }

  /**
   * @brief В зависимости от выбранной стратегии реализует способ преобразования
   * объекта.
   * @param modify_class Указатель на экземпляр класса, производного от
   * TransformationsBaseClass, который определяет поведение преобразования.
   * @param value_x Значение для изменения координаты x объекта.
   * @param value_y Значение для изменения координаты y объекта.
   * @param value_z Значение для изменения координаты z объекта.
   */
  void Modify(std::unique_ptr<TransformationsBaseClass> modify_class,
              double value_x, double value_y, double value_z);

  /**
   * Очищает данные объекта и сбрасывает его состояние.
   */
  void Clear();

 private:
  std::vector<Point> vertices_;  ///< текущие вершины объекта
  std::vector<std::vector<int>> facets_;  ///< полигоны
  int vertex_count_ = 0;                  ///< количество вершин
  int edge_count_ = 0;                    ///< количество рёбер

  double max_vertex_x_;  ///< максимальное значение по оси X
  double min_vertex_x_;  ///< минимальное значение по оси X
  double max_vertex_y_;  ///< максимальное значение по оси Y
  double min_vertex_y_;  ///< минимальное значение по оси Y
  double max_vertex_z_;  ///< максимальное значение по оси Z
  double min_vertex_z_;  ///< минимальное значение по оси Z

  /**
   * @brief Центрирует объект относительно начала координат.
   * @details Вычисляет центр объекта на основе его максимальных и минимальных
   * координат по осям x, y и z и смещает все вершины объекта так,
   * чтобы центр оказался в начале координат (0, 0, 0).
   */
  void CenterObject();

  /**
   * @brief Устанавливает максимальные и минимальные координаты объекта.
   * @details Проходит по всем вершинам объекта и определяет максимальные и
   * минимальные значения координат по осям x, y и z.
   */
  void SetMaxCoordinates();

  /* служебные методы */
  void PrintVertices();
  void PrintFacets();
};

}  // namespace s21

#endif  // VIEWER_SRC_MODEL_OBJECT_H
