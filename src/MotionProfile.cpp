#include "MotionProfile.h"

#include <Arduino.h>

#include "Config.h"

float compute_trapezoidal_velocity(float position, float total_distance) {
  float direction = (total_distance >= 0) ? 1.0 : -1.0;
  float abs_distance = abs(total_distance);
  float abs_position = abs(position);

  if (abs_distance < 0.1)
    return 0.0;

  float accel_distance = (MAX_VELOCITY * MAX_VELOCITY) / (2.0 * MAX_ACCEL);
  float decel_distance = (MAX_VELOCITY * MAX_VELOCITY) / (2.0 * MAX_DECEL);

  float remaining = abs_distance - abs_position;

  if (remaining <= 0.5)
    return 0.0;

  float vel;
  bool in_accel_phase = false;

  if (accel_distance + decel_distance >= abs_distance) {
    // Triangular profile: the move is too short to reach MAX_VELOCITY.
    float peak_distance = abs_distance * (MAX_DECEL / (MAX_ACCEL + MAX_DECEL));

    if (abs_position < peak_distance) {
      vel = sqrt(2.0 * MAX_ACCEL * abs_position);
      in_accel_phase = true;
    } else {
      vel = sqrt(2.0 * MAX_DECEL * remaining);
    }
  } else {
    // Trapezoidal profile: accelerate, cruise, decelerate.
    if (abs_position < accel_distance) {
      vel = sqrt(2.0 * MAX_ACCEL * abs_position);
      in_accel_phase = true;
    } else if (remaining < decel_distance) {
      vel = sqrt(2.0 * MAX_DECEL * remaining);
    } else {
      vel = MAX_VELOCITY;
    }
  }

  if (in_accel_phase && vel < MIN_VELOCITY) {
    vel = MIN_VELOCITY;
  }

  return direction * vel;
}
