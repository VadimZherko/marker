#include "mainwindow.h"
#include "./ui_mainwindow.h"

QVector<QGraphicsRectItem*> Marks;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->addMarkButton, SIGNAL(clicked()), this->DialogWidget, SLOT(addMarkDialog()));
    QObject::connect(DialogWidget, &Dialog::dataReady, this, &MainWindow::AddMark);

    scene->setSceneRect(0, 0, 100000, 100000);//Размер сцены
    drawBackground(scene);
    ui->workArea->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->workArea->setScene(scene);//Устанавливаю сцену
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawBackground(QGraphicsScene* scene)
{
    const int gridSize = 20;
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
}

void MainWindow::drawMark(Mark* mark)
{
    scene->addItem(mark);
    ui->workArea->setScene(scene);
}

void MainWindow::AddMark(int x, int y)
{
    Mark* new_mark = new Mark(x,y);
    Marks.push_back(new_mark);

    drawMark(Marks.back());
}


