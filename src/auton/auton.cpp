#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/motor_group.hpp" // IWYU pragma: keep
#include "init/initRobot.hpp"
#include "init/auton.hpp"
#include "subsystems\mogo.hpp"
#include "subsystems\intake.hpp"
#include "subsystems\drive.hpp"
#include "subsystems\ladyBrown.hpp"

// Define the limit switch port
#define LIMIT_SWITCH_PORT 'A'

// Global variable definition
AutonomousMode selectedAuton = AutonomousMode::WP_RED;  // Default autonomous

// Initialize limit switch
pros::ADIDigitalIn limitSwitch(LIMIT_SWITCH_PORT);

void initializeAutonSelector() {
    int pressCount = 0;
    bool lastState = false;
    
    // Display initial selection
    pros::lcd::clear_line(1);
    pros::lcd::print(1, "Current Auton: WP_RED");
    
    while (true) {
        bool currentState = limitSwitch.get_value();
        
        // Detect rising edge (button press)
        if (currentState && !lastState) {
            pressCount = (pressCount + 1) % 3;  // Cycle through 3 options
            
            // Update selected autonomous based on press count
            switch (pressCount) {
                case 0:
                    selectedAuton = AutonomousMode::WP_RED;
                    pros::lcd::clear_line(1);
                    pros::lcd::print(1, "Current Auton: WP_RED");
                    break;
                case 1:
                    selectedAuton = AutonomousMode::WP_BLUE;
                    pros::lcd::clear_line(1);
                    pros::lcd::print(1, "Current Auton: WP_BLUE");
                    break;
                case 2:
                    selectedAuton = AutonomousMode::SKILLS;
                    pros::lcd::clear_line(1);
                    pros::lcd::print(1, "Current Auton: SKILLS");
                    break;
            }
            
            // Debounce delay
            pros::delay(50);
        }
        
        lastState = currentState;
        pros::delay(20);  // Small delay to prevent excessive CPU usage
    }
}

AutonomousMode getSelectedAuton() {
    return selectedAuton;
}

void autWPRED(){
    chassis.calibrate();
     chassis.setPose(-58.89, -22.7, 180);
     mogoMech.set_value(false);
     chassis.moveToPoint(-19.3, -23.7, 2500,    {.forwards = false, .maxSpeed=100, }, true);
     pros::delay(1000); 
}

void autWPBLUE() {
    // Implement blue autonomous routine
}

void skillsAut() {
    // Implement skills autonomous routine
}
