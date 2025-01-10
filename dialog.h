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
    QDialog dialog;
    const int gridSize = 80;
    const int sceneSize = 2000;

signals:
    void dataReady(int x, int y, int angular);
    void dataDuplicateReady(int x, int y);
    void dataMoveToReady(int x, int y);

public slots:
    void addMarkDialog();
    void duplicateMarkDialog();
    void moveToMarkDialog();
};

#endif // DIALOG_H
