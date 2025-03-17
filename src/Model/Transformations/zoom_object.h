#ifndef VIEWER_SRC_MODEL_TRANSFORMATIONS_ZOOM_OBJECT_H
#define VIEWER_SRC_MODEL_TRANSFORMATIONS_ZOOM_OBJECT_H

#include "transformations.h"

namespace s21 {

 /**
  * @brief Класс ZoomObject для выполнения операций масштабирования.
  * @details Класс наследует от TransformationsBaseClass и предоставляет
  * функциональность для изменения размера объекта. Принимает
  * указатель на объект типа s21::Object в конструкторе.
  */
  class ZoomObject : public TransformationsBaseClass {

    public:

   /**
    * @brief Конструктор класса ZoomObject.
    * @details Инициализирует объект ZoomObject, передавая указатель на
    * объект в базовый класс TransformationsBaseClass.
    * Это позволяет производить операции масштабирования на
    * заданном объекте.
    * @param obj Указатель на объект типа s21::Object, который
    * будет подвергаться преобразованиям.
    */
    ZoomObject(s21::Object *obj) : TransformationsBaseClass(obj) {};


   /**
    * @brief Деструктор по умолчанию.
    */
    ~ZoomObject() = default;


   /**
    * @brief Метод для изменения размера объекта.
    * @details Метод масштабирует все вершины объекта, умножая
    * координаты каждой вершины на соответствующие коэффициенты
    * масштабирования по осям x, y и z.
    * @param x Коэффициент масштабирования по оси X.
    * @param y Коэффициент масштабирования по оси Y.
    * @param z Коэффициент масштабирования по оси Z.
    */
    void Modify(double x, double y, double z) override;

    };

} // namespace s21

#endif  // VIEWER_SRC_MODEL_TRANSFORMATIONS_ZOOM_OBJECT_H
