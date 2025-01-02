#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

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

    void drawMark(Mark*);

private:
    Ui::MainWindow *ui;
    Dialog* DialogWidget = new Dialog;
    QGraphicsScene *scene = new QGraphicsScene();

    QVector<Mark*> Marks;


    void AddMark(int x , int y);
    void drawBackground(QGraphicsScene*);
};
#endif // MAINWINDOW_H
