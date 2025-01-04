#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>

#include "dialog.h"
#include "mark.h"

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
    QGraphicsScene *scene = new QGraphicsScene();

    void AddMark(int x , int y, int angular);
    void removeMark();
    void drawBackground(QGraphicsScene*);
};
#endif // MAINWINDOW_H
