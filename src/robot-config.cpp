#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
vex::motor      motor_right(vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor      motor_left(vex::PORT2, vex::gearSetting::ratio18_1, true);
vex::controller controller1(vex::controllerType::primary);
vex::motor      catapult_motor(vex::PORT3, vex::gearSetting::ratio18_1, false);
vex::bumper     BumperA(Brain.ThreeWirePort.A);
vex::limit      LimitB(Brain.ThreeWirePort.B);
vex::motor      expandLeft(vex::PORT4, vex::gearSetting::ratio18_1, false);
vex::motor      expandRight(vex::PORT5, vex::gearSetting::ratio18_1, true);
vex::motor      intakeMotor(vex::PORT6, vex::gearSetting::ratio18_1, false);
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}