#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     lightSensor,    sensorLightActive)
#pragma config(Sensor, S3,     touchMuxer,     sensorHiTechnicTouchMux)
#pragma config(Sensor, S4,     IRseeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motor12,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motor11,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motor21,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motor22,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorArm,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// #pragma DebuggerWindows("debugStream")

#include "JoystickDriver.c"
#include "../Headers/CSEnumerated.h"
#include "../Headers/CSMethods.h"

void initializeRobot() { return; }

void processWheels() {

	if(Button(CONTROLLER_A, 5))
			spinRight();
	else if(Button(CONTROLLER_A, 6))
			spinLeft();

	if (((Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X) > 15) || (Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X) < -15)) && !Button(CONTROLLER_A, 7)) {
		MotorF(motor11, Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X));
		MotorF(motor21, Happy(CONTROLLER_A, JOYSTICK_L, AXIS_X));
	}
	else if (!Button(CONTROLLER_A, 5) && !Button(CONTROLLER_A, 6) && (Hat(CONTROLLER_A) == HAT_NONE)) {
		MotorS(motor11);
		MotorS(motor21);
	}

	if ((Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y) > 15) || (Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y) < -15)) {
		MotorF(motor12, Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y));
		MotorF(motor22, Happy(CONTROLLER_A, JOYSTICK_R, AXIS_Y));
	}
	else if (!Button(CONTROLLER_A, 5) && !Button(CONTROLLER_A, 6) && (Hat(CONTROLLER_A) == HAT_NONE)) {
		MotorS(motor12);
		MotorS(motor22);
	}

	if (Hat(CONTROLLER_A) == HAT_NE) {
		MotorF(motor12, 90);
		MotorF(motor22, 90);
		MotorF(motor11, 90);
		MotorF(motor21, 90);
	}
	else if (Hat(CONTROLLER_A) == HAT_NW) {
		MotorF(motor12, 90);
		MotorF(motor22, 90);
		MotorF(motor11, -90);
		MotorF(motor21, -90);
	}
	else if (Hat(CONTROLLER_A) == HAT_SW) {
		MotorF(motor12, -90);
		MotorF(motor22, -90);
		MotorF(motor11, -90);
		MotorF(motor21, -90);
	}
	else if (Hat(CONTROLLER_A) == HAT_SE) {
		MotorF(motor12, -90);
		MotorF(motor22, -90);
		MotorF(motor11, 90);
		MotorF(motor21, 90);
	}
}

void processArm() {
	if ((Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y) > 15) || (Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y) < -15)) {
		if(!touchMuxer1 && !touchMuxer2)
			MotorF(motorArm, Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y)*2);
		else if (!touchMuxer1 && (Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y)*2 < 0))
			MotorF(motorArm, Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y)*2);
		else if (!touchMuxer2 && (Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y)*2 > 0))
			MotorF(motorArm, Happy(CONTROLLER_B, JOYSTICK_R, AXIS_Y)*2);
		else if (!touchMuxer1 || !touchMuxer2)
			MotorS(motorArm);
	}
	else
		MotorS(motorArm);

	if (Button(CONTROLLER_B, 4))
		ArmUpDistance(0.075);
	else if (Button(CONTROLLER_B, 2))
		ArmDownDistance(0.075);
}

void processSensors() {
	touchMultiplexerUpdate();
}

task main() {
	initializeRobot();
	for (int i=0; ; i++) {
		//writeDebugStreamLine("Sensor: %d", SensorValue(lightSensor));
		CatsAndCorgis();
		processSensors();
		processWheels();
		processArm();
	}
}
