#include "Odometry.h"

#include <Arduino.h>

#include "Config.h"
#include "TurnSensor.h"
#include "Hardware.h"

float heading = 0.0;  // deg
float lateral = 0.0;  // cm
float velocity = 0.0; // cm/s

unsigned long vel_last_time = 0;
int32_t vel_last_counts = 0;

static const float WHEEL_CIRCUMFERENCE = 3.14159 * WHEEL_DIAMETER_CM;

void update_heading() {
  turnSensorUpdate();

  int32_t signedAngle = (int32_t)turnAngle;

  heading = (float)signedAngle / (float)turnAngle1;
  if (heading > 180.0)
    heading -= 360.0;
  if (heading < -180.0)
    heading += 360.0;
}

void update_velocity() {
  unsigned long now = millis();
  float dt = (now - vel_last_time) / 1000.0;
  if (dt <= 0)
    dt = 0.001;

  int32_t left_counts = encoders.getCountsLeft();
  int32_t right_counts = encoders.getCountsRight();
  int32_t average_counts = (left_counts + right_counts) / 2;

  int32_t delta_counts = average_counts - vel_last_counts;
  float distance_cm =
      (delta_counts / COUNTS_PER_REVOLUTION) * WHEEL_CIRCUMFERENCE;

  velocity = distance_cm / dt;
  lateral += distance_cm;

  vel_last_counts = average_counts;
  vel_last_time = now;
}

void update() {
  update_velocity();
  update_heading();
}

void reset_encoders() {
  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();
  lateral = 0.0;
  vel_last_counts = 0;
  vel_last_time = millis();
}

float distance_to_counts(float distance) {
  return (distance / WHEEL_CIRCUMFERENCE) * COUNTS_PER_REVOLUTION;
}
