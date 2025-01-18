#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog();

private:
    const int gridSize = 40;

    QDialog addMarkDialog;
    QDialog duplicateMarkDialog;
    QDialog moveToMarkDialog;

    bool checkInput(QString, QString);

signals:
    void dataReady(double x, double y, int angular);
    void dataDuplicateReady(double x, double y);
    void dataMoveToReady(double x, double y);

public slots:
    void showAddMarkDialog();
    void showDuplicateMarkDialog();
    void showMoveToMarkDialog();
};

#endif // DIALOG_H
