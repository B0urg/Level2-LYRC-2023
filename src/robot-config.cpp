#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;
vex::motor      motor_right(vex::PORT6, vex::gearSetting::ratio18_1, true);
vex::motor      motor_left(vex::PORT7, vex::gearSetting::ratio18_1, false);
vex::controller controller1(vex::controllerType::primary);
vex::motor      catapult_motor(vex::PORT8, vex::gearSetting::ratio18_1, false);
vex::potV2      pot1(Brain.ThreeWirePort.A);
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // Nothing to initialize
}