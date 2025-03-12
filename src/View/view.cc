#include "view.h"

#include "ui_view.h"

View::View(QWidget *parent, s21::Controller *controller)
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

View::~View() {
  SaveSettings();
  delete ui_;
}

void View::OpenClicked() {
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

    x_step_ = controller_->GetMaxCoordinateX() * 0.1;
    y_step_ = controller_->GetMaxCoordinateY() * 0.1;

    ui_->GLwidget->update();

  } else {
    controller_->ClearObject();
    ui_->message_window->setText("Error: Invalid object file: " + object_path_);
  }
}

/* одновременно может выбрана только одна проекция */
void View::ProjectionSelected(View::Projection projection) {
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
void View::LineViewSelected(View::Line line) {
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
void View::VertexViewSelected(View::Vertex vertex) {
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

QColor View::SetColor() {
  QColor selected_color =
      QColorDialog::getColor(Qt::black, this, "Select color");

  return selected_color;
}

void View::SaveSettings() {
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

void View::LoadSettings() {
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

void View::ConnectButtons() {
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

  connect(ui_->zoomInOut, &QSlider::valueChanged, this, [this]() {

    controller_->Zoom(static_cast<double>(ui_->zoomInOut->value()) / current_scale_);

//    if (ui_->zoomInOut->value() > current_scale_) {
//        controller_->Zoom(1.1);
//    } else {
//        controller_->Zoom(0.9);
//    }
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

void View::MoveUp() {
  controller_->MoveYUp(y_step_);
  ui_->GLwidget->update();
}

void View::MoveUpReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::MoveUp);
}

void View::MoveDown() {
  controller_->MoveYDown(y_step_);
  ui_->GLwidget->update();
}

void View::MoveDownReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::MoveDown);
}

void View::MoveRight() {
//  controller_->MoveXRight(x_step_);
    ui_->GLwidget->MoveXAxis(x_step_);
  ui_->GLwidget->update();
}

void View::MoveRightReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::MoveRight);
}

void View::MoveLeft() {
  controller_->MoveXLeft(x_step_);
  ui_->GLwidget->update();
}

void View::MoveLeftReleased() {
  action_tmr_.stop();
  disconnect(&action_tmr_, &QTimer::timeout, this, &View::MoveLeft);
}
