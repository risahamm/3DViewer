#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QString>
#include <QObject>
#include <QColor>
#include <QColorDialog>
#include "Controller/controller.h"


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

    struct Color {
        float red;
        float green;
        float blue;
        float alpha;
    };

    struct Settings {
        View::Perspective perspective;
        View::Line line;
        float line_size;
        View::Color line_color;
        View::Vertex vertex;
        float vertex_size;
        View::Color vertex_color;
        View::Color background_color;
    };

    View(QWidget *parent = nullptr, s21::Controller *controller = nullptr);
    ~View();

    friend class Object3d;

    Settings current_settings; ///< текущие настройки

    Ui::View* GetUiPtr() { return ui_;}



private slots:

    void on_Open_clicked();
    void PerspectiveSelected(View::Perspective perspective);
    void LineViewSelected(View::Line line);
    void VertexViewSelected(View::Vertex vertex);
    View::Color SetColor();
    View::Color SetColor(QColor color);

private:

    s21::Controller *controller_;
    Ui::View *ui_;
    QString object_path_;



};
#endif // VIEW_H
