#include "opengl_view.h"
#include "Controller/controller.h"
#include "Model/object.h"

Object3d::Object3d(QWidget *parent)
        : QOpenGLWidget(parent) {}

Object3d::~Object3d() {}

void Object3d::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Черный фон
}

void Object3d::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT); // Очистка цветового буфера

    SetUpPerspective();

//    setFixedSize(600, 600);

    // Рисуем точки
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f); // Красный цвет

    std::vector<s21::Point> vertices = view_->controller->getVertices();
    for (s21::Point &k : vertices) {

        glVertex3d(k.x, k.y, k.z);
    }
    glEnd();


    // Соединяем точки
    std::vector<std::vector<int>> facets = view_->controller->getFacets();
    for (std::vector<int> &f : facets)  {
        glBegin(GL_LINE_LOOP);
        for (int &f1 : f)  {
            glVertex3d(vertices[f1].x, vertices[f1].y, vertices[f1].z);
        }
        glEnd();
    }

}

void Object3d::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

}

void Object3d::SetUpPerspective() {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double MAX = FindMaxCoordinate();
    glOrtho(-MAX, MAX, -MAX, MAX, 0.01, MAX*1000); // Установка проекции
//    glOrtho(-10, 10, -10, 10, 0.01, MAX*1000); // Установка проекции

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

double Object3d::FindMaxCoordinate() {

    double xMax = view_->controller->getMaxCoordinateX();
    double yMax = view_->controller->getMaxCoordinateY();

    double MAX = 0.0;

    if (xMax > yMax) {
        MAX = xMax;

    } else {
        MAX = yMax;
    };

    MAX *= 3;
    return MAX;
}

void Object3d::SetApplicationWidgetPtr(View *ptr) {

    view_ = ptr;
};
