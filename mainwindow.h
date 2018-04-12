#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "numberrec.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbTraining_clicked();
    void on_pbRecognition_clicked();

private:
    Ui::MainWindow *ui;
    NumberRec *mNumberRec;
    QString mTrainingSetPath;
    QString mNNPath;
};

#endif // MAINWINDOW_H
