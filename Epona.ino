#include <SPI.h>
#include <Ethernet.h>
#include <RobotOpen.h>

USBJoystick usb1('0');

//ToDo: shooter spinup, index motor, ball feed motor
// all will be momentary driven

void setup()
{
  RobotOpen.begin();
}


void enabled() {
  RobotOpen.setPWM(SIDECAR_PWM1, usb1.makePWM(ANALOG_LEFTY, INVERT));
  RobotOpen.setPWM(SIDECAR_PWM2, usb1.makePWM(ANALOG_RIGHTY, NORMAL));
}


void disabled() {
}
void timedtasks() {
}

void loop() {
  RobotOpen.pollDS();
  if (RobotOpen.enabled())
    enabled();
  else
    disabled();
  timedtasks();
  RobotOpen.outgoingDS();
}
