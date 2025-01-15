#include "dialog.h"

Dialog::Dialog()
{
    QString StyleSheet(R"(
    QDialog {
        background-color: #1A1A2E;
        border: 2px solid #a0a0a0;
        border-radius: 10px;
    }
    QLabel {
        color: #FF6F61;
        font-size: 14px;
        padding: 5px;
    }
    QLineEdit {
        background-color: #1A1A2E;
        color: #FF6F61;
        border: 1px solid #FF6F61;
        border-radius: 5px;
        padding: 5px;
    }
    QLineEdit:focus {
        border: 1px solid #FF6F61;
    }
    QComboBox {
        background-color: #1A1A2E;
        color: #FF6F61;
        border: 1px solid #FF6F61;
        border-radius: 5px;
        padding: 5px;
    }
    QComboBox:focus {
        border: 1px solid #FF6F61;
    }
    QComboBox::drop-down {
        background-color: #1A1A2E;
        border: 1px solid #FF6F61;
        border-radius: 5px;
    }
    QComboBox QAbstractItemView {
        background-color: #1A1A2E;
        color: #FF6F61;
        border: 1px solid #FF6F61;
        border-radius: 5px;
    }
    QComboBox QAbstractItemView::item:selected {
        background-color: #FF6F61;
        color: #1A1A2E;
    }
    QComboBox::down-arrow {
        image: url(down_arrow.png);
    }
    QPushButton {
        background-color: #FF6F61;
        color: #1A1A2E;
        border: none;
        border-radius: 5px;
        padding: 10px;
        font-weight: bold;
    }
    QPushButton:hover {
        background-color: #FF6F61;
    }
    QPushButton:pressed {
        background-color: #003f6b;
    }
    QPushButton:focus {
        outline: none;
        border: 2px solid #FF6F61;
    }
    )");

    addMarkDialog.setWindowTitle("Add");

    QLabel* xLabel = new QLabel("X", &addMarkDialog);
    QLineEdit* xLineEdit = new QLineEdit(&addMarkDialog);
    xLineEdit->setObjectName("xLineEdit");
    xLabel->setBuddy(xLineEdit);

    QLabel* yLabel = new QLabel("Y", &addMarkDialog);
    QLineEdit* yLineEdit = new QLineEdit(&addMarkDialog);
    yLineEdit->setObjectName("yLineEdit");
    yLabel->setBuddy(yLineEdit);

    QPushButton* addButton = new QPushButton("Add mark", &addMarkDialog);

    QLabel* angularLabel = new QLabel("Angular", &addMarkDialog);
    QComboBox* angularComboBox = new QComboBox(&addMarkDialog);
    angularComboBox->addItem("0");
    angularComboBox->addItem("90");
    angularComboBox->addItem("180");
    angularComboBox->addItem("270");
    angularComboBox->setObjectName("angularComboBox");
    angularLabel->setBuddy(angularComboBox);

    QVBoxLayout* addMarkDialogLayout = new QVBoxLayout(&addMarkDialog);

    addMarkDialogLayout->addWidget(xLabel);
    addMarkDialogLayout->addWidget(xLineEdit);
    addMarkDialogLayout->addWidget(yLabel);
    addMarkDialogLayout->addWidget(yLineEdit);
    addMarkDialogLayout->addWidget(angularLabel);
    addMarkDialogLayout->addWidget(angularComboBox);
    addMarkDialogLayout->addWidget(addButton);
    this->addMarkDialog.setLayout(addMarkDialogLayout );
    addMarkDialog.setStyleSheet(StyleSheet);

    connect(addButton, SIGNAL(clicked()), &addMarkDialog, SLOT(accept()));

    // Duplicate Mark Dialog
    duplicateMarkDialog.setWindowTitle("Duplicate");

    QLabel* xLabelDup = new QLabel("X", &duplicateMarkDialog);
    QLineEdit* xLineEditDup = new QLineEdit(&duplicateMarkDialog);
    xLineEditDup->setObjectName("xLineEdit");
    xLabel->setBuddy(xLineEditDup);

    QLabel* yLabelDup = new QLabel("Y", &duplicateMarkDialog);
    QLineEdit* yLineEditDup = new QLineEdit(&duplicateMarkDialog);
    yLineEditDup->setObjectName("yLineEdit");
    yLabel->setBuddy(yLineEditDup);

    QPushButton* addButtonDup = new QPushButton("Duplicate marks",&duplicateMarkDialog);

    QVBoxLayout* duplicateMarkLayout = new QVBoxLayout(&duplicateMarkDialog);

    duplicateMarkLayout->addWidget(xLabelDup);
    duplicateMarkLayout->addWidget(xLineEditDup);
    duplicateMarkLayout->addWidget(yLabelDup);
    duplicateMarkLayout->addWidget(yLineEditDup);
    duplicateMarkLayout->addWidget(addButtonDup);
    this->duplicateMarkDialog.setLayout(duplicateMarkLayout);
    duplicateMarkDialog.setStyleSheet(StyleSheet);

    connect(addButtonDup, SIGNAL(clicked()), &duplicateMarkDialog, SLOT(accept()));

    //Move To Dialog
    moveToMarkDialog.setWindowTitle("Move");

    moveToMarkDialog.setWindowTitle("Move");

    QLabel* xLabelMove = new QLabel("X", &moveToMarkDialog);
    QLineEdit* xLineEditMove = new QLineEdit(&moveToMarkDialog);
    xLineEditMove->setObjectName("xLineEdit");
    xLabelMove->setBuddy(xLineEditMove);

    QLabel* yLabelMove = new QLabel("Y", &moveToMarkDialog);
    QLineEdit* yLineEditMove = new QLineEdit(&moveToMarkDialog);
    yLineEditMove->setObjectName("yLineEdit");
    yLabelMove->setBuddy(yLineEditMove);

    QPushButton* addButtonMove = new QPushButton("Move mark", &moveToMarkDialog);

    QVBoxLayout* moveToMarkLayout = new QVBoxLayout;

    moveToMarkLayout->addWidget(xLabelMove);
    moveToMarkLayout->addWidget(xLineEditMove);
    moveToMarkLayout->addWidget(yLabelMove);
    moveToMarkLayout->addWidget(yLineEditMove);
    moveToMarkLayout->addWidget(addButtonMove);
    this->moveToMarkDialog.setLayout(moveToMarkLayout);
    moveToMarkDialog.setStyleSheet(StyleSheet);

    connect(addButtonMove, SIGNAL(clicked()), &moveToMarkDialog, SLOT(accept()));
}

