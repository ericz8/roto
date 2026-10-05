// Config.h
// Tunable constants for the robot and the competition field.

#pragma once

// ---------------------------------------------------------------------------
// Field
// ---------------------------------------------------------------------------

const float TILE_WIDTH = 50.0; // cm, one grid square on the Robot Tour field

// Distance multiplier
const float FRICTION = 1.0;

// ---------------------------------------------------------------------------
// Robot geometry
// ---------------------------------------------------------------------------
const float TRACK_WIDTH = 8.5; // cm, wheel-to-wheel distance

const float WHEEL_DIAMETER_CM = 3.2;
const float COUNTS_PER_REVOLUTION = 358.3; // encoder counts per wheel turn

// ---------------------------------------------------------------------------
// Motion limits
// ---------------------------------------------------------------------------

const float MAX_VELOCITY = 100.0; // cm/s
const float MIN_VELOCITY = 3.0;   // cm/s, floor during the accel phase
const float MAX_ACCEL = 25.0;     // cm/s^2
const float MAX_DECEL = 25.0;     // cm/s^2

// ---------------------------------------------------------------------------
// Run timing
// ---------------------------------------------------------------------------

// Total time the run should take. It is split evenly across all commands,
// then clamped to [MIN_TIME_PER_MOVE, MAX_TIME_PER_MOVE] seconds per move.
const int TARGET_TIME = 71; // s
const double MIN_TIME_PER_MOVE = 1.0; // s
const double MAX_TIME_PER_MOVE = 2.5; // s
