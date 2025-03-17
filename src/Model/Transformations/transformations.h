#ifndef VIEWER_SRC_MODEL_TRANSFORMATIONS_H
#define VIEWER_SRC_MODEL_TRANSFORMATIONS_H

#include "../object.h"


namespace s21 {

 /**
  * @brief Базовый класс для преобразований объектов.
  * @details Служит абстрактным базовым классом для всех классов, реализующих
  * преобразования объектов, такие как вращение (rotate), перемещение (move) и
  * масштабирование (zoom). Определяет интерфейс для модификации объекта
  * через виртуальный метод Modify().
  */
  class TransformationsBaseClass {

   public:

   /**
    * @brief Конструктор класса TransformationsBaseClass.
    * @details Конструктор инициализирует объект класса TransformationsBaseClass.
    * Параметр obj указывает на объект типа s21::Object, который будет
    * модифицироваться.
    * @param obj Указатель на объект типа s21::Object, который будет
    * подвергаться преобразованиям. По умолчанию равен nullptr.
    */
    TransformationsBaseClass(s21::Object *obj = nullptr) : object_(obj) {};


   /**
    * @brief Деструктор по умолчанию.
    */
    virtual ~TransformationsBaseClass() = default;


   /**
    * @brief Виртуальный метод для модификации объекта.
    * @details Метод реализован в производных классах для выполнения
    * конкретных преобразований объекта, таких как вращение, перемещение или
    * масштабирование.
    * @param x Значение изменения по оси X.
    * @param y Значение изменения по оси Y.
    * @param z Значение изменения по оси Z.
    */
    virtual void Modify(double x, double y, double z) = 0;

   protected:
    s21::Object *object_; ///< указатель на объект

  };

} // namespace s21

#endif  // VIEWER_SRC_MODEL_TRANSFORMATIONS_H

