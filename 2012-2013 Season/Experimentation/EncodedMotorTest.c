#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     IRsensor,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  motorA,          nxtMotorA,     tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          nxtMotorB,     tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          nxtMotorB,     tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     motor11,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motor12,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motor21,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorArm,      tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    servo2,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "../Headers/CSEnumerated.h"
#include "../Headers/CSGlobalVariables.h"
#include "../Headers/CSMethods.h"

#include "JoystickDriver.c"
#include "../Headers/CSEnumerated.h"
#include "../Headers/CSGlobalVariables.h"
#include "../Headers/CSMethods.h"

void initializeRobot() { return; }

void processMotors() {
	if ((Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X) > 15) || (Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X) < -15)) {
		MotorR(motor11, Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X));
		MotorF(motor21, Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X));
	}
	else if (!Button(CONTROLLER_A, 5) && !Button(CONTROLLER_A, 6) && (Hat(CONTROLLER_A) == HAT_NONE)) {
		MotorS(motor11);
		MotorS(motor21);
	}

	if ((Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y) > 15) || (Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y) < -15)) {
		MotorF(motor12, Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y));
		//MotorF(motor22, Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y));
	}
	else if (!Button(CONTROLLER_A, 5) && !Button(CONTROLLER_A, 6) && (Hat(CONTROLLER_A) == HAT_NONE)) {
		MotorS(motor12);
		MotorS(motor22);
	}

	//if(Button(CONTROLLER_A, 5)) spinRight();
	//else if(Button(CONTROLLER_A, 6)) spinLeft();
}

void processServos() {
	if(Button(CONTROLLER_A, 1)) {
		servo[servo1] += 1;
		servo[servo2] += 1;
		servo[servo3] += 1;
		servo[servo4] += 1;
		servo[servo5] += 1;
	}
	else if(Button(CONTROLLER_A, 2)) {
		servo[servo1] += -1;
		servo[servo2] += -1;
		servo[servo3] += -1;
		servo[servo4] += -1;
		servo[servo5] += -1;
	}
}

task main() {
  initializeRobot();
  for (int i=0; ; i++) {
  	CatsAndCorgis();
  	processMotors();
  	processServos();
  }
}