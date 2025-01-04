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

    QLabel* angularLabel = new QLabel("Angular");
    QComboBox* angularComboBox = new QComboBox;
    angularComboBox->addItem("0");
    angularComboBox->addItem("90");
    angularComboBox->addItem("180");
    angularComboBox->addItem("270");
     angularLabel->setBuddy(angularComboBox);

    QVBoxLayout* dialogLayout = new QVBoxLayout;

    dialogLayout->addWidget(xLabel);
    dialogLayout->addWidget(xLineEdit);
    dialogLayout->addWidget(yLabel);
    dialogLayout->addWidget(yLineEdit);
    dialogLayout->addWidget(angularLabel);
    dialogLayout->addWidget(angularComboBox);
    dialogLayout->addWidget(addButton);
    this->dialog.setLayout(dialogLayout);

    connect(addButton, &QPushButton::clicked, this, [this, &xLineEdit, &yLineEdit, &angularComboBox]()
    {
        if((xLineEdit->text() != "0" and xLineEdit->text().toInt() == 0) or (yLineEdit->text() != "0" and yLineEdit->text().toInt() == 0))
        {
            QMessageBox::warning(this,"Error", "Invalid input");
        }
        else
        {
            int x = (xLineEdit->text().toInt() + 13) * 70;
            int y = (yLineEdit->text().toInt() + 13) * 70;
            emit dataReady(x, y, angularComboBox->currentText().toInt());
        }

        this->dialog.accept();
    });

    this->dialog.exec();
    delete dialogLayout;
}
