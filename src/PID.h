// PID.h
// Minimal PID controller that measures its own time step with millis().

#pragma once

class PID {
public:
  PID(float kp, float ki, float kd);

  // Returns the control output for the given setpoint and measurement.
  float compute(float setpoint, float measured);

private:
  float kp, ki, kd;
  float previous_error;
  float integral;
  unsigned long last_time;
};
