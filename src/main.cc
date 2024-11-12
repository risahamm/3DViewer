#include "View/view.h"
#include "Controller/controller.h"
#include "Model/object.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Object object;
    s21::Controller controller(&object);
    View w(nullptr, &controller);
    w.show();
    return a.exec();
}
