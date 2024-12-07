#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/motor_group.hpp" // IWYU pragma: keep
#include "init/initRobot.hpp"
#include "subsystems\mogo.hpp"
#include "subsystems\intake.hpp"
#include "subsystems\drive.hpp"
#include "subsystems\ladyBrown.hpp"


// initialize function. Runs on program startup
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
    IntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    LiftMotor1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    LiftMotor2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);
    
    // Start autonomous selector task
    //pros::Task selectorTask(initializeAutonSelector);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is e\\nabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    chassis.setPose(-58.89, -22.7, 180);
    intakeAuton(-10000);
    mogoMech.set_value(false);
    pros::lcd::print(0, "done");
    chassis.turnToHeading(90, 23000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-19.3, -23.7, 2500, {.forwards = false, .maxSpeed = 100}, true);
    chassis.waitUntilDone();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
pros::Controller controller(pros::E_CONTROLLER_MASTER);

void opcontrol() {
while (true) {
    tankDrive();
    Intakerun();
    grab();
    pros::delay(20); 
    }
}
