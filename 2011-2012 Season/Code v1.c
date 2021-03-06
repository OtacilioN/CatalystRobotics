#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Hubs,  S2, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          nxtMotorA,     tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorRight,    tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorLeft,     tmotorNormal, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S2_C1_1,     motorF,        tmotorNormal, openLoop, encoder)
#pragma config(Motor,  mtr_S2_C1_2,     motorG,        tmotorNone, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*/

#include "JoystickDriver.c"  //le joystick things

/* Chris' Amazing Documentation: runMotorTime method
  This runMotorTime method takes in a tMotor object, and two integers
  and will move the specified motor for the specified amount of time (in
  milliseconds) at the specified amount of power. To have the
  motor run in the opposite direction, multiply the power by -1.
*/
void runMotorTime(tMotor motorToRun, int power, int milliseconds)
{
   motor[motorToRun] = power;
   wait1Msec(milliseconds);
   motor[motorToRun] = 0;
}

/* Chris' Amazing Documentation: runMotorEncoder method
  This runMotorEncoder method takes in a tMotor object, and two integers
  and will move the specified motor to the specified angle (in
  degrees) at the specified power. When using this method, it is
  important to remember that motor encoder considers the resting
  position of the motor to be "zero" degrees and, as a result, the angle
  entered into this method will move it to that amount of degrees
  relative to the resting spot. This method also resets the resting
  spot (by powering off the motor) and the encoder after each time
  it is called.
*/
void runMotorEncoder(tMotor motorToRun, int power, int degrees)
{
  nMotorEncoder[motorToRun] = 0; //reset the encoder
  nMotorEncoderTarget[motorToRun] = degrees; //set encoder target for motor to reach
  motor[motorToRun] = power; //turn on motor and set power
  while(nMotorRunState[motorToRun] != runStateIdle)  // While Motor B is still running (hasn't reached target yet):
  {
    // Do not continue.
  }
  motor[motorToRun] = 0; //stop motor
}

void TeleOp()
{
	getJoystickSettings(joystick);  //get updates from joystick

  if(joystick.joy1_TopHat == 0)
	{
	  motor[motorA] = 25; //forward
	}
	else if(joystick.joy1_TopHat == 4)
	{
	  motor[motorA] = -25; //reverse
	}
	else
	{
	  motor[motorA] = 0; //off
	}

	/*
	//motor[motorRight] = joystick.joy1_x2;      // MotorB's powerlevel is set to the x2 stick's current position.
	if (((joystick.joy1_y2 > -15) && (joystick.joy1_y2 < 15)) || ((joystick.joy1_y1 > -15) && (joystick.joy1_y1 < 15)) ) {}
  else
  {*/
  motor[motorRight] = -joystick.joy1_y2*0.5;      // MotorB's powerlevel is set to the y2 stick's current position.
  motor[motorLeft] = -joystick.joy1_y1*0.5;      // MotorB's powerlevel is set to the y2 stick's current position.
  /*
  }
  */


	/*
	if (joystick.joy1_x2 <= -15 || joystick.joy1_x2 >= 15)
  {
	  motor[motorRight] = joystick.joy1_y2*0.5;
	  motor[motorLeft] = joystick.joy1_y2*0.5;
  }
  else if ((joystick.joy1_y2 >= -20)&& (joystick.joy1_y2 <= 30) && (joystick.joy1_x2 == -128))
  {
	  motor[motorRight] = joystick.joy1_y2*0.5;
	  motor[motorLeft] = joystick.joy1_y2*-0.5;
  }
  else if ((joystick.joy1_y2 >= -20) && (joystick.joy1_y2 <= 30) && (joystick.joy1_x2 == 127))
  {
	  motor[motorRight] = joystick.joy1_y2*-0.5;
	  motor[motorLeft] = joystick.joy1_y2*0.5;
  }
  else {}
  */

}

task main()
{
  //*** autonomous
  //runMotorTime(motorA, 40, 3000); //close claw
  //runMotorEncoder(motorA, -25, 90); //open claw
  //*** tele-op
  //prepareTeleOp(); //sets up controllers, prepares for tele-op
  //waitForStart(); //waits for controllers to be picked up
  //waitForStart();
  /*
  while (true)
  {
	  TeleOp();
	  //insert other things that must be infinitely looped
  }
  */
  //motor[motorRight] = 10;
  //motor[motorLeft] = 10;
  while (true)
  { TeleOp(); }
}
