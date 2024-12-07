#include "main.h" // IWYU pragma: keep
#include "init/initRobot.hpp"
#include "subsystems\ladyBrown.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep


pros::Motor LiftMotor1(1,pros::v5::MotorGears::green);
pros::Motor LiftMotor2(2,pros::v5::MotorGears::green);

// Include the rotational sensor
extern pros::Rotation liftRotationSensor; // Declaration

// Initialize the rotational sensor on a specified port (e.g., port 1)
pros::Rotation liftRotationSensor(1);

// Constants for target angles
const int LIFT_DOWN_ANGLE = 0;
const int LIFT_UP_ANGLE = 20;
const int LIFT_SCORE_ANGLE = 135;

// LiftUp function: Moves the lift to 20 degrees
void LiftUp() {
  while (liftRotationSensor.get_position() < LIFT_UP_ANGLE) {
    LiftMotor1.move_voltage(12000);
    LiftMotor2.move_voltage(12000);
  }
  // Stop the motors once the position is reached
  LiftMotor1.move_voltage(0);
  LiftMotor2.move_voltage(0);
}

// LiftDown function: Moves the lift to 0 degrees
void LiftDown() {
  while (liftRotationSensor.get_position() > LIFT_DOWN_ANGLE) {
    LiftMotor1.move_voltage(-12000);
    LiftMotor2.move_voltage(-12000);
  }
  // Stop the motors once the position is reached
  LiftMotor1.move_voltage(0);
  LiftMotor2.move_voltage(0);
}

// LiftScore function: Moves the lift to 135 degrees, then back to 20 degrees
void LiftScore() {
  // Move to the score position
  while (liftRotationSensor.get_position() < LIFT_SCORE_ANGLE) {
    LiftMotor1.move_voltage(12000);
    LiftMotor2.move_voltage(12000);
  }
  // Brief pause at the score position
  pros::delay(500);

  // Move back down to the LiftUp position (20 degrees)
  while (liftRotationSensor.get_position() > LIFT_UP_ANGLE) {
    LiftMotor1.move_voltage(-12000);
    LiftMotor2.move_voltage(-12000);
  }
  // Stop the motors once the position is reached
  LiftMotor1.move_voltage(0);
  LiftMotor2.move_voltage(0);
}



