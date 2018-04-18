#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scribblearea.h"

#include <QDebug>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("NNumberRec");

    mNNPath = "saved.tinn";
    mTrainingSetPath = "semeion.data";
    mRecoPath = "Scribble.txt";
    mDrawPath = "Drawing.txt";
    ui->leTrain->setText(mTrainingSetPath);
    ui->leReco->setText(mRecoPath);

    mNumberRec = new NumberRec;

    mSet = new QBarSet("Results");
    *mSet << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;

    mSeries = new QStackedBarSeries();
    mSeries->append(mSet);

    mChart = new QChart();
    mChart->addSeries(mSeries);
    //chart->setTitle("Simple stackedbarchart example");
    mChart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    mChart->createDefaultAxes();
    mChart->setAxisX(axis, mSeries);

    mChart->axisY()->setMin(0);
    mChart->axisY()->setMax(1);

    mChart->legend()->setVisible(false);
    //mChart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(mChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(300,300);

    ui->layChart->addWidget(chartView);

    scribbleArea = new ScribbleArea;
    ui->hlScribble->addWidget(scribbleArea);
    scribbleArea->setFixedSize(160,160);

    createActions();
    createMenus();

    //resize(650, 500);
}

MainWindow::~MainWindow()
{
    delete mChart;
    delete mSet;
    delete mSeries;
    delete scribbleArea;
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
        scribbleArea->saveImage(mDrawPath, 0);
        Result = mNumberRec->Recognize(mDrawPath, mNNPath);
    }
    else
        Result = mNumberRec->Recognize(mRecoPath, mNNPath);

    for(QString Str : Result)
        ui->teResult->append(Str);

    QStringList ResultReco = Result.at(0).split(" ", QString::SkipEmptyParts);

    for(int i=0; i<ResultReco.size(); i++)
        mSet->replace(i, ResultReco.at(i).toFloat());
}

//! [3]
void MainWindow::open()
//! [3] //! [4]
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
        scribbleArea->openImage(fileName);
}
//! [4]

//! [5]
void MainWindow::save()
//! [5] //! [6]
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}
//! [6]

//! [7]
void MainWindow::penColor()
//! [7] //! [8]
{
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}
//! [8]

//! [9]
void MainWindow::penWidth()
//! [9] //! [10]
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        scribbleArea->penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        scribbleArea->setPenWidth(newWidth);
}
//! [10]

//! [13]
void MainWindow::createActions()
//! [13] //! [14]
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));


    saveAct = new QAction(tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            scribbleArea, SLOT(clearImage()));
}
//! [14]

//! [15]
void MainWindow::createMenus()
//! [15] //! [16]
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    ui->menuBar->insertMenu(openAct, fileMenu);
    ui->menuBar->insertMenu(openAct, optionMenu);
}
//! [16]

//! [19]
bool MainWindow::saveFile(const QByteArray &fileFormat)
//! [19] //! [20]
{
    QString initialPath = QDir::currentPath() + "/Scribble" + ".txt";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"),
                               initialPath,
                               tr("All Files (*)"));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return scribbleArea->saveImage(fileName, fileFormat.constData());
    }
}
//! [20]


void MainWindow::on_tbClear_clicked()
{
    clearScreenAct->triggered();
}

void MainWindow::on_tbSave_clicked()
{
    saveAct->triggered();
}

void MainWindow::on_tbOpen_clicked()
{
    openAct->triggered();
}

void MainWindow::on_tbBrowseTrain_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
    {
        mTrainingSetPath = fileName;
        ui->leTrain->setText(mTrainingSetPath);
    }
}

void MainWindow::on_tbBrowseReco_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty())
    {
        mRecoPath = fileName;
        ui->leReco->setText(mRecoPath);
    }
}