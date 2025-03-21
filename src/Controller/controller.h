#ifndef VIEWER_SRC_CONTROLLER_CONTROLLER_H
#define VIEWER_SRC_CONTROLLER_CONTROLLER_H

#include "../Model/Transformations/move_object.h"
#include "../Model/Transformations/zoom_object.h"
#include "../Model/Transformations/rotate_object.h"
#include "../Model/object.h"

namespace s21 {

/**
 * @brief Класс Controller для управления объектами типа Object.
 * @details Предоставляет интерфейс для взаимодействия с объектами
 * типа Object. Позволяет открывать файлы, получать информацию о
 * вершинах и гранях, а также выполнять операции перемещения и
 * вращения объекта в трехмерном пространстве.
 */
class Controller {
 public:
  /**
   * @brief Конструктор класса Controller.
   * @details Инициализирует объект Controller с указателем на
   * объект типа Object.
   * @param obj Указатель на объект типа Object, который будет управляться
   * контроллером.
   */
  Controller(Object *obj = nullptr) : object_(obj) {};

  /**
   * Деструктор по умолчанию.
   */
  ~Controller() = default;

  /**
   * @brief Открывает файл по указанному пути.
   * @details Вызывает метод Parse класса Object, который обрабатывает
   * данные об объекте.
   * @param path Путь к файлу, который необходимо открыть.
   * @return true если файл успешно открыт и данные загружены, иначе false.
   */
  bool OpenFile(const std::string &path);

  /**
   * @brief Получает список вершин объекта.
   * @return Вектор точек, представляющих вершины объекта.
   */
  std::vector<s21::Point> GetVertices() { return object_->GetVertices(); };

  /**
   * @brief Получает список граней объекта.
   * @return Вектор векторов целых чисел, представляющих грани объекта.
   */
  std::vector<std::vector<int>> GetFacets() { return object_->GetFacets(); };

  /**
   * @brief Получает количество вершин объекта.
   * @return Общее количество вершин в объекте
   */
  int GetVerticesCount() { return object_->GetVertexCount(); };

  /**
   * @brief Получает количество рёбер объекта.
   * @return Общее количество рёбер в объекте
   */
  int GetEdgesCount() { return object_->GetEdgeCount(); };

  /**
   * @brief Получает максимальную координату по оси X.
   * @return Максимальное значение координаты X.
   */
  double GetMaxCoordinateX() { return object_->GetMaxX(); };

  /**
   * @brief Получает минимальную координату по оси X.
   * @return Минимальное значение координаты X.
   */
  double GetMinCoordinateX() { return object_->GetMinX(); };

  /**
   * @brief Получает максимальную координату по оси Y.
   * @return Максимальное значение координаты Y.
   */
  double GetMaxCoordinateY() { return object_->GetMaxY(); };

  /**
   * @brief Получает минимальную координату по оси Y.
   * @return Минимальное значение координаты Y.
   */
  double GetMinCoordinateY() { return object_->GetMinY(); };

  /**
   * @brief Получает максимальную координату по оси Z.
   * @return Максимальное значение координаты Z.
   */
  double GetMaxCoordinateZ() { return object_->GetMaxZ(); };

  /**
   * @brief Получает минимальную координату по оси Z.
   * @return Минимальное значение координаты Z.
   */
  double GetMinCoordinateZ() { return object_->GetMinZ(); };

  /**
   * @brief Перемещает объект по оси X вправо.
   * @details Использует объект типа MoveObject для выполнения преобразования.
   * @param value Значение, на которое объект будет перемещен вправо по оси X.
   */
  void MoveXRight(double value);

  /**
   * @brief Перемещает объект по оси X влево.
   * @details Использует объект типа MoveObject для выполнения преобразования.
   * @param value Значение, на которое объект будет перемещен влево по оси X.
   */
  void MoveXLeft(double value);

  /**
   * @brief Перемещает объект по оси Y вверх.
   * @details Использует объект типа MoveObject для выполнения преобразования.
   * @param value Значение, на которое объект будет перемещен вверх по оси Y.
   */
  void MoveYUp(double value);

  /**
   * @brief Перемещает объект по оси Y вниз.
   * @details Использует объект типа MoveObject для выполнения преобразования.
   * @param value Значение, на которое объект будет перемещен вниз по оси Y.
   */
  void MoveYDown(double value);

  /**
   * @brief Перемещает объект по оси Z вперед.
   * @details Использует объект типа MoveObject для выполнения преобразования.
   * @param value Значение, на которое объект будет перемещен вперед по оси Z.
   */
  void MoveZForward(double value);

  /**
   * @brief Перемещает объект по оси Z назад.
   * @details Использует объект типа MoveObject для выполнения преобразования.
   * @param value Значение, на которое объект будет перемещен назад по оси Z.
   */
  void MoveZBackward(double value);

  /**
   * @brief Метод для изменения масштаба объекта.
   * @details Принимает значение масштаба и применяет его к
   * объекту, создавая новый объект типа ZoomObject, который
   * будет использоваться для изменения масштаба.
   * @param value Значение масштаба, которое будет применено
   * к объекту по всем осям (X, Y, Z).
   */
  void Zoom(double value);

  /**
   * @brief Вращает объект относительно оси X вверх.
   * @details Использует объект типа RotateObject для выполнения преобразования.
   * @param value Угол поворота объекта вокруг оси X.
   */
  void RoateXUp(double value);

  /**
   * @brief Вращает объект относительно оси X вниз.
   * @details Использует объект типа RotateObject для выполнения преобразования.
   * @param value Угол поворота объекта вокруг оси X.
   */
  void RoateXDown(double value);

  /**
   * @brief Вращает объект относительно оси Y вправо.
   * @details Использует объект типа RotateObject для выполнения преобразования.
   * @param value Угол поворота объекта вокруг оси Y.
   */
  void RoateYRight(double value);

  /**
   * @brief Вращает объект относительно оси Y влево.
   * @details Использует объект типа RotateObject для выполнения преобразования.
   * @param value Угол поворота объекта вокруг оси Y.
   */
  void RoateYLeft(double value);

  /**
   * @brief Вращает объект относительно оси Z по часовой стрелке.
   * @details Использует объект типа RotateObject для выполнения преобразования.
   * @param value Угол поворота объекта вокруг оси Z.
   */
  void RoateZClckWs(double value);

  /**
   * @brief Вращает объект относительно оси Z против часовой стрелке.
   * @details Использует объект типа RotateObject для выполнения преобразования.
   * @param value Угол поворота объекта вокруг оси Z.
   */
  void RoateZCClckWs(double value);

  /**
   * @brief Очищает данные объекта и сбрасывает его состояние.
   */
  void ClearObject() { object_->Clear(); }

 private:
  Object *object_;  ///< указатель на объект
};

}  // namespace s21

#endif  // VIEWER_SRC_CONTROLLER_CONTROLLER_H
