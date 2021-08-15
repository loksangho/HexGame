#pragma once

#ifndef WORKFLOWMANAGER_H
#define WORKFLOWMANAGER_H


/*
 *  This is a helper class for the game logic. Not really used.
 *
 */

#include "node.h"
#include "graph.h"
#include "hexboard.h"

// Workflow Manager
class WorkflowManager {
    public:
        WorkflowManager(int length);
        void play_game();
        Colour switch_turn(Colour c);
    private:
        HexBoard* board;

};
#endif // WORKFLOWMANAGER_H
