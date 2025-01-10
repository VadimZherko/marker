#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QString>

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

    const int gridSize = 80;

    bool AddMark(int x , int y, int angular);
    void removeMark();
    void duplicateMark(int x, int y);
    void moveToMark(int x, int y);
    void drawBackground(QGraphicsScene*);

private slots:
    void rotateMark();
};
#endif // MAINWINDOW_H
