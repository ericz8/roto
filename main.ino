// roto - Science Olympiad Robot Tour
// Pololu 3pi+ 32U4 robot that drives a pre-programmed route on a grid of
// 50 cm tiles, paced to finish close to a target time.
//
// Code layout:
//   src/Config.h         field, robot and timing constants
//   src/Route.cpp        the route to run (edit this per field)
//   src/Commands.h       command type and route shorthands (FF, L90, ...)
//   src/Odometry.*       heading, distance and velocity estimation
//   src/MotionProfile.*  trapezoidal velocity profile
//   src/Controller.*     velocity + heading PID control
//   src/PID.*            PID controller
//   src/TurnSensor.*     gyro setup and integration (from Pololu example)

#include <Pololu3piPlus32U4.h>
#include <Pololu3piPlus32U4IMU.h>
#include <Wire.h>

#include "src/Config.h"
#include "src/Controller.h"
#include "src/Hardware.h"
#include "src/Odometry.h"
#include "src/Route.h"
#include "src/TurnSensor.h"

using namespace Pololu3piPlus32U4;

Motors motors;
Encoders encoders;
ButtonA buttonA;
OLED display;
IMU imu;

double time_per_move;
int current_command = 0;

// UNUSED: not read or written anywhere.
bool direction = false;

// Keeps a heading in the range -180..180 degrees.
static float wrap_heading(float angle) {
  if (angle > 180.0)
    angle -= 360.0;
  if (angle < -180.0)
    angle += 360.0;
  return angle;
}

// Sets the controller targets for a command that is just starting.
static void start_command(const Command &cmd) {
  if (cmd.type == Command::FORWARD) {
    reset_encoders();
    target_lateral = cmd.value;
  } else if (cmd.type == Command::BACKWARD) {
    reset_encoders();
    target_lateral = -cmd.value;
    Serial.println(target_lateral);
  } else if (cmd.type == Command::LEFT) {
    target_heading = wrap_heading(target_heading + cmd.value);
  } else if (cmd.type == Command::RIGHT) {
    target_heading = wrap_heading(target_heading - cmd.value);
  }
}

void setup() {
  turnSensorSetup();
  turnSensorReset();

  display.clear();

  // Spread the target time evenly over every command.
  time_per_move = (double)TARGET_TIME / (double)NUM_COMMANDS;
  time_per_move =
      constrain(time_per_move, MIN_TIME_PER_MOVE, MAX_TIME_PER_MOVE);

  for (int i = 0; i < NUM_COMMANDS; i++) {
    commands[i].duration = time_per_move;
  }
}

void loop() {
  update();
  apply_controls();

  display.gotoXY(0, 0);
  display.print(heading);

  // Debug telemetry:
  // Serial.print("velocity: ");
  // Serial.println(velocity);
  // Serial.print("target_velocity: ");
  // Serial.println(target_velocity);

  static unsigned long command_start_time = 0;
  if (current_command < NUM_COMMANDS) {
    Command cmd = commands[current_command];

    if (command_start_time == 0) {
      command_start_time = millis();
      start_command(cmd);
    }

    bool move_complete = (millis() - command_start_time >= cmd.duration * 1000);

    if (move_complete) {
      target_lateral = 0.0;
      lateral = 0.0;
      stop_motors();
      delay(20);
      current_command++;

      display.println(heading);
      command_start_time = 0;
    }
  } else {
    stop_motors();
  }

  delay(10);
}
