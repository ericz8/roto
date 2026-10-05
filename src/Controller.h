// Controller.h
// Closed-loop drive control: a velocity PID (plus feedforward) for distance
// and a heading PID for steering, mixed into left/right motor speeds.

#pragma once

#include "PID.h"

extern float target_heading;  // deg
extern float target_lateral;  // cm
extern float target_velocity; // cm/s

extern PID heading_pid;
extern PID velocity_pid;

// Forward motor command from the velocity profile and velocity PID.
int velocity_control();

// Turning motor command from the heading PID.
int heading_control();

// Runs both controllers and writes the result to the motors.
void apply_controls();

void stop_motors();
