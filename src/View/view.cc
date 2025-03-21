#include "view.h"

#include "ui_view.h"

s21::View::View(QWidget *parent, s21::Controller *controller)
    : QMainWindow(parent),
      controller_(controller),
      user_settings_(new QSettings("s21Soft", "3D Viewer")),
      ui_(new Ui::View) {
  ui_->setupUi(this);
  ui_->GLwidget->SetApplicationWidgetPtr(this);

  ConnectButtons();

  /* восстановим предыдущие настройки */
  LoadSettings();
}

s21::View::~View() {
  SaveSettings();
  delete ui_;
}

void s21::View::ConnectButtons() {
  connect(ui_->Open, &QPushButton::clicked, this, &View::OpenClicked);

  connect(ui_->moveYplus, &QPushButton::pressed, this, [this]() {
    connect(&action_tmr_, &QTimer::timeout, this, &View::MoveUp);
    action_tmr_.start(50);
  });

  connect(ui_->moveYplus, &QPushButton::released, this, &View::MoveUpReleased);

  connect(ui_->moveYminus, &QPushButton::pressed, this, [this]() {
    connect(&action_tmr_, &QTimer::timeout, this, &View::MoveDown);
    action_tmr_.start(50);
  });

  connect(ui_->moveYminus, &QPushButton::released, this,
          &View::MoveDownReleased);

  connect(ui_->moveXplus, &QPushButton::pressed, this, [this]() {
    connect(&action_tmr_, &QTimer::timeout, this, &View::MoveRight);
    action_tmr_.start(50);
  });

  connect(ui_->moveXplus, &QPushButton::released, this,
          &View::MoveRightReleased);

  connect(ui_->moveXminus, &QPushButton::pressed, this, [this]() {
    connect(&action_tmr_, &QTimer::timeout, this, &View::MoveLeft);
    action_tmr_.start(50);
  });

  connect(ui_->moveXminus, &QPushButton::released, this,
          &View::MoveLeftReleased);

  connect(ui_->rotate_left_button, &QPushButton::pressed, this, [this]() {
    connect(&action_tmr_, &QTimer::timeout, this, &View::RotateLeft);
    action_tmr_.start(50);
  });

  connect(ui_->rotate_left_button, &QPushButton::released, this,
          &View::RotateLeftReleased);

  connect(ui_->rotate_right_button, &QPushButton::pressed, this, [this]() {
    connect(&action_tmr_, &QTimer::timeout, this, &View::RotateRight);
    action_tmr_.start(50);
  });

  connect(ui_->rotate_right_button, &QPushButton::released, this,
          &View::RotateRightReleased);

  connect(ui_->rotate_up_button, &QPushButton::pressed, this, [this]() {
    connect(&action_tmr_, &QTimer::timeout, this, &View::RotateUp);
    action_tmr_.start(50);
  });

  connect(ui_->rotate_up_button, &QPushButton::released, this,
          &View::RotateUpReleased);

  connect(ui_->rotate_down_button, &QPushButton::pressed, this, [this]() {
    connect(&action_tmr_, &QTimer::timeout, this, &View::RotateDown);
    action_tmr_.start(50);
  });

  connect(ui_->rotate_down_button, &QPushButton::released, this,
          &View::RotateDownReleased);

  connect(ui_->rotate_z_plus_button, &QPushButton::pressed, this, [this]() {
    connect(&action_tmr_, &QTimer::timeout, this, &View::RotateClckWise);
    action_tmr_.start(50);
  });

  connect(ui_->rotate_z_plus_button, &QPushButton::released, this,
          &View::RotateClckWiseReleased);

  connect(ui_->rotate_z_minus_button, &QPushButton::pressed, this, [this]() {
    connect(&action_tmr_, &QTimer::timeout, this, &View::RotateCClckWise);
    action_tmr_.start(50);
  });

  connect(ui_->rotate_z_minus_button, &QPushButton::released, this,
          &View::RotateCClckWiseReleased);

  connect(ui_->zoomInOut, &QSlider::valueChanged, this, [this]() {
    controller_->Zoom(static_cast<double>(ui_->zoomInOut->value()) /
                      current_scale_);
    current_scale_ = static_cast<double>(ui_->zoomInOut->value());
    ui_->GLwidget->update();
  });

  connect(ui_->background_color_button, &QPushButton::clicked, this, [this]() {
    current_settings.background_color = SetColor();
    ui_->GLwidget->update();
  });

  connect(ui_->line_color_button, &QPushButton::clicked, this, [this]() {
    current_settings.line_color = SetColor();
    ui_->GLwidget->update();
  });

  connect(ui_->vertex_color_button, &QPushButton::clicked, this, [this]() {
    current_settings.vertex_color = SetColor();
    ui_->GLwidget->update();
  });

  connect(ui_->ortho_proj_button, &QPushButton::clicked, this, [this]() {
    ProjectionSelected(View::Projection::ortho);
    ui_->GLwidget->update();
  });

  connect(ui_->perspect_proj_button, &QPushButton::clicked, this, [this]() {
    ProjectionSelected(View::Projection::perspect);
    ui_->GLwidget->update();
  });

  connect(ui_->solid_line_button, &QPushButton::clicked, this, [this]() {
    LineViewSelected(View::Line::solid);
    ui_->GLwidget->update();
  });

  connect(ui_->dashed_line_button, &QPushButton::clicked, this, [this]() {
    LineViewSelected(View::Line::dashed);
    ui_->GLwidget->update();
  });

  connect(ui_->dot_vertex_button, &QPushButton::clicked, this, [this]() {
    VertexViewSelected(View::Vertex::dot);
    ui_->GLwidget->update();
  });

  connect(ui_->square_vertex_button, &QPushButton::clicked, this, [this]() {
    VertexViewSelected(View::Vertex::square);
    ui_->GLwidget->update();
  });

  connect(ui_->no_vertex_button, &QPushButton::clicked, this, [this]() {
    VertexViewSelected(View::Vertex::no_vertex);
    ui_->GLwidget->update();
  });

  connect(ui_->edge_size_slider, &QSlider::valueChanged, this, [this]() {
    current_settings.line_size = ui_->edge_size_slider->value();
    ui_->GLwidget->update();
  });

  connect(ui_->vertex_size_slider, &QSlider::valueChanged, this, [this]() {
    current_settings.vertex_size = ui_->vertex_size_slider->value();
    ui_->GLwidget->update();
  });
}

