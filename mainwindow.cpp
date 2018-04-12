#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mTrainingSetPath = "semeion.data";
    mNNPath = "saved.tinn";

    mNumberRec = new NumberRec;
}

MainWindow::~MainWindow()
{
    delete mNumberRec;
    delete ui;
}

void MainWindow::on_pbTraining_clicked()
{
    QStringList Log;
    Log = mNumberRec->TrainFromFile(mTrainingSetPath, mNNPath);
    for(QString Str : Log)
        ui->teTrainingResult->append(Str);
}

void MainWindow::on_pbRecognition_clicked()
{
    QStringList Result;
    Result = mNumberRec->Recognize(mTrainingSetPath, mNNPath);
    for(QString Str : Result)
        ui->teResult->append(Str);
}
