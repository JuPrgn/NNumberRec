#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QBoxLayout;
class NumberRec;
class ScribbleWidget;
class BarChartResult;

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
    void on_tbBrowseTrain_clicked();
    void on_tbBrowseReco_clicked();

    //    void clear();
    //    void open();
    //    void save();

private:
    Ui::MainWindow *ui;
    NumberRec *mNumberRec;
    QString mTrainingSetPath;
    QString mRecoPath;
    QString mDrawPath;
    QString mNNPath;

    ScribbleWidget *mScribbleWidget;
    BarChartResult * mBarChartResult;

//    void createActions();
//    void createMenus();
//    bool maybeSave();
//    bool saveFile(const QByteArray &fileFormat);

//    QMenu *saveAsMenu;
//    QMenu *fileMenu;
//    QMenu *optionMenu;

//    QAction *openAct;
//    QAction *saveAct;
//    QAction *penColorAct;
//    QAction *penWidthAct;
//    QAction *clearScreenAct;
};

#endif // MAINWINDOW_H
