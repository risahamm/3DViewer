#include "opengl_view.h"
#include "Controller/controller.h"
#include "Model/object.h"

Object3d::Object3d(QWidget *parent)
        : QOpenGLWidget(parent) {}

Object3d::~Object3d() {}

void Object3d::initializeGL() {

    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Черный фон
}

void Object3d::SetApplicationWidgetPtr(View *ptr) {

    view_ = ptr;
};


/* вызывается каждый раз, когда вызываем update() */
void Object3d::paintGL() {

    /* если объект не выбран, ничего не рисуем */
    if (view_->object_path_ == nullptr) {
        return;
    }

    /* Очистка цветового буфера */
    glClear(GL_COLOR_BUFFER_BIT);

    SetUpPerspective();

    /* Рисуем точки */
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f(191.0f / 255.0f, 189.0f / 255.0f, 193.0f / 255.0f); // Красный цвет

    std::vector<s21::Point> vertices = view_->controller_->getVertices();
    for (s21::Point &k : vertices) {

        glVertex3d(k.x, k.y, k.z);
    }
    glEnd();

    glLineWidth(2.0f);

    /* Соединяем точки */
    std::vector<std::vector<int>> facets = view_->controller_->getFacets();
    for (std::vector<int> &f : facets)  {
        glBegin(GL_LINE_LOOP);
        for (int &f1 : f)  {
            glVertex3d(vertices[f1].x, vertices[f1].y, vertices[f1].z);
        }
        glEnd();
    }

}

/* вызывается только один раз в самом начале при отрисовке виджета */
void Object3d::resizeGL(int w, int h) {

    glViewport(0, 0, w, h);

}

void Object3d::SetUpPerspective() {

    OrthoPerspective();
}

void Object3d::OrthoPerspective() {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Установка проекции */
    double max = FindMaxCoordinate();
    double min_z = view_->controller_->getMinCoordinateZ();
    double max_z = view_->controller_->getMaxCoordinateZ();

    glOrtho(-max, max, -max, max, min_z * 2, max_z * 2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Object3d::ParallelPerspective() {

    double max = FindMaxCoordinate();
    double min_z = view_->controller_->getMinCoordinateZ();
    double max_z = view_->controller_->getMaxCoordinateZ();

   /* Установка проекции */
    glFrustum(-max, max, -max, max, min_z, max_z);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Object3d::GetSettings() {

//    Perspective perspective;
//    Line line;
//    float line_size;
//    double line_color;
//    Vertex vertex;
//    float vertex_size;
//    double vertex_color;
//    double background_color;

    current_settings_.perspective = view_->GetPerspectiveType();
    current_settings_.line = view_->GetLineType();
//    current_settings_.line_size = view_->ui_->edge_size_slider->getValue(); // не работает
}

double Object3d::FindMaxCoordinate() {

    double xMax = view_->controller_->getMaxCoordinateX();
    double yMax = view_->controller_->getMaxCoordinateY();

    double MAX = 0.0;

    if (xMax > yMax) {
        MAX = xMax;

    } else {
        MAX = yMax;
    };

    MAX *= 2;
    return MAX;
}
