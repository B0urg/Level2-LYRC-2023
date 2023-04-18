using namespace vex;

extern brain Brain;
extern vex::motor      motor_right;
extern vex::motor      motor_left;
extern vex::controller controller1;
extern vex::motor      catapult_motor;
extern vex::bumper     BumperA;
extern vex::limit      LimitB;
extern vex::motor      expandLeft;
extern vex::motor      expandRight;
extern vex::motor      intakeMotor;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void);
