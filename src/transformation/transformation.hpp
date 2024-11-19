#ifndef CPP4_3DVIEWER_V2_0_1_SRC_3D_TRANSFORMATION_HPP_
#define CPP4_3DVIEWER_V2_0_1_SRC_3D_TRANSFORMATION_HPP_

/************************************************************
 * @file transformation.hpp
 * @brief Реализация афинных преобразований
 ************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>

#include "../object/object.hpp"

namespace s21 {

/************************************************************
 * @brief Преобразований
 *
 * Перечисление возможных преобразований
 ************************************************************/
enum Movement { MoveX, MoveY, MoveZ, RotateX, RotateY, RotateZ, SCALE };

/************************************************************
 * @brief Класс афинных преобразований
 *
 * Базовый класс с одним виртуальным методом для возможных преобразований
 ************************************************************/
class TransformationStrategy {
 public:
  /************************************************************
   * @brief Виртуальный метод преобразований
   *
   * Виртуальный метод для  преобразования модели
   * @param vertexes Вектор, над которым будет происходить преобразование
   * @param move Название преобразования
   * @param value Значение, указывающий или шаг, или угол, или коэффициент
   *масштабирования
   ************************************************************/
  virtual void Transform(std::vector<Point>& vertexes, Movement move,
                         double value) = 0;
};

/************************************************************
 * @brief Класс поворота модели
 *
 * Класс для поворота модели по заданной оси координат.
 ************************************************************/
class Rotate : public TransformationStrategy {
 public:
  /************************************************************
   * @brief Переопределенный метод из родительского класса TransformStrategy
   *
   * @param vertexes Вектор, который будем поворачивать
   * @param move Название преобразования: поворото по X, Y или Z
   * @param value Значение, указывающий угол поворота
   ************************************************************/
  void Transform(std::vector<Point>& vertexes, Movement move,
                 double angle) override;

 private:
  /************************************************************
   * @brief Метод поворота модели по оси X
   *
   * Поворачивает модель по оси X
   * @param vertexes Вектор, который будем поворачивать
   * @param value Значение, указывающий угол поворота
   ************************************************************/
  void rotateX(std::vector<Point>& vertexes, double angle);

  /************************************************************
   * @brief Метод поворота модели по оси Y
   *
   * Поворачивает модель по оси Y
   * @param vertexes Вектор, который будем поворачивать
   * @param value Значение, указывающий угол поворота
   ************************************************************/
  void rotateY(std::vector<Point>& vertexes, double angle);

  /************************************************************
   * @brief Метод поворота модели по оси Z
   *
   * Поворачивает модель по оси Z
   * @param vertexes Вектор, который будем поворачивать
   * @param value Значение, указывающий угол поворота
   ************************************************************/
  void rotateZ(std::vector<Point>& vertexes, double angle);
};

/************************************************************
 * @brief Класс перемещения модели
 *
 * Перемещает модель по оси X, Y, Z
 ************************************************************/
class Move : public TransformationStrategy {
 public:
  /************************************************************
   * @brief Переопределенный метод из родительского класса TransformStrategy
   *
   * @param vertexes Вектор, над которым буде произведена операция перемещения
   * @param move Название преобразования: перемещение по X, Y или Z
   * @param value Значение, указывающий шаг перемещения
   ************************************************************/
  void Transform(std::vector<Point>& vertexes, Movement move,
                 double step) override;

 private:
  /************************************************************
   * @brief Метод перемещения по оси X
   *
   * Перемещает модель по оси X на заданное значение
   * @param vertexes Вектор, над которым буде произведена операция перемещения
   * @param value Значение, указывающий шаг перемещения
   ************************************************************/
  void moveX(std::vector<Point>& vertexes, double step);

  /************************************************************
   * @brief Метод перемещения по оси Y
   *
   * Перемещает модель по оси Y на заданное значение
   * @param vertexes Вектор, над которым буде произведена операция перемещения
   * @param value Значение, указывающий шаг перемещения
   ************************************************************/
  void moveY(std::vector<Point>& vertexes, double step);

  /************************************************************
   * @brief Метод перемещения по оси Z
   *
   * Перемещает модель по оси Z на заданное значение
   * @param vertexes Вектор, над которым буде произведена операция перемещения
   * @param value Значение, указывающий шаг перемещения
   ************************************************************/
  void moveZ(std::vector<Point>& vertexes, double step);
};

/************************************************************
 * @brief Класс масштабирования модели
 ************************************************************/
class Scale : public TransformationStrategy {
 public:
  /************************************************************
   * @brief Переопределенный метод из родительского класса TransformStrategy
   *
   * @param vertexes Вектор, над которым буде произведена операция
   *масштабирования
   * @param move Название преобразования: масштабирование (SCALE)
   * @param value Коэффициент масштабирования
   ************************************************************/
  void Transform(std::vector<Point>& vertexes, Movement move,
                 double step) override;

 private:
  /************************************************************
   * @brief Метод масштабирования модели
   *
   * @param vertexes Вектор, над которым буде произведена операция
   *масштабирования
   * @param value Коэффициент масштабирования
   ************************************************************/
  void scale(std::vector<Point>& vertexes, double scal);
};

/************************************************************
 * @brief Класс инкапсулирующий указатель на объект базового класса
 ************************************************************/
class ObjectTransformer {
  TransformationStrategy* strategy_;

 public:
  /************************************************************
   * @brief Конструктор по умолчанию
   ************************************************************/
  ObjectTransformer() = default;

  /************************************************************
   * @brief Метод для выбора стратегии
   *
   * В методе выбирается стратегия для трансформации: поворот, перемещение или
   *масштабирование
   * @param strategy Указатель на стратегию
   ************************************************************/
  void set_strategy(TransformationStrategy* strategy);

  /************************************************************
   * @brief Метод преобразования модели
   *
   * В методе вызывается метод преобразования модели той стратегии, которую мы
   *установили
   * @param vertexes Вектор, над которым будет происходить преобразование
   * @param move Название преобразования
   * @param value Значение, указывающий или шаг, или угол, или коэффициент
   *масштабирования
   ************************************************************/
  void TransformModel(std::vector<Point>& vertexes, Movement move,
                      double value);
};

}  // namespace s21

#endif