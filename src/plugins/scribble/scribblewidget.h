#ifndef SCRIBBLEWIDGET_H
#define SCRIBBLEWIDGET_H

#include <QWidget>

const QString DEFAULT_DIR_SCRIBBLE_KEY("Scribble/default_dir_scribble");

class ScribbleArea;

namespace Ui {
class ScribbleWidget;
}

class ScribbleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScribbleWidget(QWidget *parent = 0);
    ~ScribbleWidget();

private:
    Ui::ScribbleWidget *ui;
    ScribbleArea *mScribbleArea;

private slots:
    void on_tbClear_clicked();
    void on_tbSave_clicked();
    void on_tbOpen_clicked();

public slots:
    void penColor();
    void penWidth();
    bool saveFile(const QByteArray &fileFormat);
    bool openFile(void);
    bool saveImage(const QString &fileName, const char *fileFormat);
    bool openImage(const QString &fileName);
    void clearImage(void);
};

#endif // SCRIBBLEWIDGET_H
