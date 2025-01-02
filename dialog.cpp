#include "dialog.h"

Dialog::Dialog() {}

void Dialog::addMarkDialog() //Создание диалога для добавления новой метки
{
    this->dialog.setWindowTitle("Add new mark");

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
    this->dialog.setLayout(dialogLayout);


    connect(addButton, &QPushButton::clicked, this, [this, &xLineEdit, &yLineEdit]()
        {
            emit dataReady(xLineEdit->text().toInt(), xLineEdit->text().toInt());
            this->dialog.accept();
        });

    this->dialog.exec();
}
