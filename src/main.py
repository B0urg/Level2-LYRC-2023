# ----------------------------------------------------------------------------- #
#                                                                               #              
#    Project:        Level2-LYRC-2023                                           #
#    Module:         main.py                                                    #
#    Author:         Kim Bourg                                                  #
#    Created:        Fri Aug 05 2022                                            #
#    Description:                                                               # 
#                                                                               #
#                                                                               #                                                                          
#                                                                               #                                                                          
# ----------------------------------------------------------------------------- #

# Library imports
from vex import *
import time

# Brain should be defined by default
autoPilot=False
brain=Brain()
controller_1 = Controller(PRIMARY)
bumper_a = Bumper(brain.three_wire_port.a)


left_drive_smart = Motor(Ports.PORT1, GearSetting.RATIO_18_1, False)
right_drive_smart = Motor(Ports.PORT2, GearSetting.RATIO_18_1, True)
drivetrain = DriveTrain(left_drive_smart, right_drive_smart, 319.19, 295, 40, MM, 1)
brain.screen.clear_screen()
brain.screen.set_cursor(1,1)
brain.screen.print("Autopilot : Off")
MAX_SPEED = 40


def startAutoPilot():
    global autoPilot
    if autoPilot == True:
        return
    autoPilot = True
    t_end = time.time() + 10
    while time.time() < t_end:
        if(bumper_a.pressing() == 1):
            drivetrain.drive(REVERSE, 100)
            wait(1, SECONDS)
            drivetrain.turn(LEFT, 50)
            wait(1, SECONDS)
        else:
            drivetrain.drive(FORWARD)
    autoPilot = False
    drivetrain.stop()


controller_1.buttonB.pressed(startAutoPilot)
while True:
    brain.screen.clear_screen()
    brain.screen.set_cursor(1,1)
    brain.screen.print('Autopilot : ', 'On' if autoPilot == True else "Off")
    brain.screen.next_row()
    brain.screen.print("Bumper:", "True" if bumper_a.pressing() == 1 else "False")
    brain.screen.next_row()
    brain.screen.next_row()
    wait(100 ,MSEC)
