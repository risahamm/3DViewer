#ifndef VIEW_H
#define VIEW_H

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QTimer>
#include <QVBoxLayout>

#include "Controller/controller.h"

namespace s21 {
class Controller;
}

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  enum class Projection { ortho, perspect };

  enum class Line { solid, dashed };

  enum class Vertex { dot, square, no_vertex };

  struct Settings {
    View::Projection projection;
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

  Settings current_settings;  ///< текущие настройки

  Ui::View *GetUiPtr() { return ui_; }

 private slots:

  void OpenClicked();
  void ProjectionSelected(View::Projection perspective);
  void LineViewSelected(View::Line line);
  void VertexViewSelected(View::Vertex vertex);
  QColor SetColor();

  void MoveUp();
  void MoveUpReleased();
  void MoveDown();
  void MoveDownReleased();
  void MoveRight();
  void MoveRightReleased();
  void MoveLeft();
  void MoveLeftReleased();

 private:
  s21::Controller *controller_;
  Ui::View *ui_;
  QString object_path_;

  QSettings *user_settings_;

  QTimer action_tmr_;  ///< таймер для зажатия transformations buttons

  double x_step_;  ///< шаг для move
  double y_step_;

  double current_scale_; ///< текущий масштаб отображения объекта

  void ConnectButtons();
  void SaveSettings();
  void LoadSettings();
};
#endif  // VIEW_H
