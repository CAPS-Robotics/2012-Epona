#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <RobotOpen.h>

/* I/O Setup */
ROJoystick usb1(1);         // Joystick #1
ROPWM leftDrive(0);
ROPWM rightDrive(1);

void setup()
{
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
}

void enabled() {
  leftDrive.write(usb1.leftY());
  rightDrive.write(usb1.rightY());
}

void disabled() {
}


void timedtasks() {
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}

