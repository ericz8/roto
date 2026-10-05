// Commands.h
// Command type and shorthand macros used to write routes.

#pragma once

#include "Config.h"

struct Command {
  // PIVOT_LEFT / PIVOT_RIGHT are UNUSED: the main loop does not handle them.
  enum Type { FORWARD, BACKWARD, LEFT, RIGHT, PIVOT_LEFT, PIVOT_RIGHT } type;
  float value;    // cm for FORWARD/BACKWARD, deg for LEFT/RIGHT
  float duration; // s, filled in by setup()
};

// ---------------------------------------------------------------------------
// Durations are left at 0 and assigned in setup().
// ---------------------------------------------------------------------------

// Straight moves
#define FF {Command::FORWARD, TILE_WIDTH, 0}          // forward one tile
#define BF {Command::BACKWARD, TILE_WIDTH, 0}         // backward one tile
#define FH {Command::FORWARD, TILE_WIDTH / 2.0, 0}    // forward half tile
#define BH {Command::BACKWARD, TILE_WIDTH / 2.0, 0}   // backward half tile
#define F6 {Command::FORWARD, 6.0, 0}                 // forward 6 cm
#define B6 {Command::BACKWARD, 6.0, 0}                // backward 6 cm

// Friction-compensated moves (scaled by FRICTION)
#define FFB {Command::FORWARD, TILE_WIDTH * FRICTION, 0}
#define BFB {Command::BACKWARD, TILE_WIDTH * FRICTION, 0}
#define FHB {Command::FORWARD, (TILE_WIDTH / 2.0) * FRICTION, 0}
#define BHB {Command::BACKWARD, (TILE_WIDTH / 2.0) * FRICTION, 0}

// Diagonal half-tile moves, meant to follow a 45 degree turn 
#define FD {Command::FORWARD, TILE_WIDTH * FRICTION * 1.414 / 2.0, 0}
#define BD {Command::BACKWARD, TILE_WIDTH * FRICTION * 1.414 / 2.0, 0}

// Turns in place
#define L90 {Command::LEFT, 90.0, 0}
#define R90 {Command::RIGHT, 90.0, 0}
#define L45 {Command::LEFT, 45.0, 0} 
#define R45 {Command::RIGHT, 45.0, 0}
