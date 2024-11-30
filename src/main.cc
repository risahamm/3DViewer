#include "View/view.h"
#include "Controller/controller.h"
#include "Model/object.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Object object;
    s21::Controller controller(&object);
    View app(nullptr, &controller);

    app.setWindowIcon(QIcon(":/View/icons/app_icon.png"));
    app.setWindowTitle("3D Viewer");

    app.show();
    return a.exec();
}
