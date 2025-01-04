#include "mainwindow.h"
#include "./ui_mainwindow.h"

QVector<QGraphicsRectItem*> Marks;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->addMarkButton, SIGNAL(clicked()), this->DialogWidget, SLOT(addMarkDialog()));
    QObject::connect(ui->duplicateMarkButton, SIGNAL(clicked()), this->DialogWidget, SLOT(duplicateMarkDialog()));

    QObject::connect(DialogWidget, &Dialog::dataReady, this, &MainWindow::AddMark);
    QObject::connect(DialogWidget, &Dialog::dataDuplicateReady, this, &MainWindow::duplicateMark);

    QObject::connect(ui->removeMarkButton, &QPushButton::clicked,this, &MainWindow::removeMark);

    scene->setSceneRect(0, 0, 1890, 1890);//Размер сцены
    drawBackground(scene);
    ui->workArea->setDragMode(QGraphicsView::ScrollHandDrag);
    //ui->workArea->setDragMode(QGraphicsView::RubberBandDrag);
    ui->workArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->workArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->workArea->setScene(scene);//Устанавливаю сцену
    ui->workArea->translate(13,13);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawBackground(QGraphicsScene* scene)
{
    const int gridSize = 70;
    QPen pen(Qt::gray);
    auto size = scene->sceneRect();

    for(int y = size.top(); y < size.bottom(); y += gridSize)
    {
        scene->addLine(size.left(),y,size.right(),y,pen);
    }

    for(int x = size.left(); x < size.right(); x += gridSize)
    {
        scene->addLine(x, size.top(), x, size.bottom(),pen);
    }

    pen.setWidth(5);
    scene->addLine((size.right() / 2) + (int)(size.right()  / 2)%70 , 0, (size.right() / 2) + (int)(size.right()  / 2)%70, size.bottom(), pen);
    scene->addLine(0, (size.bottom() / 2) + (int)(size.bottom()  / 2)%70, size.right(), (size.bottom() / 2) + (int)(size.bottom()  / 2)%70, pen);
}

void MainWindow::AddMark(int x, int y, int angular)
{
    Mark* new_mark = new Mark(x, y, angular);
    scene->addItem(new_mark);
    ui->workArea->setScene(scene);
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
            AddMark(markItem->getX() + x, markItem->getY() + y, markItem->getAngular());
        }
    }
    else
    {
        QMessageBox::warning(this,"Error", "No items selected");
    }
}



