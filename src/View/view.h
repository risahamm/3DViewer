#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QString>
#include <QObject>
#include <QColor>
#include <QColorDialog>
#include <QSettings>
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

    struct Settings {
        View::Perspective perspective;
        View::Line line;
        float line_size;
        QColor line_color;
        View::Vertex vertex;
        float vertex_size;
        QColor vertex_color;
        QColor background_color;
    };

    View(QWidget *parent = nullptr, s21::Controller *controller = nullptr);
    ~View();

    friend class Object3d;

    Settings current_settings; ///< текущие настройки

    Ui::View* GetUiPtr() { return ui_;}



private slots:

    void OpenClicked();
    void PerspectiveSelected(View::Perspective perspective);
    void LineViewSelected(View::Line line);
    void VertexViewSelected(View::Vertex vertex);
    QColor SetColor();

private:

    s21::Controller *controller_;
    Ui::View *ui_;
    QString object_path_;

    QSettings *user_settings_;

    void SaveSettings();
    void LoadSettings();

};
#endif // VIEW_H
