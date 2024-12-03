#include "opengl_view.h"
#include "Controller/controller.h"
#include "Model/object.h"

Object3d::Object3d(QWidget *parent)
        : QOpenGLWidget(parent) {

}

Object3d::~Object3d() {}

void Object3d::initializeGL() {

    initializeOpenGLFunctions();
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

    /* получим текущие настройки */
    GetSettings();

    SetUpBackgroundColor();

    SetUpPerspective();

    /* Рисуем точки */
    glPointSize(static_cast<GLfloat>(current_settings_.vertex_size));
    glBegin(GL_POINTS);
    glColor3f(191.0f / 255.0f, 189.0f / 255.0f, 193.0f / 255.0f); // Красный цвет

    std::vector<s21::Point> vertices = view_->controller_->getVertices();
    for (s21::Point &point : vertices) {

        glVertex3d(point.x, point.y, point.z);
    }
    glEnd();

//    glLineWidth(2.0f);
    glLineWidth(static_cast<GLfloat>(current_settings_.line_size));

    /* Соединяем точки */
    std::vector<std::vector<int>> facets = view_->controller_->getFacets();
    for (std::vector<int> &facet : facets)  {
        glBegin(GL_LINE_LOOP);
        for (int &vertex : facet)  {
            glVertex3d(vertices[vertex].x, vertices[vertex].y, vertices[vertex].z);
        }
        glEnd();
    }

}

/* вызывается только один раз в самом начале при отрисовке виджета */
void Object3d::resizeGL(int w, int h) {

    glViewport(0, 0, w, h);

}

void Object3d::SetUpPerspective() {

    if (current_settings_.perspective == View::Perspective::ortho) {
        OrthoPerspective();

    } else {
        ParallelPerspective(); // TODO надо проверить
    }

}

void Object3d::SetUpBackgroundColor() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // TODO потом подставить сюда выбор цвета
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

    current_settings_.perspective = view_->GetPerspectiveType();
    current_settings_.line = view_->GetLineType();
    current_settings_.line_size = view_->GetLineSize();
//    current_settings_.line_color = ;
    current_settings_.vertex = view_->GetVertexType();
    current_settings_.vertex_size = view_->GetVertexSize();
//    current_settings_.vertex_color =
//    current_settings_.background_color =
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
