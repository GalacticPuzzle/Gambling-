#include "subsystems\intake.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h" // IWYU pragma: keep
#include "init/initRobot.hpp"


int intakeB = 0;

void Intakerun() {
    // Read controller buttons
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intakeB = 1;  // Run intake forward
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        intakeB = -1; // Run intake backward
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_A) && 
               !controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && 
               !controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        intakeB = (intakeB != 1) ? 1 : 0; // Toggle forward intake
    } else {
        intakeB = 0;  // Stop intake
    }

    // Apply intake state to motor
    if (intakeB == 1) {
        IntakeMotor.move(127);  // Forward
    } else if (intakeB == -1) {
        IntakeMotor.move(-127); // Backward
    } else {
        IntakeMotor.move(0);    // Stop
    }

    // Debugging Output
    pros::lcd::print(0, "Intake State: %d", intakeB);
}


//############################# AUT ###############################
void intakeAuton(int power){
    IntakeMotor.move_voltage(power);

}
