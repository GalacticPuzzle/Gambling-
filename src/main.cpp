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
void competition_initialize() {

     pros::Task screen_task([&]() {
        while (true) {
            // Combine position data onto one line
            pros::lcd::print(1, "X:%.1f Y:%.1f T:%.1f", 
                           chassis.getPose().x,
                           chassis.getPose().y,
                           chassis.getPose().theta);
        
            pros::delay(20);
        }
    });
}

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
    // chassis.setPose(-0, 0, 0);
    // chassis.moveToPoint(-2, -40, 2500, {.forwards = false, .maxSpeed = 70}, true);
    // pros::delay(1100); 

    // mogoMech.set_value(true);

    // chassis.waitUntil(15);
    // mogoMech.set_value(true);
    // chassis.waitUntilDone();

    // intakeAuton(-100000);
    // pros::delay(2000); 

    // chassis.turnToHeading(-75, 25000);
    // chassis.waitUntilDone();



//******************  ***************SKILLLLLSSS PROGGGGGGG *********************************************
chassis.setPose(0,0,0);
mogoMech.set_value(false);
chassis.moveToPoint(-0.2, -5.7, 1000,{.forwards = false, .maxSpeed = 60}, true);
pros::delay(500);
intakeAuton(-12000);
pros::lcd::print(1,"37, suzie, chhibber");
chassis.moveToPoint(0.3, -14.6, 25000, {.forwards = false, .maxSpeed = 50}, false);
chassis.turnToPoint(37.9, 13.3, 25000);










    //chassis.moveToPoint(-24.2, -34    .9, 25000,{.forwards = true, .maxSpeed = 80}, false);
    
    // mogoMech.set_value(false);
    // pros::lcd::print(0, "done");
    // chassis.turnToHeading(90, 23000);
    // chassis.waitUntilDone();
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
    //pros::lcd::print(1, "X:%.1f Y:%.1f T:%.1f", 
                           //chassis.getPose().x,
                           //chassis.getPose().y,
                           //chassis.getPose().theta);
    tankDrive();
    Intakerun();
    grab();
    pros::delay(20); 
    }
}
