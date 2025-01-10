#include "dialog.h"

Dialog::Dialog() {}

void Dialog::addMarkDialog()
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
            int x = (xLineEdit->text().toInt() + (int)(sceneSize/gridSize/2)) * gridSize + gridSize / 2;
            int y = (yLineEdit->text().toInt() + (int)(sceneSize/gridSize/2)) * gridSize + gridSize / 2;
            emit dataReady(x, y, angularComboBox->currentText().toInt());
        }

        this->dialog.accept();
    });

    this->dialog.exec();
    delete dialogLayout;
    delete angularLabel;
    delete xLabel;
    delete xLineEdit;
    delete yLabel;
    delete yLineEdit;
    delete angularComboBox;
    delete addButton;
}

void Dialog::duplicateMarkDialog()
{
    this->dialog.setWindowTitle("Duplicate");

    QLabel* xLabel = new QLabel("X ");
    QLineEdit* xLineEdit = new QLineEdit();
    xLabel->setBuddy(xLineEdit);

    QLabel* yLabel = new QLabel("Y ");
    QLineEdit* yLineEdit = new QLineEdit();
    yLabel->setBuddy(yLineEdit);

    QPushButton* addButton = new QPushButton("Duplicate marks");

    QVBoxLayout* dialogLayout = new QVBoxLayout;

    dialogLayout->addWidget(xLabel);
    dialogLayout->addWidget(xLineEdit);
    dialogLayout->addWidget(yLabel);
    dialogLayout->addWidget(yLineEdit);
    dialogLayout->addWidget(addButton);
    this->dialog.setLayout(dialogLayout);

    connect(addButton, &QPushButton::clicked, this, [this, &xLineEdit, &yLineEdit]()
            {
                if((xLineEdit->text() != "0" and xLineEdit->text().toInt() == 0) or (yLineEdit->text() != "0" and yLineEdit->text().toInt() == 0))
                {
                    QMessageBox::warning(this,"Error", "Invalid input");
                }
                else
                {
                    int x = (xLineEdit->text().toInt()) * gridSize;
                    int y = (yLineEdit->text().toInt()) * gridSize;
                    emit dataDuplicateReady(x, y);
                }

                this->dialog.accept();
            });

    this->dialog.exec();
    delete dialogLayout;
    delete xLabel;
    delete xLineEdit;
    delete yLabel;
    delete yLineEdit;
    delete addButton;
}

void Dialog::moveToMarkDialog()
{
    this->dialog.setWindowTitle("Move");

    QLabel* xLabel = new QLabel("X ");
    QLineEdit* xLineEdit = new QLineEdit();
    xLabel->setBuddy(xLineEdit);

    QLabel* yLabel = new QLabel("Y ");
    QLineEdit* yLineEdit = new QLineEdit();
    yLabel->setBuddy(yLineEdit);

    QPushButton* addButton = new QPushButton("Move mark");

    QVBoxLayout* dialogLayout = new QVBoxLayout;

    dialogLayout->addWidget(xLabel);
    dialogLayout->addWidget(xLineEdit);
    dialogLayout->addWidget(yLabel);
    dialogLayout->addWidget(yLineEdit);
    dialogLayout->addWidget(addButton);
    this->dialog.setLayout(dialogLayout);

    connect(addButton, &QPushButton::clicked, this, [this, &xLineEdit, &yLineEdit]()
            {
                if((xLineEdit->text() != "0" and xLineEdit->text().toInt() == 0) or (yLineEdit->text() != "0" and yLineEdit->text().toInt() == 0))
                {
                    QMessageBox::warning(this,"Error", "Invalid input");
                }
                else
                {
                    int x = (xLineEdit->text().toInt() + (int)(sceneSize/gridSize/2)) * gridSize + gridSize / 2;
                    int y = (yLineEdit->text().toInt() + (int)(sceneSize/gridSize/2)) * gridSize + gridSize / 2;
                    emit dataMoveToReady(x, y);
                }

                this->dialog.accept();
            });

    this->dialog.exec();
    delete dialogLayout;
    delete xLabel;
    delete xLineEdit;
    delete yLabel;
    delete yLineEdit;
    delete addButton;
}
