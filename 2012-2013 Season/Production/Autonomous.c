#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     GYRO,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S3,     touchMuxer,     sensorHiTechnicTouchMux)
#pragma config(Sensor, S4,     IRseeker,       sensorHiTechnicIRSeeker1200)
#pragma config(Motor,  mtr_S1_C1_1,     motor12,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motor11,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motor21,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motor22,       tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorArm,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorLED,      tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma DebuggerWindows("debugStream")

#include "JoystickDriver.c"
#include "../Headers/CSEnumerated.h"
#include "../Headers/CSMethods.h"
#include "../Headers/CSTasks.h"
//#include "../Drivers/HTGYRO-driver.h"

void initializeRobot() {
	return;
}

task main() {
  initializeRobot();
  //waitForStart();

  //StartTask(getHeading);
	//wait10Msec(200);

	motorForDistance(autonomousWheelPower, 6);
	wait10Msec(autonomous10Mdelay);
	ArmUpDistance(7.2);
	irDecision = SensorValue(IRseeker);
	writeDebugStreamLine("irDecision: %d", irDecision);
	if ((irDecision == 3) || (irDecision == 4)) {
		MotorF(motorLED, 90);
		wait10Msec(50);
		MotorS(motorLED);
	}
	else if ((irDecision == 6) || (irDecision == 7)) {
		MotorR(motorLED, 90);
		wait10Msec(50);
		MotorS(motorLED);
	}
	if ((irDecision == 5) || (irDecision == 0)) {
	motorForDistance(-autonomousWheelPower, 1);
	wait10Msec(autonomous10Mdelay);
		encodedTurn(autonomousWheelPower, 0.11);
		wait10Msec(autonomous10Mdelay);
		motorStrafeForDistance(-autonomousWheelPower, 4.2);
		wait10Msec(autonomous10Mdelay);
		motorForDistance(autonomousWheelPower, 0.1);
		wait10Msec(autonomous10Mdelay);
		encodedDiagonal(autonomousWheelPower, 4.65);
		wait10Msec(autonomous10Mdelay);
		//motorStrafeForDistance(-autonomousWheelPower, 0.05);
		//wait10Msec(autonomous10Mdelay*5);
		while (SensorValue(IRseeker) != irMiddleTarget) {
			writeDebugStreamLine("Sensor: %d", SensorValue(IRseeker));
			if (SensorValue(IRseeker) == 0) {
				if (irStrafeCount % 2 == 1) {
					motorStrafeForDistance(-autonomousWheelPower, 0.2*irStrafeCount);
					irStrafeCount++;
					wait10Msec(irSeekingDelay);
				}
				else if (irStrafeCount % 2 == 0) {
					//motorStrafeForDistance(autonomousWheelPower, 0.2*irStrafeCount);
					irStrafeCount++;
					wait10Msec(irSeekingDelay);
				}
				else
					wait10Msec(irSeekingDelay);
			}
			else if (SensorValue(IRseeker) < irMiddleTarget) {
				motorStrafeForDistance(-autonomousWheelPower, 0.2);
				irLeftRightCount--;
				wait10Msec(irSeekingDelay);
			}
			else if (SensorValue(IRseeker) > irMiddleTarget) {
				motorStrafeForDistance(autonomousWheelPower, 0.2);
				irLeftRightCount++;
				wait10Msec(irSeekingDelay);
			}
			else if (SensorValue(IRseeker) == irMiddleTarget) {
				break;
			}
		}
		//motorStrafeForDistance(-autonomousWheelPower, 0.2);
	  //wait10Msec(autonomous10Mdelay);
	  ArmUp();
	  wait10Msec(autonomous10Mdelay);
	  motorForDistance(autonomousWheelPower,1.25);
	  wait10Msec(autonomous10Mdelay*10);
	  ArmDownDistance(2);
	  wait10Msec(autonomous10Mdelay);
	  motorForDistance(-autonomousWheelPower,3);
	  wait10Msec(autonomous10Mdelay);
	  ArmDown();
	}
	else if ((irDecision == 3) || (irDecision == 4)) {
		motorForDistance(-autonomousWheelPower, 0.5);
		wait10Msec(autonomous10Mdelay);
		motorStrafeForDistance(-autonomousWheelPower, 4.05);
	  wait10Msec(autonomous10Mdelay);
		motorForDistance(autonomousWheelPower, 3.25);
	  wait10Msec(autonomous10Mdelay*5);
		//gyroCompensate();
	  //wait10Msec(autonomous10Mdelay*5);
		motorStrafeForDistance(autonomousWheelPower, 2);
	  wait10Msec(autonomous10Mdelay);
		while (SensorValue(IRseeker) != irTarget) {
			writeDebugStreamLine("Sensor: %d", SensorValue(IRseeker));
			if (SensorValue(IRseeker) == 0) {
				if (irStrafeCount % 2 == 1) {
					motorStrafeForDistance(-autonomousWheelPower, 0.2*irStrafeCount);
					irStrafeCount++;
					wait10Msec(irSeekingDelay);
				}
				else if (irStrafeCount % 2 == 0) {
					//motorStrafeForDistance(autonomousWheelPower, 0.2*irStrafeCount);
					irStrafeCount++;
					wait10Msec(irSeekingDelay);
				}
				else
					wait10Msec(irSeekingDelay);
			}
			else if (SensorValue(IRseeker) < irTarget) {
				motorStrafeForDistance(-autonomousWheelPower, 0.2);
				irLeftRightCount--;
				wait10Msec(irSeekingDelay);
			}
			else if (SensorValue(IRseeker) > irTarget) {
				motorStrafeForDistance(autonomousWheelPower, 0.2);
				irLeftRightCount++;
				wait10Msec(irSeekingDelay);
			}
			else if (SensorValue(IRseeker) == irTarget) {
				break;
			}
		}
	  ArmUp();
	  wait10Msec(autonomous10Mdelay);
	  motorForDistance(autonomousWheelPower, 2);
	  wait10Msec(autonomous10Mdelay*10);
	  ArmDownDistance(2);
	  wait10Msec(autonomous10Mdelay);
	  motorForDistance(-autonomousWheelPower, 3);
	  wait10Msec(autonomous10Mdelay);
	  ArmDown();
	}
	else if ((irDecision == 6) || (irDecision == 7)) {
		motorForDistance(-autonomousWheelPower, 1);
		wait10Msec(autonomous10Mdelay);
		encodedTurn(autonomousWheelPower, 0.11);
		wait10Msec(autonomous10Mdelay);
		motorStrafeForDistance(-autonomousWheelPower, 4.2);
		wait10Msec(autonomous10Mdelay);
		motorForDistance(autonomousWheelPower, 0.1);
		wait10Msec(autonomous10Mdelay);
		encodedDiagonal(autonomousWheelPower, 4.65);
		wait10Msec(autonomous10Mdelay);
		motorStrafeForDistance(-autonomousWheelPower, 0.05);
		wait10Msec(autonomous10Mdelay*5);
		while (SensorValue(IRseeker) != irTarget) {
			writeDebugStreamLine("Sensor: %d", SensorValue(IRseeker));
			if (SensorValue(IRseeker) == 0) {
				if (irStrafeCount % 2 == 1) {
					motorStrafeForDistance(autonomousWheelPower, 0.2*irStrafeCount);
					irStrafeCount++;
					wait10Msec(irSeekingDelay);
				}
				else if (irStrafeCount % 2 == 0) {
					//motorStrafeForDistance(autonomousWheelPower, 0.2*irStrafeCount);
					irStrafeCount++;
					wait10Msec(irSeekingDelay);
				}
				else
					wait10Msec(irSeekingDelay);
			}
			else if (SensorValue(IRseeker) < irTarget) {
				motorStrafeForDistance(-autonomousWheelPower, 0.2);
				irLeftRightCount--;
				wait10Msec(irSeekingDelay);
			}
			else if (SensorValue(IRseeker) > irTarget) {
				motorStrafeForDistance(autonomousWheelPower, 0.2);
				irLeftRightCount++;
				wait10Msec(irSeekingDelay);
			}
			else if (SensorValue(IRseeker) == irTarget) {
				break;
			}
		}
		//ewait10Msec(autonomous10Mdelay*3);
		//gyroCompensate();
		wait10Msec(autonomous10Mdelay);
	  ArmUp();
	  wait10Msec(autonomous10Mdelay);
	  motorForDistance(autonomousWheelPower, 2.75);
	  wait10Msec(autonomous10Mdelay*10);
	  ArmDownDistance(2);
	  wait10Msec(autonomous10Mdelay);
	  motorForDistance(-autonomousWheelPower, 3);
	  wait10Msec(autonomous10Mdelay);
	  ArmDown();
	}
}
