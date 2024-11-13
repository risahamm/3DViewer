#ifndef OPENGL_VIEW_H
#define OPENGL_VIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "view.h"

class Object3d : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Object3d(QWidget *parent = nullptr, View *v = nullptr);
    ~Object3d();


protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    View *view_;

};

#endif // OPENGL_VIEW_H
