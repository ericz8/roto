#include "PID.h"

#include <Arduino.h>

PID::PID(float kp, float ki, float kd)
    : kp(kp), ki(ki), kd(kd), previous_error(0), integral(0),
      last_time(millis()) {}

float PID::compute(float setpoint, float measured) {
  unsigned long now = millis();
  float dt = (now - last_time) / 1000.0;
  if (dt <= 0)
    dt = 0.001;

  float error = setpoint - measured;
  integral += error * dt;
  float derivative = (error - previous_error) / dt;

  previous_error = error;
  last_time = now;

  return kp * error + ki * integral + kd * derivative;
}
