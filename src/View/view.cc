#include "view.h"
#include "./ui_view.h"
#include "Controller/controller.h"

View::View(QWidget *parent, s21::Controller *controller)
        : QMainWindow(parent), controller_(controller)
        , ui(new Ui::View)
{

    ui->setupUi(this);
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

//    qInfo() << "test" << controller_->check1 << Qt::endl;

//    QString verticesCount = QString::number(controller_->getVerticesCount());
//    ui->vertices_amount->setText(verticesCount);

//    QString EdgeCount = QString::number(controller_->getVerticesCount());
//    ui->edges_amount->setText(EdgeCount);
}

