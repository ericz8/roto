// TurnSensor.h
// Configures the 3pi+ 32U4's gyro, calibrates it, and uses it to measure how
// much the robot has turned about its Z axis.
//
// Taken from the TurnSensor example in Pololu's Pololu3piPlus32U4 library.
// The code is unchanged; it is only split into a header and source file.

#pragma once

#include <stdint.h>

// This constant represents a turn of 45 degrees.
const int32_t turnAngle45 = 0x20000000;

// This constant represents a turn of 90 degrees.
const int32_t turnAngle90 = turnAngle45 * 2;

// This constant represents a turn of approximately 1 degree.
const int32_t turnAngle1 = (turnAngle45 + 22) / 45;

/* turnAngle is a 32-bit unsigned integer representing the amount
the robot has turned since the last time turnSensorReset was
called.  This is computed solely using the Z axis of the gyro, so
it could be inaccurate if the robot is rotated about the X or Y
axes.

Our convention is that a value of 0x20000000 represents a 45
degree counter-clockwise rotation.  This means that a uint32_t
can represent any angle between 0 degrees and 360 degrees.  If
you cast it to a signed 32-bit integer by writing
(int32_t)turnAngle, that integer can represent any angle between
-180 degrees and 180 degrees. */
extern uint32_t turnAngle;

// turnRate is the current angular rate of the gyro, in units of
// 0.07 degrees per second.
extern int16_t turnRate;

// This is the average reading obtained from the gyro's Z axis
// during calibration.
extern int16_t gyroOffset;

// This variable helps us keep track of how much time has passed
// between readings of the gyro.
extern uint16_t gyroLastUpdate;

// This should be called to set the starting point for measuring
// a turn.  After calling this, turnAngle will be 0.
void turnSensorReset();

// Read the gyro and update the angle.  This should be called as
// frequently as possible while using the gyro to do turns.
void turnSensorUpdate();

// This should be called in setup() to enable and calibrate the
// gyro.  It uses the display, yellow LED, and button A.  While the
// display shows "Gyro cal", you should be careful to hold the robot
// still.
void turnSensorSetup();
