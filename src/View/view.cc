#include "view.h"
#include "./ui_view.h"

View::View(QWidget *parent)
        : QMainWindow(parent)
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
}

