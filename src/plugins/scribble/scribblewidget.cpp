#include "scribblewidget.h"
#include "ui_scribblewidget.h"

#include "scribblearea.h"

#include <QtWidgets>

ScribbleWidget::ScribbleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScribbleWidget)
{
    ui->setupUi(this);

    mScribbleArea = new ScribbleArea;
    ui->hlScribble->addWidget(mScribbleArea);
    mScribbleArea->setFixedSize(160,160);
}

ScribbleWidget::~ScribbleWidget()
{
    delete mScribbleArea;
    delete ui;
}

bool ScribbleWidget::openImage(const QString &fileName)
{
    return mScribbleArea->openImage(fileName);
}

bool ScribbleWidget::saveImage(const QString &fileName, const char *fileFormat)
{
    return mScribbleArea->saveImage(fileName, fileFormat);
}

void ScribbleWidget::clearImage(void)
{
    mScribbleArea->clearImage();
}

void ScribbleWidget::penColor()
{
    QColor newColor = QColorDialog::getColor(mScribbleArea->penColor());
    if (newColor.isValid())
        mScribbleArea->setPenColor(newColor);
}

void ScribbleWidget::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        mScribbleArea->penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        mScribbleArea->setPenWidth(newWidth);
}

bool ScribbleWidget::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/Scribble" + ".txt";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"),
                               initialPath, tr("All Files (*)"));
    if(fileName.isEmpty())
        return false;
    else
        return mScribbleArea->saveImage(fileName, fileFormat.constData());
}

bool ScribbleWidget::openFile(void)
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open File"), QDir::currentPath());
    if(!fileName.isEmpty())
        return openImage(fileName);
    return false;
}

void ScribbleWidget::on_tbClear_clicked()
{
    clearImage();
}

void ScribbleWidget::on_tbSave_clicked()
{
    saveFile(0);
}

void ScribbleWidget::on_tbOpen_clicked()
{
    openFile();
}
