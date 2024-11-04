#ifndef OPENGL_VIEW_H
#define OPENGL_VIEW_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Square : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Square(QWidget *parent = nullptr);
    ~Square();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
};

#endif // OPENGL_VIEW_H