void s21::View::OpenClicked() {
  object_path_ = QFileDialog::getOpenFileName(
      this, "Choose file", "/Users/", "All files (*.*);; Object file (*.obj)");
  ui_->message_window->setText(object_path_);

  /* находим индекс последнего символа '/' */
  int last_slash_idx = object_path_.lastIndexOf('/');
  ui_->file_name_label->setText(object_path_.mid(last_slash_idx + 1));

  ui_->zoomInOut->setValue(100);
  current_scale_ = 100.0;

  /* если файл обработан успешно */
  if (controller_->OpenFile(object_path_.toStdString())) {
    QString verticesCount = QString::number(controller_->GetVerticesCount());
    ui_->vertices_amount->setText(verticesCount);

    QString EdgeCount = QString::number(controller_->GetEdgesCount());
    ui_->edges_amount->setText(EdgeCount);

    x_step = 0.0;
    y_step = 0.0;
    z_step = 0.0;

    ui_->GLwidget->update();

  } else {
    controller_->ClearObject();
    ui_->message_window->setText("Error: Invalid object file: " + object_path_);
  }
}

/* одновременно может выбрана только одна проекция */
void s21::View::ProjectionSelected(View::Projection projection) {
  if (projection == View::Projection::ortho) {
    ui_->ortho_proj_button->setChecked(true);
    ui_->perspect_proj_button->setChecked(false);
    current_settings.projection = View::Projection::ortho;

  } else if (projection == View::Projection::perspect) {
    ui_->perspect_proj_button->setChecked(true);
    ui_->ortho_proj_button->setChecked(false);
    current_settings.projection = View::Projection::perspect;
  }
}

/* одновременно может выбран только один тип отображения граней */
void s21::View::LineViewSelected(View::Line line) {
  if (line == View::Line::solid) {
    ui_->solid_line_button->setChecked(true);
    ui_->dashed_line_button->setChecked(false);
    current_settings.line = View::Line::solid;

  } else if (line == View::Line::dashed) {
    ui_->dashed_line_button->setChecked(true);
    ui_->solid_line_button->setChecked(false);
    current_settings.line = View::Line::dashed;
  }
}

/* одновременно может выбран только один тип отображения вершин */
void s21::View::VertexViewSelected(View::Vertex vertex) {
  if (vertex == View::Vertex::dot) {
    ui_->dot_vertex_button->setChecked(true);
    ui_->square_vertex_button->setChecked(false);
    ui_->no_vertex_button->setChecked(false);
    current_settings.vertex = View::Vertex::dot;

  } else if (vertex == View::Vertex::square) {
    ui_->square_vertex_button->setChecked(true);
    ui_->dot_vertex_button->setChecked(false);
    ui_->no_vertex_button->setChecked(false);
    current_settings.vertex = View::Vertex::square;

  } else if (vertex == View::Vertex::no_vertex) {
    ui_->no_vertex_button->setChecked(true);
    ui_->dot_vertex_button->setChecked(false);
    ui_->square_vertex_button->setChecked(false);
    current_settings.vertex = View::Vertex::no_vertex;
  }
}

QColor s21::View::SetColor() {
  QColor selected_color =
      QColorDialog::getColor(Qt::black, this, "Select color");

  return selected_color;
}

