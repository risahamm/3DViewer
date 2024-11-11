#include "View/view.h"
#include "Controller/controller.h"
#include "Model/object.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Object object;
    qInfo() << "test" << object.check << Qt::endl;
    s21::Controller controller(&object);
//    qInfo() << "test" << controller.check1 << Qt::endl;
    View w(nullptr, &controller);
    w.show();
    return a.exec();
}
