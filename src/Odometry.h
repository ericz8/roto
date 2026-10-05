// Odometry.h
// Robot state estimation: heading from the gyro, distance and velocity from
// the wheel encoders.

#pragma once

#include <stdint.h>

extern float heading;  // deg, -180..180
extern float lateral;  // cm travelled since the last reset_encoders()
extern float velocity; // cm/s

extern unsigned long vel_last_time;
extern int32_t vel_last_counts;

void update_heading();
void update_velocity();

// Refreshes velocity and heading. Call once per loop.
void update();

// Zeroes the encoders and the distance travelled.
void reset_encoders();

// Converts a distance in cm to encoder counts.
float distance_to_counts(float distance);
