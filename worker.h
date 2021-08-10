#pragma once

#ifndef WORKER_H
#define WORKER_H

#include <QThread>
#include "hexboard.h"

class Worker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(const QString &parameter, HexBoard* board, Colour player_colour, int mc_trials);

signals:
    void resultReady(const QString &result);
};


#endif // WORKER_H
