#include "View/view.h"
#include "Controller/controller.h"
#include "Model/object.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icons/app_icon.png"));

    s21::Object object;
    s21::Controller controller(&object);
    View view(nullptr, &controller);

    view.show();
    view.setWindowTitle("3D Viewer");

    return app.exec();
}
