#ifndef VIEWER_SRC_MODEL_TRANSFORMATIONS_ROTATE_OBJECT_H
#define VIEWER_SRC_MODEL_TRANSFORMATIONS_ROTATE_OBJECT_H

#include "transformations.h"

namespace s21 {

/**
 * @brief Класс для выполнения вращения объектов.
 * Класс RotateObject наследуется от базового класса TransformationsBaseClass
 * и предназначен для выполнения операций вращения над объектами. Он предоставляет
 * методы для изменения координат объекта в соответствии с заданными углами
 * вращения вокруг осей.
 */
  class RotateObject : public TransformationsBaseClass {

  public:

  /**
   * @brief Конструктор класса RotateObject.
   * @details Инициализирует объект класса RotateObject, передавая указатель
   * на объект в базовый класс TransformationsBaseClass.
   * @param obj Указатель на объект, над которым будут выполняться трансформации.
   */
    RotateObject(s21::Object *obj) : TransformationsBaseClass(obj) {};

    /**
     * @brief Деструктор по умолчанию.
     */
    ~RotateObject() = default;


  /**
   * @brief Метод для изменения координат объектов.
   * @details Метод выполняет вращение объекта вокруг заданной оси на указанный
   * угол. Угол задается в градусах и преобразуется в радианы. В зависимости от
   * значений параметров `x`, `y` и `z`, метод выполняет вращение вокруг соответствующей
   * оси (X, Y или Z) для всех вершин объекта.
   * @param x Угол вращения вокруг оси X (в градусах).
   * @param y Угол вращения вокруг оси Y (в градусах).
   * @param z Угол вращения вокруг оси Z (в градусах).
   */
    void Modify(double x, double y, double z) override;

    /**
     * @brief Метод для вращения координат вокруг оси.
     * @details Метод выполняет вращение двух координат (`coord_a` и `coord_b`)
     * на заданный угол. Угол передается в радианах.
     * @param angle Угол вращения (в радианах).
     * @param coord_a Ссылка на первую координату, которая будет изменена.
     * @param coord_b Ссылка на вторую координату, которая будет изменена.
     */
    void RotateAxis(double angle, double &coord_a, double &coord_b);

  };

} // s21

#endif // VIEWER_SRC_MODEL_TRANSFORMATIONS_ROTATE_OBJECT_H
