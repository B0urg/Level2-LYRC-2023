using namespace vex;

extern brain Brain;
vex::motor      motor_right(vex::PORT15, vex::gearSetting::ratio18_1, true);
vex::motor      motor_left(vex::PORT16, vex::gearSetting::ratio18_1, false);
vex::controller controller1(vex::controllerType::primary);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
