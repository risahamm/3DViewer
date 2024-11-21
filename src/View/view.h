#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFileDialog> // для открытия файла и чтобы записать путь
#include <QString>
//#include <QObject>

namespace s21 {
class Controller;
}

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr, s21::Controller *controller = nullptr);
    ~View();
    s21::Controller *controller;

private slots:    
    void on_Open_clicked();

private:
    Ui::View *ui;

};
#endif // VIEW_H
