#ifndef BARCHARTRESULT_H
#define BARCHARTRESULT_H

#include <QWidget>

#include <QtCharts/QChartView>
//#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class BarChartResult;
}

class BarChartResult : public QWidget
{
    Q_OBJECT

public:
    explicit BarChartResult(QWidget *parent = 0);
    ~BarChartResult();

public slots:
    void setResult(QStringList Result);

private:
    Ui::BarChartResult *ui;
    QChart *mChart;
    QList<QBarSet*> mListBarSet;
    QBarSet *mSet;
//    QStackedBarSeries *mSeries;
    QHorizontalBarSeries *mSeries;
};

#endif // BARCHARTRESULT_H
