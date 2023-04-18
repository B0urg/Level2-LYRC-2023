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

void spinTillPressed(bumper b, motor m){
  bool done = false;
  while(!done){
    m.spin(directionType::fwd);
    if(b.pressing()){
      done = true;
      m.stop();
    }
  }
}
void spinTillPressed(limit l, motor m){
  bool done = false;
  while(!done){
    m.spin(directionType::fwd);
    if(l.pressing()){
      done = true;
      m.stop();
    }
  }
}

void shoot(){
  catapult_motor.setBrake(brakeType::coast);
  if(!LimitB.pressing()) spinTillPressed(LimitB, catapult_motor);
  spinTillPressed(BumperA, catapult_motor);
  spinTillPressed(LimitB, catapult_motor);
  catapult_motor.setBrake(brakeType::hold);
}

void expand(){
  Brain.Screen.print("pressed");
  expandLeft.spin(directionType::fwd, 200, velocityUnits::pct);
  expandRight.spin(directionType::fwd, 200, velocityUnits::pct);
  wait(2000, msec);
  expandLeft.stop();
  expandRight.stop();
  }
void setIntake(){
  if(!intakeMotor.isSpinning()){
    intakeMotor.spin(directionType::fwd);
  }else{
    intakeMotor.stop();
  }
}


void pre_auton(void) {
  // Initializing Robot Configuration.
  vexcodeInit();
  if(!LimitB.pressing()) spinTillPressed(LimitB, catapult_motor);

}
  /**
   * 
  
  catapult_motor.stop();
  catapult_motor.resetPosition();
  while(catapult_motor.position(rotationUnits::deg) != 530){
    catapult_motor.spin(directionType::fwd);
  }
  catapult_motor.stop(brakeType::hold);
  */
  // TODO: clearing encoders, setting servo positions, ...

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
    if(controller1.ButtonR1.pressing()) shoot();
    if(controller1.ButtonB.pressing()) expand();
    if(controller1.ButtonX.pressing()) setIntake();
    wait(20, msec);
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
