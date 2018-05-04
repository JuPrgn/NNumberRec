#include "barchartresult.h"
#include "ui_barchartresult.h"

BarChartResult::BarChartResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BarChartResult)
{
    ui->setupUi(this);

    mSet = new QBarSet("Results");
    *mSet << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0 << 0;
    mSet->setLabelColor(Qt::black);
    mSet->setLabelFont(QFont("Helvetica [Cronyx]", 9));//, QFont::Bold));
//    mSet->setLabelFont(QFont("Helvetica [Cronyx]", 8, QFont::Bold));

//    mSeries = new QStackedBarSeries();
    mSeries = new QHorizontalBarSeries();
    mSeries->append(mSet);
    //mSeries->setLabelsAngle(270.0);
    mSeries->setLabelsPosition(QAbstractBarSeries::LabelsInsideBase);
    mSeries->setLabelsVisible(true);

    mChart = new QChart();
    mChart->addSeries(mSeries);
    //chart->setTitle("Simple stackedbarchart example");
    mChart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    mChart->createDefaultAxes();
    mChart->setAxisY(axis, mSeries);

    mChart->axisX()->setMin(0);
    mChart->axisX()->setMax(1);
    mChart->axisX()->setVisible(false);

    mChart->legend()->setVisible(false);
    //mChart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(mChart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(300,320);

    ui->layChart->addWidget(chartView);



    // Customize series
//    QPen pen(QRgb(0xfdb157));
//    pen.setWidth(5);
//    mSeries->setPen(pen);


    for(auto item: mSeries->barSets())
    {
//        item->setColor(Qt::darkBlue);
        item->setColor(QRgb(0xffa02f));
//        item->setBrush(QBrush(QRgb(0xfdb157)));
//        QPen pen(QRgb(0xffa02f));
        QPen pen(Qt::black);
        pen.setWidth(1);
        item->setPen(pen);
        item->setLabelColor(Qt::black);
    }

    // Customize chart title
//    QFont font;
//    font.setPixelSize(18);
//    mChart->setTitleFont(font);
//    mChart->setTitleBrush(QBrush(Qt::white));
//    mChart->setTitle("Customchart example");

    // Customize chart background
    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QRgb(0xd2d0d1));
    backgroundGradient.setColorAt(1.0, QRgb(0x4c4547));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    mChart->setBackgroundBrush(backgroundGradient);


    // Customize plot area background
//    QLinearGradient plotAreaGradient;
//    plotAreaGradient.setStart(QPointF(0, 1));
//    plotAreaGradient.setFinalStop(QPointF(1, 0));
//    plotAreaGradient.setColorAt(0.0, QRgb(0x555555));
//    plotAreaGradient.setColorAt(1.0, QRgb(0x55aa55));
//    plotAreaGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
//    mChart->setPlotAreaBackgroundBrush(plotAreaGradient);
//    mChart->setPlotAreaBackgroundVisible(true);

    // Customize axis label font
//    QFont labelsFont;
//    labelsFont.setPixelSize(12);
////    axisX->setLabelsFont(labelsFont);
//    axis->setLabelsFont(labelsFont);

    // Customize axis colors
    QPen axisPen(QRgb(Qt::black));
    axisPen.setWidth(1);
    axis->setLinePen(axisPen);

    // Customize axis label colors
    axis->setLabelsBrush(QBrush(Qt::black));

    // Customize grid lines and shades
////    axisX->setGridLineVisible(false);
    axis->setGridLineVisible(false);
//    axis->setShadesPen(Qt::NoPen);
//    axis->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
//    axis->setShadesVisible(true);

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
