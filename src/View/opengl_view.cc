#include "opengl_view.h"

Square::Square(QWidget *parent)
        : QOpenGLWidget(parent)
{
}

Square::~Square()
{
}

void Square::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Черный фон
}

void Square::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT); // Очистка цветового буфера

    // Рисуем точки
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет
    glVertex2f(-0.5f, -0.5f); // Левый нижний угол
    glVertex2f(0.5f, -0.5f);  // Правый нижний угол
    glVertex2f(0.5f, 0.5f);   // Правый верхний угол
    glVertex2f(-0.5f, 0.5f);
    glEnd();


    // Рисуем
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет
    glVertex2f(-0.5f, -0.5f); // Левый нижний угол
    glVertex2f(0.5f, -0.5f);  // Правый нижний угол
    glVertex2f(0.5f, 0.5f);   // Правый верхний угол
    glVertex2f(-0.5f, 0.5f);  // Левый верхний угол
    glEnd();

}

void Square::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Установка проекции
    glMatrixMode(GL_MODELVIEW);
}