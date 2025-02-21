#ifndef OPENGL_VIEW_H
#define OPENGL_VIEW_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "view.h"

class Object3d : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  Object3d(QWidget *parent = nullptr);
  ~Object3d();

  friend class View;

  void SetApplicationWidgetPtr(View *ptr);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 private:
  View *view_;

  void SetUpPerspective();
  void SetUpBackgroundColor();
  void SetUpPaintColor(QColor color);
  void SetUpLineStyle();
  void SetUpVertexStyle();

  void OrthoPerspective();
  void ParallelPerspective();

  double FindMaxCoordinate();
};

#endif  // OPENGL_VIEW_H
