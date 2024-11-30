#include "view.h"
#include "ui_view.h"

View::View(QWidget *parent, s21::Controller *controller)
        : QMainWindow(parent), controller(controller)
        , ui(new Ui::View) {

    ui->setupUi(this);
    ui->GLwidget->SetApplicationWidgetPtr(this);
}

View::~View() {
    delete ui;
}
void View::on_Open_clicked() {

    object_path = QFileDialog::getOpenFileName(this, "Choose file", "/Users/", "All files (*.*);; Object file (*.obj)");
    ui->File_path->setText(object_path);

    controller->ClearObject();

    controller->OpenFile(object_path.toStdString());

    QString verticesCount = QString::number(controller->getVerticesCount());
    ui->vertices_amount->setText(verticesCount);

    QString EdgeCount = QString::number(controller->getEdgesCount());
    ui->edges_amount->setText(EdgeCount);

    ui->GLwidget->update();

}

