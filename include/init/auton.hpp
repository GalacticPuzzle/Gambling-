#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp"  // IWYU pragma: keep

// Autonomous modes
enum class AutonomousMode {
    SKILLS,
    WP_RED,
    WP_BLUE
};

// Function declarations
void autWPRED();
void autWPBLUE();
void skillsAut();

// Autonomous selector functions
void initializeAutonSelector();
AutonomousMode getSelectedAuton();

// Global variable to store selected autonomous
extern AutonomousMode selectedAuton;
