#include "opengl_view.h"
#include "Controller/controller.h"
#include "Model/object.h"

Object3d::Object3d(QWidget *parent)
        : QOpenGLWidget(parent)
{
}

Object3d::~Object3d()
{
}

void Object3d::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Черный фон
}

void Object3d::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT); // Очистка цветового буфера

////    Тестовый квадрат:
//    // Рисуем точки
//    glPointSize(5);
//    glBegin(GL_POINTS);
//    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет
//    glVertex2f(-0.5f, -0.5f); // Левый нижний угол
//    glVertex2f(0.5f, -0.5f);  // Правый нижний угол
//    glVertex2f(0.5f, 0.5f);   // Правый верхний угол
//    glVertex2f(-0.5f, 0.5f);
//    glEnd();


//    // Рисуем
//    glBegin(GL_LINE_LOOP);
//    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет
//    glVertex2f(-0.5f, -0.5f); // Левый нижний угол
//    glVertex2f(0.5f, -0.5f);  // Правый нижний угол
//    glVertex2f(0.5f, 0.5f);   // Правый верхний угол
//    glVertex2f(-0.5f, 0.5f);  // Левый верхний угол
//    glEnd();


    // Рисуем точки
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет

    std::vector<s21::Point> vertices = view_->controller->getVertices();
    for (s21::Point i : vertices) {
        glVertex3d(i.x, i.y, i.z);
    }
    glEnd();


//    // Рисуем
//    glBegin(GL_LINE_LOOP);
//    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет
//    glVertex2f(-0.5f, -0.5f); // Левый нижний угол
//    glVertex2f(0.5f, -0.5f);  // Правый нижний угол
//    glVertex2f(0.5f, 0.5f);   // Правый верхний угол
//    glVertex2f(-0.5f, 0.5f);  // Левый верхний угол
//    glEnd();


}

void Object3d::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Установка проекции
    glMatrixMode(GL_MODELVIEW);
}
