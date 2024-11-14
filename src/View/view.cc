#include "view.h"
#include "./ui_view.h"
#include "Controller/controller.h"

View::View(QWidget *parent, s21::Controller *controller)
        : QMainWindow(parent), controller(controller)
        , ui(new Ui::View)
{

    ui->setupUi(this);
    ui->widget->setApplicationWidgetPtr(this);
}

View::~View()
{
    delete ui;
}
void View::on_Open_clicked()
{
    QString path;
    path = QFileDialog::getOpenFileName(this, "Choose file", "/Users/", "All files (*.*);; Object file (*.obj)");
    ui->File_path->setText(path);

    controller->OpenFile(path.toStdString());

    QString verticesCount = QString::number(controller->getVerticesCount());
    ui->vertices_amount->setText(verticesCount);

    QString EdgeCount = QString::number(controller->getEdgesCount());
    ui->edges_amount->setText(EdgeCount);
}

