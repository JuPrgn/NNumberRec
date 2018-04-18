#ifndef NUMBERREC_H
#define NUMBERREC_H

#include <QObject>
#include "Tinn.h"

typedef struct
{
    float** in;
    float** tg;
    int nips;
    int nops;
    int rows;
}
Data;

class NumberRec : public QObject
{
    Q_OBJECT
public:
    explicit NumberRec(QObject *parent = nullptr);

    QStringList TrainFromFile(QString TrainingSetPath,
                       QString NNPath);
    QStringList Recognize(QString TrainingSetPath,
                   QString NNPath);

signals:

public slots:
};

#endif // NUMBERREC_H
