#include "Route.h"

// Each line starts with the turn (if any) followed by the straight moves on
// that heading. See Commands.h for the available shorthands.
Command commands[] = {
    F6,  FH,
    L90, FF,
    R90, FF, BF,
    L90, BF, BF,
    R90, FF,
    L90, FF,
    R90, FF,
    R90, FF,
    L90, FF,
    L90, FF,
    R90, FF,
    L90, FF, FF,
    B6,
};

const int NUM_COMMANDS = sizeof(commands) / sizeof(commands[0]);
