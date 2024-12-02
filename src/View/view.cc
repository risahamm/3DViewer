#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent, s21::Controller *controller)
        : QMainWindow(parent), controller_(controller)
        , ui_(new Ui::View) {

    ui_->setupUi(this);
    ui_->GLwidget->SetApplicationWidgetPtr(this);

    connect(ui_->ortho_proj_button, &QPushButton::clicked, this, [this]() {
        PerspectiveSelected(View::Perspective::ortho);
    });
    connect(ui_->parall_proj_button, &QPushButton::clicked, this, [this]() {
        PerspectiveSelected(View::Perspective::parallel);
    });

    connect(ui_->solid_line_button, &QPushButton::clicked, this, [this]() {
        LineViewSelected(View::Line::solid);
    });
    connect(ui_->dashed_line_button, &QPushButton::clicked, this, [this]() {
        LineViewSelected(View::Line::dashed);
    });

    /* настройки по умолчанию */
    ui_->ortho_proj_button->setChecked(true);
    ui_->solid_line_button->setChecked(true);

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


/* одновременно может выбрана только одна проекция */
void View::PerspectiveSelected(View::Perspective perspective) {

    if (perspective == View::Perspective::ortho) {
        ui_->ortho_proj_button->setChecked(true);
        ui_->parall_proj_button->setChecked(false);

    } else if (ui_->parall_proj_button->isChecked()) {
        ui_->parall_proj_button->setChecked(true);
        ui_->ortho_proj_button->setChecked(false);
    }
}

/* одновременно может выбрана только один тип отображения граней */
void View::LineViewSelected(View::Line line) {

    if (line == View::Line::solid) {
        ui_->solid_line_button->setChecked(true);
        ui_->dashed_line_button->setChecked(false);

    } else if (ui_->dashed_line_button->isChecked()) {
        ui_->dashed_line_button->setChecked(true);
        ui_->solid_line_button->setChecked(false);
    }
}