void Dialog::showAddMarkDialog()
{
    if(addMarkDialog.exec() == QDialog::Accepted)
    {
        QLineEdit* xLineEdit = addMarkDialog.findChild<QLineEdit*>("xLineEdit");
        QLineEdit* yLineEdit = addMarkDialog.findChild<QLineEdit*>("yLineEdit");
        QComboBox* angularComboBox = addMarkDialog.findChild<QComboBox*>("angularComboBox");

        if((xLineEdit->text() != "0" and xLineEdit->text().toInt() == 0) or (yLineEdit->text() != "0" and yLineEdit->text().toInt() == 0))
        {
            QMessageBox::warning(this,"Error", "Invalid input");

            xLineEdit->clear();
            yLineEdit->clear();
            angularComboBox->setCurrentIndex(0);
        }
        else
        {
            int x = xLineEdit->text().toInt() * gridSize - gridSize / 3;
            int y = yLineEdit->text().toInt() * - gridSize;
            xLineEdit->clear();
            yLineEdit->clear();
            angularComboBox->setCurrentIndex(0);
            emit dataReady(x, y, angularComboBox->currentText().toInt());
        }
    }
}

void Dialog::showDuplicateMarkDialog()
{
    if(duplicateMarkDialog.exec() == QDialog::Accepted)
    {
        QLineEdit* xLineEdit = duplicateMarkDialog.findChild<QLineEdit*>("xLineEdit");
        QLineEdit* yLineEdit = duplicateMarkDialog.findChild<QLineEdit*>("yLineEdit");

        if((xLineEdit->text() != "0" and xLineEdit->text().toInt() == 0) or (yLineEdit->text() != "0" and yLineEdit->text().toInt() == 0))
        {
            QMessageBox::warning(this,"Error", "Invalid input");

            xLineEdit->clear();
            yLineEdit->clear();
        }
        else
        {
            int x = (xLineEdit->text().toInt()) * gridSize;
            int y = (yLineEdit->text().toInt()) * -gridSize;
            xLineEdit->clear();
            yLineEdit->clear();
            emit dataDuplicateReady(x, y);

        }
    }
}

void Dialog::showMoveToMarkDialog()
{
    QLineEdit* xLineEdit = moveToMarkDialog.findChild<QLineEdit*>("xLineEdit");
    QLineEdit* yLineEdit = moveToMarkDialog.findChild<QLineEdit*>("yLineEdit");

    if(moveToMarkDialog.exec() == QDialog::Accepted)
    {
        if((xLineEdit->text() != "0" and xLineEdit->text().toInt() == 0) or (yLineEdit->text() != "0" and yLineEdit->text().toInt() == 0))
        {
            QMessageBox::warning(this,"Error", "Invalid input");

            xLineEdit->clear();
            yLineEdit->clear();
        }
        else
        {
            int x = xLineEdit->text().toInt() * gridSize - gridSize / 3;
            int y = yLineEdit->text().toInt() * -gridSize;
            xLineEdit->clear();
            yLineEdit->clear();
            emit dataMoveToReady(x, y);
        }
    }
}

