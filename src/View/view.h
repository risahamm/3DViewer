#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFileDialog> // для открытия файла и чтобы записать путь
#include <QString>
#include <QObject>
#include "Controller/controller.h"
//#include "opengl_view.h"


namespace s21 {
class Controller;
}

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow {
    Q_OBJECT

public:

    enum class Perspective {
        ortho,
        parallel
    };

    enum class Line {
        solid,
        dashed
    };

    enum class Vertex {
        dot,
        square,
        no_vertex
    };

    View(QWidget *parent = nullptr, s21::Controller *controller = nullptr);
    ~View();

    friend class Object3d;

    Perspective GetPerspectiveType();
    Line GetLineType();



private slots:

    void on_Open_clicked();
    void PerspectiveSelected(View::Perspective perspective);
    void LineViewSelected(View::Line line);

private:

    s21::Controller *controller_;
    Ui::View *ui_;
    QString object_path_;


};
#endif // VIEW_H
