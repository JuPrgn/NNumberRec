#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>

#include "numberrec.h"
#include "scribblewidget.h"
#include "barchartresult.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSettings settings("user.ini", QSettings::IniFormat);
    ui->setupUi(this);

    setWindowTitle("NNumberRec");

    mNNPath = "saved.tinn";//settings.value(DEFAULT_DIR_NN_KEY).toString();
    mTrainingSetPath = settings.value(DEFAULT_DIR_TRAIN_KEY).toString();//"semeion.data";
    mRecoPath = settings.value(DEFAULT_DIR_RECO_KEY).toString();//"Scribble.txt";
    mDrawPath = "Drawing.txt";
    ui->leTrain->setText(mTrainingSetPath);
    ui->leReco->setText(mRecoPath);

    mNumberRec = new NumberRec;

    mScribbleWidget = new ScribbleWidget;
    ui->layScribble->addWidget(mScribbleWidget);

    mBarChartResult = new BarChartResult;
    ui->layChart->addWidget(mBarChartResult);

//    createActions();
//    createMenus();

//    resize(650, 500);
}

MainWindow::~MainWindow()
{
    delete mScribbleWidget;
    delete mBarChartResult;
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

    if(ui->ckbDrawing->isChecked())
    {
        mScribbleWidget->saveImage(mDrawPath, 0);
        Result = mNumberRec->Recognize(mDrawPath, mNNPath);
    }
    else
        Result = mNumberRec->Recognize(mRecoPath, mNNPath);

    // Write results in lineEdit
    for(QString Str : Result) ui->teResult->append(Str);

    // Update chart results
    QStringList ResultReco = Result.at(0).split(" ", QString::SkipEmptyParts);
    mBarChartResult->setResult(ResultReco);
}

void MainWindow::on_tbBrowseTrain_clicked()
{
    QSettings settings("user.ini", QSettings::IniFormat);
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open File"), settings.value(DEFAULT_DIR_TRAIN_KEY).toString());
    if (!fileName.isEmpty())
    {
        QDir dir(QDir::currentPath());
        mTrainingSetPath = dir.relativeFilePath(fileName);
        ui->leTrain->setText(mTrainingSetPath);

        // Update default path
        settings.setValue(DEFAULT_DIR_TRAIN_KEY, fileName);
    }
}

void MainWindow::on_tbBrowseReco_clicked()
{
    QSettings settings("user.ini", QSettings::IniFormat);
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open File"), settings.value(DEFAULT_DIR_RECO_KEY).toString());
    if (!fileName.isEmpty())
    {
        QDir dir(QDir::currentPath());
        mRecoPath = dir.relativeFilePath(fileName);
        ui->leReco->setText(mRecoPath);

        // Update default path
        settings.setValue(DEFAULT_DIR_RECO_KEY, fileName);
    }
}

//void MainWindow::createActions()
//{
//    openAct = new QAction(tr("&Open..."), this);
//    openAct->setShortcuts(QKeySequence::Open);
//    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));


//    saveAct = new QAction(tr("&Save..."), this);
//    saveAct->setShortcuts(QKeySequence::Save);
//    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

//    penColorAct = new QAction(tr("&Pen Color..."), this);
//    connect(penColorAct, SIGNAL(triggered()), mScribbleWidget, SLOT(penColor()));

//    penWidthAct = new QAction(tr("Pen &Width..."), this);
//    connect(penWidthAct, SIGNAL(triggered()), mScribbleWidget, SLOT(penWidth()));

//    clearScreenAct = new QAction(tr("&Clear Screen"), this);
//    clearScreenAct->setShortcut(tr("Ctrl+L"));
//    connect(clearScreenAct, SIGNAL(triggered()),
//            mScribbleWidget, SLOT(clearImage()));
//}

//void MainWindow::createMenus()
//{
//    fileMenu = new QMenu(tr("&File"), this);
//    fileMenu->addAction(openAct);
//    fileMenu->addAction(saveAct);

//    optionMenu = new QMenu(tr("&Options"), this);
//    optionMenu->addAction(penColorAct);
//    optionMenu->addAction(penWidthAct);
//    optionMenu->addSeparator();
//    optionMenu->addAction(clearScreenAct);

//    ui->menuBar->insertMenu(openAct, fileMenu);
//    ui->menuBar->insertMenu(openAct, optionMenu);
//}

//void MainWindow::save()
//{
//    QAction *action = qobject_cast<QAction *>(sender());
//    QByteArray fileFormat = action->data().toByteArray();
//    mScribbleWidget->saveFile(fileFormat);
//}

//void MainWindow::open()
//{
//    mScribbleWidget->openFile();
//}

//void MainWindow::clear()
//{
//    mScribbleWidget->clearImage();
//}
