#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QString>

#include "dialog.h"
#include "mark.h"
#include "scene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Dialog* DialogWidget = new Dialog;
    Scene* scene = new Scene;

    const int gridSize = 40;

    bool addMark(double x , double y, int angular);
    bool checkInputMark(double, double);
    void removeMark();
    void duplicateMark(double x, double y);
    void moveToMark(double x, double y);

private slots:
    void rotateMark();
};
#endif // MAINWINDOW_H
