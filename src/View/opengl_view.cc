#include "opengl_view.h"

#include "Controller/controller.h"
#include "Model/object.h"

Object3d::Object3d(QWidget *parent) : QOpenGLWidget(parent) {}

Object3d::~Object3d() {}

void Object3d::initializeGL() { initializeOpenGLFunctions(); }

/* вызывается только один раз в самом начале при отрисовке виджета */
void Object3d::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void Object3d::SetUpBackgroundColor() {
  GLfloat red =
      static_cast<GLfloat>(view_->current_settings.background_color.redF());
  GLfloat green =
      static_cast<GLfloat>(view_->current_settings.background_color.greenF());
  GLfloat blue =
      static_cast<GLfloat>(view_->current_settings.background_color.blueF());
  GLfloat alpha =
      static_cast<GLfloat>(view_->current_settings.background_color.alphaF());

  glClearColor(red, green, blue, alpha);
}

void Object3d::SetApplicationWidgetPtr(View *ptr) { view_ = ptr; };

/* вызывается каждый раз, когда вызываем update() */
void Object3d::paintGL() {

  /* если объект не выбран, ничего не рисуем */
  if (view_->object_path_ == nullptr) {
    return;
  }

  SetUpBackgroundColor();

  /* очистка цветового буфера */
  glClear(GL_COLOR_BUFFER_BIT);

  SetUpProjection();

  std::vector<s21::Point> vertices = view_->controller_->GetVertices();

  /* рисуем вершины */
  if (view_->current_settings.vertex == View::Vertex::dot ||
      view_->current_settings.vertex == View::Vertex::square) {
    glPointSize(static_cast<GLfloat>(view_->current_settings.vertex_size));
    SetUpVertexStyle();
    glBegin(GL_POINTS);
    SetUpPaintColor(view_->current_settings.vertex_color);

    for (int i = 1; i < vertices.size(); i++) {
      glVertex3d(vertices.at(i).x, vertices.at(i).y, vertices.at(i).z);
    }
    glEnd();
  }

  /* соединяем вершины */
  SetUpPaintColor(view_->current_settings.line_color);
  SetUpLineStyle();
  glLineWidth(static_cast<GLfloat>(view_->current_settings.line_size));
  std::vector<std::vector<int>> facets = view_->controller_->GetFacets();
  for (std::vector<int> &facet : facets) {
    glBegin(GL_LINE_LOOP);
    for (int &vertex : facet) {
      glVertex3d(vertices[vertex].x, vertices[vertex].y, vertices[vertex].z);
    }
    glEnd();
  }
}

void Object3d::SetUpPaintColor(QColor color) {
  GLfloat red = static_cast<GLfloat>(color.redF());
  GLfloat green = static_cast<GLfloat>(color.greenF());
  GLfloat blue = static_cast<GLfloat>(color.blueF());

  glColor3f(red, green, blue);
}

void Object3d::SetUpLineStyle() {
  if (view_->current_settings.line == View::Line::dashed) {
    glEnable(GL_LINE_STIPPLE);

    /* устанавливаем паттерн (пунктирная линия) */
    glLineStipple(1, 0xFF);

  } else {
    /* отключаем режим пунктирной линии */
    glDisable(GL_LINE_STIPPLE);
  }
}

void Object3d::SetUpVertexStyle() {
  if (view_->current_settings.vertex == View::Vertex::dot) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
}

void Object3d::SetUpProjection() {
  if (view_->current_settings.projection == View::Projection::ortho) {
    OrthoProjection();

  } else {
    PerspectProjection();
  }
}

void Object3d::OrthoProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* установка проекции */
  double max = FindMaxCoordinate() * 2;
  double min_z = view_->controller_->GetMinCoordinateZ();
  double max_z = view_->controller_->GetMaxCoordinateZ();

  glOrtho(-max, max, -max, max, min_z * 2, max_z * 2);

  /* значения, на которые необходимо сдивнуть объект при вызове move */
  glTranslatef(static_cast<GLfloat>(view_->x_step),
               static_cast<GLfloat>(view_->y_step), 0.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Object3d::PerspectProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  double max = FindMaxCoordinate();

  if (max <= 1) {
    max *= 3;
  } else {
    max *= 2;
  }

  GLdouble z_near = 0.01;
  GLdouble z_far = max * 1000;

  if (max <= 0.5) {
    max = 2;
  }

  GLdouble fov_y = 75; ///< угол обзора по вертикали
  GLdouble height = tan(fov_y / 360 * M_PI) * z_near;
  GLdouble width = height;

  /* установка проекции */
  glFrustum(-width, width, -height, height, z_near, z_far);

  view_->z_step = -max;

  /* значения, на которые необходимо сдивнуть объект при вызове move */
  glTranslatef(static_cast<GLfloat>(view_->x_step),
               static_cast<GLfloat>(view_->y_step),
               static_cast<GLfloat>(view_->z_step));

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

double Object3d::FindMaxCoordinate() {
  double x_max = view_->controller_->GetMaxCoordinateX();
  double y_max = view_->controller_->GetMaxCoordinateY();

  double max = 0.0;

  if (x_max > y_max) {
    max = x_max;

  } else {
    max = y_max;
  };

  return max;
}
