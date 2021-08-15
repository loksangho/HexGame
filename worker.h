#pragma once

#ifndef WORKER_H
#define WORKER_H

/*
 *  This is the worker class for the threaded object in the game logic implmentation.
 *
 */


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
