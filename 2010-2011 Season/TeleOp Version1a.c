#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S3,     HTIRL,               sensorLowSpeed)
#pragma config(Sensor, S4,     HTGYRO,              sensorNone)
#pragma config(Motor,  mtr_S1_C1_1,     leftMotor,     tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightMotor,    tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     wristMotor,    tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    elbow,                tServoNormal)
#pragma config(Servo,  srvo_S1_C2_2,    wrist,                tServoNormal)
#pragma config(Servo,  srvo_S1_C2_3,    tipperL,              tServoNormal)
#pragma config(Servo,  srvo_S1_C2_4,    tipperR,              tServoNormal)
#pragma config(Servo,  srvo_S1_C2_5,    trapperL,             tServoNormal)
#pragma config(Servo,  srvo_S1_C2_6,    trapperR,             tServoNormal)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define button1 0x01
#define button2 0x02
#define button3 0x04
#define button4 0x08
#define button5 0x10
#define button6 0x20
#define button7 0x40
#define button8 0x80
#define button9 0x100
#define button10 0x200


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "../3rd Party Sensor Drivers/drivers/HTDIR-driver.h"
#include "../3rd Party Sensor Drivers/drivers/HTGYRO-driver.h"
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

int wristPosition = -84;
int elbowPosition = 1;
int trapperPosition = 100;
int tipperPosition = 100;
int servoIncrement = 8;
long Gyro_offset;           //**offset value may vary depending on sensor & temperature
long Gyro_value;
long sum;



/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to initialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  nMotorPIDSpeedCtrl[wristMotor] = mtrSpeedReg;
  nMotorEncoder[wristMotor] = 0; //Resets Encoder Values

  //servoChangeRate[wrist] = 2;    // Slows the Change Rate of wrist to 2 positions per update.  Default = 10
  servo[wrist] = wristPosition;
  servo[elbow] = elbowPosition;
  servo[trapperL] = trapperPosition;
  servo[trapperR] = 256 - trapperPosition;
  servo[tipperL] = tipperPosition;
  servo[tipperR] = 256 - tipperPosition;

  Gyro_offset = HTGYROstartCal(HTGYRO);   //start calibration, but do not trust results
  for (int i = 0 ; i < 10; i++)           //instead read 10 values and generate average offset
  {
    sum = sum + HTGYROreadRot(HTGYRO);
    wait1Msec(50);
  }
  Gyro_offset = sum / 10.0;

return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Motor Control
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void motorControlProportional()
{
  int nLeft;
  int nRight;
  int threshold = 2;                /* int 'threshold' will allow us to ignore low       */
                                    /* readings that keep our robot in perpetual motion. */
  //getJoystickSettings(joystick);
  nLeft = (int)(joystick.joy1_y1 * 0.79);    //read joystick, scale 128 --> 100
  nRight = (int)(joystick.joy1_y2 * -0.79);  //read joystick, scale 128 --> 100

  if (joystick.joy1_Buttons & button6) /* Fine Motor Control */
  {
    nLeft = nLeft / 2;
    nRight = nRight / 2;
  }

  if (abs(nLeft) > threshold)     /* run Left motor */
    motor[leftMotor]  = nLeft;
  else
    motor[leftMotor]  = 0;

  if (abs(nRight) > threshold)     /* run Left motor */
    motor[rightMotor]  = nRight;
  else
    motor[rightMotor]  = 0;

  return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Arm Control
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void armControlProportional()
{
  int nElbow;
  int nWrist;

    // Elbow (Big Motor) Control
    if ((joystick.joy2_Buttons & button2) && (nMotorEncoder[wristMotor] < 500))
    {
      motor[wristMotor] = 10;
    }
    else if ((joystick.joy2_Buttons & button4) && (nMotorEncoder[wristMotor] > -500))
    {
      motor[wristMotor] = -10;
    }
    else if ((joystick.joy2_Buttons & button2) && (nMotorEncoder[wristMotor] < 500))
    {
      motor[wristMotor] = 30;
    }
    else if ((joystick.joy2_Buttons & button4) && (nMotorEncoder[wristMotor] > -500))
    {
      motor[wristMotor] = -30;
    }
    else
    {
      motor[wristMotor] = 0;
    }

  // Wrist (Servo) Control
  nElbow = joystick.joy2_y1  + 128;
  nWrist  = joystick.joy2_y2  + 128;

  servo[wrist] = nWrist - 84;
  servo[elbow] = nElbow;

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Button Control
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void buttonControl()
{

  if(joystick.joy2_Buttons & button6)             //joystick 2 "1" button
   {
     wristPosition = wristPosition+servoIncrement;
     servo[wrist] = wristPosition;
   }

  if((joystick.joy2_Buttons & button6) && (wristPosition > 0))               //joystick 2 "3" button
   {
     wristPosition = wristPosition-servoIncrement;
     servo[wrist] = wristPosition;
   }

  if((joystick.joy2_Buttons & button6) && (elbowPosition < 127))             //joystick 2 "4" button
   {
     elbowPosition = elbowPosition+servoIncrement;
     servo[elbow] = wristPosition;
   }

  if((joystick.joy2_Buttons & button6) && (elbowPosition > -127))               //joystick 2 "2" button
   {
     elbowPosition = elbowPosition-servoIncrement;
     servo[elbow] = wristPosition;
   }

   //POV to control trapper
  if((joystick.joy2_TopHat == 4) && (trapperPosition < 256))  //down POV button
   {
     trapperPosition = trapperPosition+servoIncrement;
     servo[trapperL] = trapperPosition;
     servo[trapperR] = 256 - trapperPosition;
   }

  if((joystick.joy2_TopHat == 0) && (trapperPosition > 100))  //up POV button
   {
     trapperPosition = trapperPosition-servoIncrement;
     servo[trapperL] = trapperPosition;
     servo[trapperR] = 256 - trapperPosition;
   }

  //Driver POV to control tippers
  if((joystick.joy1_TopHat == 4) && (tipperPosition < 256))  //down POV button
   {
     tipperPosition = tipperPosition+servoIncrement;
     servo[tipperL] = tipperPosition;
     servo[tipperR] = tipperPosition;
   }

  if((joystick.joy1_TopHat == 0) && (tipperPosition > 0))  //up POV button
   {
     tipperPosition = tipperPosition-servoIncrement;
     servo[tipperL] = tipperPosition;
     servo[tipperR] = tipperPosition;
   }

  return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  initializeRobot();


 // waitForStart();                 // wait for start of tele-op phase


  while (true)                    //infinite loop
  {
    getJoystickSettings(joystick);
    motorControlProportional();
    armControlProportional();
    buttonControl();
    Gyro_value=HTGYROreadRot(HTGYRO) - Gyro_offset;  //read the gyro sensor
    sum=HTDIRreadDCDir(S3);
    wait1Msec(10);
  }

}