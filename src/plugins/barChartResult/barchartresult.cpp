#include "barchartresult.h"
#include "ui_barchartresult.h"

BarChartResult::BarChartResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BarChartResult)
{
    ui->setupUi(this);

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
    chartView->setFixedSize(250,250);

    ui->layChart->addWidget(chartView);
}

BarChartResult::~BarChartResult()
{
    delete mChart;
    delete mSet;
    delete mSeries;
    delete ui;
}

void BarChartResult::setResult(QStringList Result)
{
    for(int i=0; i<Result.size(); i++)
        mSet->replace(i, Result.at(i).toFloat());
}
