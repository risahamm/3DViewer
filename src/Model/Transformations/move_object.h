#ifndef VIEWER_SRC_MODEL_TRANSFORMATIONS_MOVE_OBJECT_H
#define VIEWER_SRC_MODEL_TRANSFORMATIONS_MOVE_OBJECT_H

#include "transformations.h"

namespace s21 {

  /**
  * @brief Класс для перемещения объектов.
  * @details Класс наследует от TransformationsBaseClass и
  * предоставляет функциональность для перемещения объектов
  * в трехмерном пространстве.
  */
  class MoveObject : public TransformationsBaseClass {

  public:

  /**
  * @brief Конструктор класса MoveObject.
  * @details Инициализирует объект MoveObject, передавая указатель на
  * объект в базовый класс TransformationsBaseClass.
  * Это позволяет производить операции перемещения на
  * заданном объекте.
  * @param obj Указатель на объект типа s21::Object, который
  * будет подвергаться преобразованиям.
  */
  MoveObject(s21::Object *obj) : TransformationsBaseClass(obj) {};


  /**
  * @brief Деструктор по умолчанию.
  */
  ~MoveObject() = default;


  /**
  * @brief Метод для перемещения объекта.
  * @details Метод переопределяет виртуальный метод базового класса
  * и выполняет перемещение объекта на заданные значения по
  * осям x, y и z.
  * @param x Смещение по оси X.
  * @param y Смещение по оси Y.
  * @param z Смещение по оси Z.
  */
  void Modify(double x, double y, double z) override;

  };

} // namespace s21

#endif  // VIEWER_SRC_MODEL_TRANSFORMATIONS_MOVE_OBJECT_H
