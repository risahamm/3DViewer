#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent, s21::Controller *controller)
        : QMainWindow(parent), controller_(controller)
        , ui_(new Ui::View) {

    ui_->setupUi(this);
    ui_->GLwidget->SetApplicationWidgetPtr(this);

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
        PerspectiveSelected(View::Perspective::ortho);
        ui_->GLwidget->update();
    });
    connect(ui_->parall_proj_button, &QPushButton::clicked, this, [this]() {
        PerspectiveSelected(View::Perspective::parallel);
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

    /* настройки по умолчанию */
    ui_->ortho_proj_button->setChecked(true);
    ui_->solid_line_button->setChecked(true);
    ui_->dot_vertex_button->setChecked(true);
    current_settings.perspective = View::Perspective::ortho;
    current_settings.line = View::Line::solid;
    current_settings.line_size = ui_->edge_size_slider->value(); // по умолчанию 2px
    current_settings.line_color = SetColor("white");
    current_settings.vertex = View::Vertex::dot;
    current_settings.vertex_size = ui_->vertex_size_slider->value(); // по умолчанию 2px
    current_settings.vertex_color = SetColor("white");
    current_settings.background_color = SetColor("black");
}

View::~View() {
    delete ui_;
}
void View::on_Open_clicked() {

    object_path_ = QFileDialog::getOpenFileName(this, "Choose file", "/Users/", "All files (*.*);; Object file (*.obj)");
    ui_->File_path->setText(object_path_);

    /* Находим индекс последнего символа '/' */
    int last_slash_idx = object_path_.lastIndexOf('/');
    ui_->file_name_label->setText(object_path_.mid(last_slash_idx + 1));

    controller_->ClearObject();

    controller_->OpenFile(object_path_.toStdString());

    QString verticesCount = QString::number(controller_->getVerticesCount());
    ui_->vertices_amount->setText(verticesCount);

    QString EdgeCount = QString::number(controller_->getEdgesCount());
    ui_->edges_amount->setText(EdgeCount);

    ui_->GLwidget->update();

}


/* одновременно может выбрана только одна проекция */
void View::PerspectiveSelected(View::Perspective perspective) {

    if (perspective == View::Perspective::ortho) {
        ui_->ortho_proj_button->setChecked(true);
        ui_->parall_proj_button->setChecked(false);
        current_settings.perspective = View::Perspective::ortho;

    } else if (perspective == View::Perspective::parallel) {
        ui_->parall_proj_button->setChecked(true);
        ui_->ortho_proj_button->setChecked(false);
        current_settings.perspective = View::Perspective::parallel;
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

View::Color View::SetColor() {

    QColor selected_color = QColorDialog::getColor(Qt::black, this, "Select color");

    View::Color return_color;

    return_color.red = selected_color.redF();
    return_color.green = selected_color.greenF();
    return_color.blue = selected_color.blueF();
    return_color.alpha = selected_color.alphaF();

    return return_color;
}

View::Color View::SetColor(QColor color) {

    View::Color return_color;

    return_color.red = color.redF();
    return_color.green = color.greenF();
    return_color.blue = color.blueF();
    return_color.alpha = color.alphaF();

    return return_color;
}



