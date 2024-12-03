#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent, s21::Controller *controller)
        : QMainWindow(parent), controller_(controller)
        , ui_(new Ui::View) {

    ui_->setupUi(this);
    ui_->GLwidget->SetApplicationWidgetPtr(this);

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
    connect(ui_->edge_size_slider, &QSlider::sliderReleased, this, [this]() {
        ui_->GLwidget->update();
    });
    connect(ui_->vertex_size_slider, &QSlider::sliderReleased, this, [this]() {
        ui_->GLwidget->update();
    });

    /* настройки по умолчанию */
    ui_->ortho_proj_button->setChecked(true);
    ui_->solid_line_button->setChecked(true);
    ui_->dot_vertex_button->setChecked(true);

}

View::~View() {
    delete ui_;
}
void View::on_Open_clicked() {

    object_path_ = QFileDialog::getOpenFileName(this, "Choose file", "/Users/", "All files (*.*);; Object file (*.obj)");
    ui_->File_path->setText(object_path_);

    controller_->ClearObject();

    controller_->OpenFile(object_path_.toStdString());

    QString verticesCount = QString::number(controller_->getVerticesCount());
    ui_->vertices_amount->setText(verticesCount);

    QString EdgeCount = QString::number(controller_->getEdgesCount());
    ui_->edges_amount->setText(EdgeCount);

    ui_->GLwidget->update();

}


View::Perspective View::GetPerspectiveType() {

    View::Perspective perspective_type;

    if (ui_->ortho_proj_button->isChecked()) {
        perspective_type = View::Perspective::ortho;

    } else if (ui_->parall_proj_button->isChecked()) {
        perspective_type = View::Perspective::parallel;
    }

    return perspective_type;
}

View::Line View::GetLineType() {

    View::Line line_type;

    if (ui_->solid_line_button->isChecked()) {
        line_type = View::Line::solid;

    } else if (ui_->dashed_line_button->isChecked()) {
        line_type = View::Line::dashed;
    }

    return line_type;
}

View::Vertex View::GetVertexType() {

    View::Vertex vertex_type;

    if (ui_->dot_vertex_button->isChecked()) {
        vertex_type = View::Vertex::dot;

    } else if (ui_->square_vertex_button->isChecked()) {
        vertex_type = View::Vertex::square;

    } else if (ui_->no_vertex_button->isChecked()) {
        vertex_type = View::Vertex::no_vertex;
    }

    return vertex_type;
}

double View::GetVertexSize() {

    return ui_->vertex_size_slider->value();
}

double View::GetLineSize() {

    return ui_->edge_size_slider->value();
}


/* одновременно может выбрана только одна проекция */
void View::PerspectiveSelected(View::Perspective perspective) {

    if (perspective == View::Perspective::ortho) {
        ui_->ortho_proj_button->setChecked(true);
        ui_->parall_proj_button->setChecked(false);

    } else if (perspective == View::Perspective::parallel) {
        ui_->parall_proj_button->setChecked(true);
        ui_->ortho_proj_button->setChecked(false);
    }
}

/* одновременно может выбран только один тип отображения граней */
void View::LineViewSelected(View::Line line) {

    if (line == View::Line::solid) {
        ui_->solid_line_button->setChecked(true);
        ui_->dashed_line_button->setChecked(false);

    } else if (line == View::Line::dashed) {
        ui_->dashed_line_button->setChecked(true);
        ui_->solid_line_button->setChecked(false);
    }
}

/* одновременно может выбран только один тип отображения вершин */
void View::VertexViewSelected(View::Vertex vertex) {

    if (vertex == View::Vertex::dot) {
        ui_->dot_vertex_button->setChecked(true);
        ui_->square_vertex_button->setChecked(false);
        ui_->no_vertex_button->setChecked(false);

    } else if (vertex == View::Vertex::square) {
        ui_->square_vertex_button->setChecked(true);
        ui_->dot_vertex_button->setChecked(false);
        ui_->no_vertex_button->setChecked(false);

    } else if (vertex == View::Vertex::no_vertex) {
        ui_->no_vertex_button->setChecked(true);
        ui_->dot_vertex_button->setChecked(false);
        ui_->square_vertex_button->setChecked(false);
    }
}

