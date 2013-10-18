#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <RobotOpen.h>



/* I/O Setup */
ROJoystick usb1(1);         // Joystick #1
ROPWM leftDrive(0);
ROPWM rightDrive(1);

ROPWM index(3);
ROPWM shoot(4);
ROPWM feed(2);

ROTimer time1;

int offset = 0;

void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
  
  time1.queue(0);
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  // Constantly update PWM values with joystick values
  // Analog sticks feed back values from 0-255
  // 255 - usb1.leftY() to invert a drive
  leftDrive.write(usb1.leftY()*.85+offset);
  rightDrive.write(usb1.rightY()*.85+offset);
  
  if (usb1.btnX()){
    feed.write(usb1.btnY() ? 2 : 255);
  } else {
    feed.write(127);
  }
 
  if (usb1.btnA()){
    index.write(255);
  } else {
    index.write(127);
  }
  
  if (usb1.btnB()){
    shoot.write(255);
  } else {
    shoot.write(127);
  }
}


/* This is called while the robot is disabled
 * PWMs and Solenoids are automatically disabled
 */
void disabled() {
  // safety code
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */
void timedtasks() {
  RODashboard.publish("Uptime Seconds", ROStatus.uptimeSeconds());
  
  RODashboard.publish("Drive Offset", offset);
  
  if(time1.ready()){
  
  if (usb1.btnLShoulder()){
    offset += 1;
  }
  
  if (usb1.btnRShoulder()){
    offset -= 1;
  }
  time1.queue(100);
  }
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}
