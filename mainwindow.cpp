#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->addMarkButton, SIGNAL(clicked()), this->DialogWidget, SLOT(addMarkDialog()));
    QObject::connect(ui->duplicateMarkButton, SIGNAL(clicked()), this->DialogWidget, SLOT(duplicateMarkDialog()));
    QObject::connect(ui->moveToMarkButton, SIGNAL(clicked()), this->DialogWidget, SLOT(moveToMarkDialog()));
    QObject::connect(ui->rotateMarkButton, SIGNAL(clicked()), this, SLOT(rotateMark()));

    QObject::connect(DialogWidget, &Dialog::dataReady, this, &MainWindow::AddMark);
    QObject::connect(DialogWidget, &Dialog::dataDuplicateReady, this, &MainWindow::duplicateMark);
    QObject::connect(DialogWidget, &Dialog::dataMoveToReady, this, &MainWindow::moveToMark);

    QObject::connect(ui->removeMarkButton, &QPushButton::clicked,this, &MainWindow::removeMark);

    scene->setSceneRect(0, 0, 2000, 2000);
    drawBackground(scene);
    ui->workArea->setDragMode(QGraphicsView::ScrollHandDrag);
    //ui->workArea->setDragMode(QGraphicsView::RubberBandDrag);
    ui->workArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->workArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->workArea->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawBackground(QGraphicsScene* scene)
{
    QPen pen(Qt::gray);
    auto size = scene->sceneRect();
    auto width = scene->sceneRect().width();
    auto height = scene->sceneRect().height();

    for(int y = 0; y < height; y += gridSize)
    {
        scene->addLine(0, y, width, y, pen);
    }

    for(int x = 0; x < width; x += gridSize)
    {
        scene->addLine(x, 0, x, height, pen);
    }

    pen.setWidth(5);
    scene->addLine((width / 2) + (int)(width  / 2) % gridSize , 0, (width / 2) + (int)(width  / 2) % gridSize, height, pen);
    scene->addLine(0, (height / 2) + (int)(height  / 2) % gridSize, width, (size.bottom() / 2) + (int)(height / 2) % gridSize, pen);

    for(int x = 0,  i = (width  / gridSize) / 2 * -1 - 1; x < width; x += gridSize, i ++)
    {
        scene->addLine(x, (height / 2) + (int)(height  / 2) % gridSize - 10, x, (height / 2) + (int)(height  / 2) % gridSize +10, pen);

        QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(i)) ;
        text->setPos(x, (height / 2) + (int)(height  / 2) % gridSize + 20);
        scene->addItem(text);
    }

    for(int y = 0, i = (height  / gridSize) / 2 * -1 - 1 ; y < height; y += gridSize, i++)
    {
        scene->addLine((width / 2) + (int)(width  / 2) % gridSize - 10, y, (width / 2) + (int)(width  / 2) % gridSize + 10, y, pen);

        QGraphicsSimpleTextItem* text = new QGraphicsSimpleTextItem(QString::number(i)) ;
        text->setPos((width / 2) + (int)(width  / 2) % gridSize + 20, y);
        scene->addItem(text);
    }
}

bool MainWindow::AddMark(int x, int y, int angular)
{
    const QTransform imp;
    if(scene->itemAt(x,y,imp) == nullptr)
    {
        Mark* new_mark = new Mark(x, y, angular);
        scene->addItem(new_mark);
        ui->workArea->setScene(scene);
        return true;
    }
    else
    {
        QMessageBox::warning(this,"Error", "There is already a mark at this place");
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

void MainWindow::moveToMark(int x, int y)
{
    auto selectedItems = scene->selectedItems();
    if (!selectedItems.empty())
    {
        Mark* markItem = qgraphicsitem_cast<Mark*>(selectedItems[0]);
        if(AddMark(x, y, markItem->getAngular())) delete markItem;
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



