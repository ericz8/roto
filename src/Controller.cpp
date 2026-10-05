#include "Controller.h"

#include <Arduino.h>

#include "Config.h"
#include "Hardware.h"
#include "MotionProfile.h"
#include "Odometry.h"

float target_heading = 0.0;  // deg
float target_lateral = 0.0;  // cm
float target_velocity = 0.0; // cm/s

PID heading_pid(5.5, 0.0, 0.025);
PID velocity_pid(5.0, 0.0, 0.0);

// Motor units per cm/s of target velocity.
static const float VELOCITY_FEEDFORWARD = 20.0;

int velocity_control() {
  target_velocity = compute_trapezoidal_velocity(lateral, target_lateral);

  target_velocity = constrain(target_velocity, -MAX_VELOCITY, MAX_VELOCITY);

  float control_signal = velocity_pid.compute(target_velocity, velocity);
  float feedforward = target_velocity * VELOCITY_FEEDFORWARD;

  return constrain((int)(control_signal + feedforward), -250, 250);
}

int heading_control() {
  // Unwrap angle measurement
  float measured = heading;
  while (target_heading - measured > 180.0f)
    measured += 360.0f;
  while (target_heading - measured < -180.0f)
    measured -= 360.0f;

  float control_signal = heading_pid.compute(target_heading, measured);
  return constrain((int)control_signal, -100, 100);
}

void apply_controls() {
  int heading_signal = heading_control();
  int velocity_signal = velocity_control();

  int left_speed = velocity_signal - heading_signal;
  int right_speed = velocity_signal + heading_signal;

  motors.setSpeeds(left_speed, right_speed);
}

void stop_motors() { motors.setSpeeds(0, 0); }
