#include "main.h" // IWYU pragma: keep
#include "init/initRobot.hpp"
#include "subsystems\mogo.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep


bool mogoToggle = false;
pros::adi::DigitalOut mogoMech('A');

void grab(){
      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
        mogoToggle = !mogoToggle;
        mogoMech.set_value(mogoToggle);
  }
}