void s21::View::SaveSettings() {
  user_settings_->setValue("ortho_proj_button_checked",
                           ui_->ortho_proj_button->isChecked());
  user_settings_->setValue("parall_proj_button_checked",
                           ui_->perspect_proj_button->isChecked());
  user_settings_->setValue("solid_line_button_checked",
                           ui_->solid_line_button->isChecked());
  user_settings_->setValue("dashed_line_button_checked",
                           ui_->dashed_line_button->isChecked());
  user_settings_->setValue("dot_vertex_button_checked",
                           ui_->dot_vertex_button->isChecked());
  user_settings_->setValue("square_vertex_button_checked",
                           ui_->square_vertex_button->isChecked());
  user_settings_->setValue("no_vertex_button_checked",
                           ui_->no_vertex_button->isChecked());

  user_settings_->setValue("projection",
                           static_cast<int>(current_settings.projection));
  user_settings_->setValue("line_type",
                           static_cast<int>(current_settings.line));
  user_settings_->setValue("line_size", ui_->edge_size_slider->value());
  user_settings_->setValue("vertex_type",
                           static_cast<int>(current_settings.vertex));
  user_settings_->setValue("vertex_size", ui_->vertex_size_slider->value());

  user_settings_->setValue("line_color", current_settings.line_color.name());
  user_settings_->setValue("vertex_color",
                           current_settings.vertex_color.name());
  user_settings_->setValue("background_color",
                           current_settings.background_color.name());
}

void s21::View::LoadSettings() {
  /* второй параметр - настройки по умолчанию */
  ui_->ortho_proj_button->setChecked(
      user_settings_->value("ortho_proj_button_checked", true).toBool());
  ui_->perspect_proj_button->setChecked(
      user_settings_->value("parall_proj_button_checked", false).toBool());
  ui_->solid_line_button->setChecked(
      user_settings_->value("solid_line_button_checked", true).toBool());
  ui_->dashed_line_button->setChecked(
      user_settings_->value("dashed_line_button_checked", false).toBool());
  ui_->dot_vertex_button->setChecked(
      user_settings_->value("dot_vertex_button_checked", true).toBool());
  ui_->square_vertex_button->setChecked(
      user_settings_->value("square_vertex_button_checked", false).toBool());
  ui_->no_vertex_button->setChecked(
      user_settings_->value("no_vertex_button_checked", false).toBool());

  current_settings.projection = static_cast<View::Projection>(
      user_settings_
          ->value("projection", static_cast<int>(View::Projection::ortho))
          .toInt());
  current_settings.line = static_cast<View::Line>(
      user_settings_->value("line_type", static_cast<int>(View::Line::solid))
          .toInt());
  current_settings.line_size = user_settings_->value("line_size", 2).toFloat();
  ui_->edge_size_slider->setValue(
      user_settings_->value("line_size", 2).toInt());
  current_settings.vertex = static_cast<View::Vertex>(
      user_settings_->value("vertex_type", static_cast<int>(View::Vertex::dot))
          .toInt());
  current_settings.vertex_size =
      user_settings_->value("vertex_size", 2).toFloat();
  ui_->vertex_size_slider->setValue(
      user_settings_->value("vertex_size", 2).toInt());

  current_settings.line_color = QColor(
      user_settings_->value("line_color", "#FFFFFF").toString());  // white
  current_settings.vertex_color = QColor(
      user_settings_->value("vertex_color", "#FFFFFF").toString());  // white
  current_settings.background_color =
      QColor(user_settings_->value("background_color", "#000000")
                 .toString());  // black
}

void s21::View::MoveUp() {
  y_step += controller_->GetMaxCoordinateY() * 0.1;
  ui_->GLwidget->update();
}

void s21::View::MoveUpReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::MoveUp);
}

void s21::View::MoveDown() {
  y_step -= controller_->GetMaxCoordinateY() * 0.1;
  ui_->GLwidget->update();
}

void s21::View::MoveDownReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::MoveDown);
}

void s21::View::MoveRight() {
  x_step += controller_->GetMaxCoordinateX() * 0.1;
  ui_->GLwidget->update();
}

void s21::View::MoveRightReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::MoveRight);
}

void s21::View::MoveLeft() {
  x_step -= controller_->GetMaxCoordinateX() * 0.1;
  ui_->GLwidget->update();
}

void s21::View::MoveLeftReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::MoveLeft);
}

void s21::View::RotateLeft() {
  controller_->RoateYLeft(5);
  ui_->GLwidget->update();
}

void s21::View::RotateLeftReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::RotateLeft);
}

void s21::View::RotateRight() {
  controller_->RoateYRight(5);
  ui_->GLwidget->update();
}

void s21::View::RotateRightReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::RotateRight);
}

void s21::View::RotateUp() {
  controller_->RoateXUp(5);
  ui_->GLwidget->update();
}

void s21::View::RotateUpReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::RotateUp);
}

void s21::View::RotateDown() {
  controller_->RoateXDown(5);
  ui_->GLwidget->update();
}

void s21::View::RotateDownReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::RotateDown);
}

void s21::View::RotateClckWise() {
  controller_->RoateZClckWs(5);
  ui_->GLwidget->update();
}

void s21::View::RotateClckWiseReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::RotateClckWise);
}

void s21::View::RotateCClckWise() {
  controller_->RoateZCClckWs(5);
  ui_->GLwidget->update();
}

void s21::View::RotateCClckWiseReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::RotateCClckWise);
}
