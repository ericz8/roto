// MotionProfile.h
// Trapezoidal velocity profile for straight-line moves.

#pragma once

// Returns the target velocity (cm/s) at `position` cm into a move of
// `total_distance` cm. The sign of `total_distance` sets the direction.
// Falls back to a triangular profile when the move is too short to reach
// MAX_VELOCITY.
float compute_trapezoidal_velocity(float position, float total_distance);
