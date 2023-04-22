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
bool collecting = false;
bool roller = false;
enum colorTypes {blue, red, undefined};
const double AUTODISTANCE = 5;
colorTypes roundColor = colorTypes::undefined;

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
void setRoundColorRed(void){
  if(roundColor == colorTypes::red) return;
  if(roundColor == colorTypes::blue){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
  }else{
    Brain.Screen.newLine();
  }
  roundColor = colorTypes::red;
  Brain.Screen.print("Color : Red");
}
void setRoundColorBlue(void){
  if(roundColor == colorTypes::blue) return;
  if(roundColor == colorTypes::red){
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
  }else{
    Brain.Screen.newLine();
  }
  roundColor = colorTypes::blue;
  Brain.Screen.print("Color : Blue");
}
void shoot(void){
  catapult_motor.setBrake(brakeType::coast);
  if(!LimitB.pressing()) spinTillPressed(LimitB, catapult_motor);
  spinTillPressed(BumperA, catapult_motor);
  spinTillPressed(LimitB, catapult_motor);
  catapult_motor.setBrake(brakeType::hold);
}

void expand(void){
  expandLeft.spin(directionType::fwd, 200, velocityUnits::pct);
  expandRight.spin(directionType::fwd, 200, velocityUnits::pct);
  wait(2000, msec);
  expandLeft.stop();
  expandRight.stop();
  }
void setIntake(void){
  Brain.Screen.print("pressed");
  if(collecting){
    collecting = false;
    intakeMotor.stop();
  }else{
    collecting = true;
    intakeMotor.spin(directionType::fwd);
  }
}
void toggleRoller(void){
  if(roller){
    roller = false;
    rollerMotor.stop();
  }else{
    roller = true;
    rollerMotor.spin(directionType::fwd);
  }
}

void pre_auton(void) {
  // Initializing Robot Configuration.
  controller1.ButtonR1.pressed(shoot);
  controller1.ButtonX.pressed(setIntake);
  controller1.ButtonB.pressed(expand);
  controller1.ButtonA.pressed(toggleRoller);

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
  setIntake();
  if(Drivetrain.driveFor(AUTODISTANCE, distanceUnits::cm)){
      Drivetrain.turn(turnType::left);
  }

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
    if(!roundColor == colorTypes::undefined){
      switch(roundColor){
        case colorTypes::red :
          vision7.takeSnapshot(sigRed);
          break;
        case colorTypes::blue :
          vision7.takeSnapshot(sigBlue);
          break;
        default:
          break;
      }
      if(vision7.largestObject.exists){
        rollerMotor.spin(directionType::fwd);
      }else{
        rollerMotor.stop();
      }
    }

    //Left motor, vertical axis of left joystick
    motor_left.spin(vex::directionType::fwd, controller1.Axis3.position(vex::percentUnits::pct), vex::velocityUnits::pct);
    //Right motor, vertical axis of right joystick
    motor_right.spin(vex::directionType::fwd, controller1.Axis2.position(vex::percentUnits::pct), vex::velocityUnits::pct);
    
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
