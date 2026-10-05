// Hardware.h
// Shared handles to the 3pi+ 32U4 peripherals. The objects themselves are
// defined in main.ino.

#pragma once

// Only the main library header here: Pololu3piPlus32U4IMU.h contains the IMU
// implementation and must be included exactly once (in main.ino).
#include <Pololu3piPlus32U4.h>

extern Pololu3piPlus32U4::Motors motors;
extern Pololu3piPlus32U4::Encoders encoders;
extern Pololu3piPlus32U4::ButtonA buttonA;
extern Pololu3piPlus32U4::OLED display;
extern Pololu3piPlus32U4::IMU imu;
