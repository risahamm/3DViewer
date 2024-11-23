#ifndef OPENGL_VIEW_H
#define OPENGL_VIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "view.h"

class Object3d : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:

    Object3d(QWidget *parent = nullptr);
    ~Object3d();

    void SetApplicationWidgetPtr(View *ptr);


protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
    double FindMaxCoordinate();

private:
    View *view_;

    void SetUpPerspective();

};

#endif // OPENGL_VIEW_H
