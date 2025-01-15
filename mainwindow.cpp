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
    ui->workArea->translate(500,1500);//Расчёт
    drawBackground(scene);
    ui->workArea->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawBackground(QGraphicsScene* scene)
{
    QColor color(225,79,0,255);
    QPen pen(color,1);

    auto left = scene->sceneRect().left();
    auto right = scene->sceneRect().right();
    auto top = scene->sceneRect().top();
    auto bottom = scene->sceneRect().bottom();

    for(int y = top; y < bottom; y += gridSize) //Grid
    {
        scene->addLine(left, y, right, y, pen);
    }

    for(int x = left; x < right; x += gridSize) //Grid
    {
        scene->addLine(x, top, x, bottom, pen);
    }

    pen.setWidthF(0.2);

    for(int y = top; y < bottom; y += gridSize / 5) //Grid
    {
        scene->addLine(left, y, right, y, pen);
    }

    for(int x = left; x < right; x += gridSize / 5) //Grid
    {
        scene->addLine(x, top, x, bottom, pen);
    }

    pen.setWidth(3);
    scene->addLine(0, top, 0, bottom, pen); //coordinate axis Y
    scene->addLine(left, 0, right, 0, pen); //coordinate axis X

    color.setRgb(255,255,255,255);
    QPen pen_text(color);

    for(int x = left, i = -10; x < right; x+= gridSize, i++) //Lines on axis X
    {
        if(i == 0) continue;
        scene->addLine(x, -3, x, 3, pen);

        QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(i));
        text->setPen(pen_text);
        text->setPos(x, 10);
        scene->addItem(text);
    }

    for(int y = bottom, i = -10; y > top; y -= gridSize, i++) //Lines on axis Y
    {
        if(i == 0) continue;
        scene->addLine(-3, y, 3, y, pen);

        QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(i));
        text->setPen(pen_text);
        text->setPos(10, y);
        scene->addItem(text);
    }

    QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(0));
    text->setPen(pen_text);
    text->setPos(10, 10);
    scene->addItem(text);
}

bool MainWindow::addMark(int x, int y, int angular)
{
    const QTransform imp;
    /*if(scene->itemAt(x,y,imp) == nullptr)
    {

    }
    else
    {
        QMessageBox::warning(this,"Error", "There is already a mark at this place");
        return false;
    }*/
    Mark* new_mark = new Mark(x, y, angular);
    scene->addItem(new_mark);
    ui->workArea->setScene(scene);
    return true;
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

void MainWindow::duplicateMark(int x, int y)
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

void MainWindow::moveToMark(int x, int y)
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



