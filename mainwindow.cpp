#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QInputDialog>
#include <QLabel>

QVector<QGraphicsRectItem*> Marks;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(); //Создание сцены
    scene->setSceneRect(0, 0, 1920, 1080); //Размер сцены
    ui->workArea->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->workArea->setScene(scene);//Устанавливаю сцену

    QObject::connect(ui->addMarkButton,SIGNAL(clicked()),this,SLOT(addMarkDialog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMarkDialog() //Создание диалога для добавления новой метки
{
    QDialog Dialog;

    Dialog.setWindowTitle("Add new mark");

    QLabel* xLabel = new QLabel("X ");
    QLineEdit* xLineEdit = new QLineEdit();
    xLabel->setBuddy(xLineEdit);

    QLabel* yLabel = new QLabel("Y ");
    QLineEdit* yLineEdit = new QLineEdit();
    yLabel->setBuddy(yLineEdit);

    QPushButton* addButton = new QPushButton("Add mark");


    QVBoxLayout* dialogLayout = new QVBoxLayout;

    dialogLayout->addWidget(xLabel);
    dialogLayout->addWidget(xLineEdit);
    dialogLayout->addWidget(yLabel);
    dialogLayout->addWidget(yLineEdit);
    dialogLayout->addWidget(addButton);
    Dialog.setLayout(dialogLayout);

    auto scene = ui->workArea->scene();
    connect(addButton, &QPushButton::clicked, [&Dialog, &scene, &xLineEdit, &yLineEdit]()
    {
        QGraphicsRectItem* a = new QGraphicsRectItem(xLineEdit->text().toInt(), xLineEdit->text().toInt(), 20, 20);
        a->setBrush(Qt::black);
        a->setFlag(QGraphicsItem::ItemIsMovable);
        a->setFlag(QGraphicsItem::ItemIsSelectable);
        Marks.push_back(a);
        scene->addItem(Marks.back());
        Dialog.accept();
    });

    ui->workArea->setScene(scene);
    Dialog.exec();
}

