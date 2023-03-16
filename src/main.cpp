/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/


#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// global instances of devices

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration.
  vexcodeInit();

  // TODO: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/* This function will run after the 15 seconds autonomous period and will    */
/*         last 1:45 and is basically used to controll the motors            */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    //Left motor, vertical axis of left joystick
    motor_left.spin(vex::directionType::fwd, controller1.Axis3.position(vex::percentUnits::pct), vex::velocityUnits::pct);
    //Right motor, vertical axis of right joystick
    motor_right.spin(vex::directionType::fwd, controller1.Axis2.position(vex::percentUnits::pct), vex::velocityUnits::pct);
    wait(20, msec); // Sleep the task for a short amount of time to
  }
}


int main() {
  // Run the pre-autonomous function.
  pre_auton();
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  usercontrol();


  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
