#include "worker.h"

//const int MC_TRIALS = 50;

void Worker::doWork(const QString &parameter, HexBoard* board, Colour player_colour, int mc_trials) {
    QString result;
    /* ... here is the expensive or blocking operation ... */
    int move_int = board->best_move_AI(player_colour==Colour::BLUE?Colour::RED:Colour::BLUE, mc_trials);

    result = QString::number(move_int);
    emit resultReady(result);
}
