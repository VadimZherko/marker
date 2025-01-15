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

signals:
    void dataReady(int x, int y, int angular);
    void dataDuplicateReady(int x, int y);
    void dataMoveToReady(int x, int y);

public slots:
    void showAddMarkDialog();
    void showDuplicateMarkDialog();
    void showMoveToMarkDialog();
};

#endif // DIALOG_H
