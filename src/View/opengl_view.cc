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

    SetUpBackgroundColor();

    SetUpPerspective();

    /* Рисуем точки */
    glPointSize(static_cast<GLfloat>(view_->current_settings.vertex_size));
    glBegin(GL_POINTS);
    SetUpPaintColor(view_->current_settings.vertex_color);

    std::vector<s21::Point> vertices = view_->controller_->getVertices();

    for (int i = 1; i < vertices.size(); i++) {

        glVertex3d(vertices.at(i).x, vertices.at(i).y, vertices.at(i).z);
    }
    glEnd();


    /* Соединяем точки */
    SetUpPaintColor(view_->current_settings.line_color);
    glLineWidth(static_cast<GLfloat>(view_->current_settings.line_size));
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

    if (view_->current_settings.perspective == View::Perspective::ortho) {
        OrthoPerspective();

    } else {
        ParallelPerspective(); // TODO надо проверить
    }

}

void Object3d::SetUpBackgroundColor() {

    GLfloat red = static_cast<GLfloat>(view_->current_settings.background_color.red);
    GLfloat green = static_cast<GLfloat>(view_->current_settings.background_color.green);
    GLfloat blue = static_cast<GLfloat>(view_->current_settings.background_color.blue);
    GLfloat alpha = static_cast<GLfloat>(view_->current_settings.background_color.alpha);

    glClearColor(red, green, blue, alpha);
}

void Object3d::SetUpPaintColor(View::Color color) {

    GLfloat red = static_cast<GLfloat>(color.red);
    GLfloat green = static_cast<GLfloat>(color.green);
    GLfloat blue = static_cast<GLfloat>(color.blue);

    glColor3f(red, green, blue);
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
