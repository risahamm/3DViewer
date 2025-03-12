#ifndef OPENGL_VIEW_H
#define OPENGL_VIEW_H

#define GL_SILENCE_DEPRECATION

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

  void MoveXAxis(double x);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 private:
  View *view_;

  void SetUpProjection();
  void SetUpBackgroundColor();
  void SetUpPaintColor(QColor color);
  void SetUpLineStyle();
  void SetUpVertexStyle();

  void OrthoProjection();
  void PerspectProjection();

  double FindMaxCoordinate();


};

#endif  // OPENGL_VIEW_H
