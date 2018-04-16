#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include "numberrec.h"

#include <QStringList>
//#include <QtCharts/QChartView>
//#include <QtCharts/QPieSeries>
//#include <QtCharts/QPieSlice>

#include <QtCharts/QChartView>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

class ScribbleArea;

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

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();

    void on_tbClear_clicked();

    void on_tbSave_clicked();

    void on_tbOpen_clicked();

    void on_tbBrowseTrain_clicked();

    void on_tbBrowseReco_clicked();

private:
    Ui::MainWindow *ui;
    NumberRec *mNumberRec;
    QString mTrainingSetPath;
    QString mRecoPath;
    QString mDrawPath;
    QString mNNPath;

    QChart *mChart;
    QList<QBarSet*> mListBarSet;
    QBarSet *mSet;
    QStackedBarSeries *mSeries;
//    QPieSeries *mSeries;

    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    ScribbleArea *scribbleArea;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;

    QAction *openAct;
    QAction *saveAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *clearScreenAct;
};

#endif // MAINWINDOW_H
