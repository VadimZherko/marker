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

signals:
    void dataReady(int x, int y, int angular);

public slots:
    void addMarkDialog();

};

#endif // DIALOG_H
