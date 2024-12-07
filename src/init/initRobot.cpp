#include "main.h" // IWYU pragma: keep
#include "pros/misc.h" // IWYU pragma: keep
#include "../../include/init/initRobot.hpp" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep


// left motor group - making all motors consistently reversed
pros::MotorGroup left_motor_group({-14, -15, -16}, pros::MotorGears::blue);
// right motor group - making all motors consistently forward
pros::MotorGroup right_motor_group({13, 11, 12}, pros::MotorGears::blue);
pros::Motor IntakeMotor(20, pros::v5::MotorGears::blue); 



// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              360, // corrected drivetrain rpm to 360
                              2 // horizontal drift is 2 (for now)
);




// imu  
pros::Imu imu(19);

// odometry settings
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(8, // reduced kP for smoother movement
                                              0.001, // small integral gain to eliminate steady-state error
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              15 // reduced max acceleration for smoother starts
);

// angular PID controller
lemlib::ControllerSettings angular_controller(3, // increased kP for better turning
                                              0.001, // small integral gain
                                              8, // reduced kD slightly
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);