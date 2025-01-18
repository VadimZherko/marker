#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->addMarkButton, SIGNAL(clicked()), this->DialogWidget, SLOT(showAddMarkDialog()));
    QObject::connect(ui->duplicateMarkButton, SIGNAL(clicked()), this->DialogWidget, SLOT(showDuplicateMarkDialog()));
    QObject::connect(ui->moveToMarkButton, SIGNAL(clicked()), this->DialogWidget, SLOT(showMoveToMarkDialog()));
    QObject::connect(ui->rotateMarkButton, SIGNAL(clicked()), this, SLOT(rotateMark()));

    QObject::connect(DialogWidget, &Dialog::dataReady, this, &MainWindow::addMark);
    QObject::connect(DialogWidget, &Dialog::dataDuplicateReady, this, &MainWindow::duplicateMark);
    QObject::connect(DialogWidget, &Dialog::dataMoveToReady, this, &MainWindow::moveToMark);

    QObject::connect(ui->removeMarkButton, &QPushButton::clicked,this, &MainWindow::removeMark);

    scene->setSceneRect(-gridSize * 10, -gridSize * 40, gridSize * 50, gridSize * 50);
    ui->workArea->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::addMark(double x, double y, int angular)
{
    if(checkInputMark(x, y))
    {
        Mark* new_mark = new Mark(x, y, angular);
        scene->addItem(new_mark);
        return true;
    }
    else
    {
        return false;
    }
}

void MainWindow::removeMark()
{
    auto selectedItems = scene->selectedItems();
    for(auto item : selectedItems)
    {
        scene->removeItem(item);
        delete item;
    }
}

void MainWindow::duplicateMark(double x, double y)
{
    auto selectedItems = scene->selectedItems();
    if (!selectedItems.empty())
    {
        for(auto item : selectedItems)
        {
            Mark* markItem = qgraphicsitem_cast<Mark*>(item);
            addMark(markItem->getX() + x, markItem->getY() + y, markItem->getAngular());
        }
    }
    else
    {
        QMessageBox::warning(this,"Error", "No items selected");
    }
}

void MainWindow::moveToMark(double x, double y)
{
    auto selectedItems = scene->selectedItems();
    if (!selectedItems.empty())
    {

        Mark* markItem = qgraphicsitem_cast<Mark*>(selectedItems[0]);
        if(addMark(x, y, markItem->getAngular())) delete markItem;
    }
    else
    {
        QMessageBox::warning(this,"Error", "No items selected");
    }
}

void MainWindow::rotateMark()
{
    auto selectedItems = scene->selectedItems();
    if (!selectedItems.empty())
    {
        for(auto item : selectedItems)
        {
            Mark* markItem = qgraphicsitem_cast<Mark*>(item);
            markItem->getAngular() == 270  ? markItem->setAngular(0) : markItem->setAngular(markItem->getAngular() + 90);
        }
    }
    else
    {
        QMessageBox::warning(this,"Error", "No items selected");
    }
}


bool MainWindow::checkInputMark(double x, double y)
{
    auto collisingItems = scene->items(x - 10, y + 20, x + 10, y - 20, Qt::IntersectsItemShape, Qt::AscendingOrder);
    if(!collisingItems.empty())
    {
        QMessageBox::warning(this,"Error", "Another mark is located at the specified coordinates");
        return false;
    }

    auto left = scene->sceneRect().left();
    auto right = scene->sceneRect().right();
    auto top = scene->sceneRect().top();
    auto bottom = scene->sceneRect().bottom();

    x = (int)x + gridSize;
    y = (int)y + gridSize;

    if (x < left && y < top) {
        scene->setSceneRect(x - 3 * gridSize, y - 3 * gridSize, right - x + 3 * gridSize, bottom - y + 3 * gridSize);
        scene->invalidate();
        return true;
    }
    if (x > right && y < top) {
        scene->setSceneRect(left, y - 3 * gridSize, x - left + 3 * gridSize, bottom - y + 3 * gridSize);
        scene->invalidate();
        return true;
    }
    if (x > right && y > bottom) {
        scene->setSceneRect(left, top, x - left + 3 * gridSize, y - top + 3 * gridSize);
        scene->invalidate();
        return true;
    }
    if (x < left && y > bottom) {
        scene->setSceneRect(x - 3 * gridSize, top, right - x + 3 * gridSize, y - top + 3 * gridSize);
        scene->invalidate();
        return true;
    }

    return true;
}



