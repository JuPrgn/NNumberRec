/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include "scribblearea.h"

ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myPenColor = Qt::black;
}

bool ScribbleArea::openImage(const QString &fileName)
{
    QFile File(fileName);
    File.open(QIODevice::ReadOnly);
    QList<QByteArray> List;
    QByteArray ba = File.readAll();
    List = ba.split(' ');

    QSize newSize = image.size().expandedTo(size());
    resizeImage(&image, newSize);

    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            if(List.at(i*16 + j).at(0) == '0')
                image.setPixel(j,i,0xFFFFFF);
            else
                image.setPixel(j,i,0x000000);
        }
    }
    File.close();
    update();
    return true;
}

bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
{
    Q_UNUSED(fileFormat);
    QFile File(fileName);
    File.open(QIODevice::WriteOnly);
    if(!File.isOpen())
        return false;
    QString Str;
    for(int i=0; i<16; i++)
    {
        for(int j=0; j<16; j++)
        {
            if(QColor(image.pixel(j,i)) == Qt::white)
                Str.append("0.0000 ");
            else
                Str.append("1.0000 ");
        }
    }
    File.write(Str.toLocal8Bit());
    File.close();
    return true;
}

void ScribbleArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void ScribbleArea::clearImage()
{
    image.fill(Qt::white);
    modified = true;
    update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        myPenColor = Qt::black;
        lastPoint = event->pos();
        scribbling = true;
    }
    else if (event->button() == Qt::RightButton)
    {
        myPenColor = Qt::white;
        lastPoint = event->pos();
        scribbling = true;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
    else if ((event->buttons() & Qt::RightButton) && scribbling)
        drawLineTo(event->pos());
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling)
    {
        myPenColor = Qt::black;
        drawLineTo(event->pos());
        scribbling = false;
    }
    else if (event->button() == Qt::RightButton && scribbling)
    {
        myPenColor = Qt::white;
        drawLineTo(event->pos());
        scribbling = false;
    }
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

     int zoom = 10; // zoomFactor from 1 to 12.
     bool showGrid = true;

     painter.drawImage(QRect(0, 0, image.width() * zoom ,
                       image.height() * zoom), image);

     // Draw the grid
     if (zoom >= 3 && showGrid)
     {
         painter.setPen(palette().foreground().color());
         painter.setPen(Qt::DotLine);

         for (int i = 0; i <= image.width(); ++i)
             painter.drawLine(zoom * i, 0,
                 zoom * i, zoom * image.height());
         for (int j = 0; j <= image.height(); ++j)
             painter.drawLine(0, zoom * j,
                 zoom * image.width(), zoom * j);
     }
}

void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height())
    {
        int newWidth = 16;
        int newHeight = 16;
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
    QPoint p;
    p.setX(endPoint.x()/10);
    p.setY(endPoint.y()/10);
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawPoint(p);
    modified = true;
    update();
}

void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void ScribbleArea::print()
{
#if QT_CONFIG(printdialog)
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_CONFIG(printdialog)
}
