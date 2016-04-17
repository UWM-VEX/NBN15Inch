/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

/**
 * This is where you declare all of the actions the robot will take.
 * The options are DriveForTime which is useful for driving into something
 * but shouldn't be used elsewhere, DriveToWayPoint, which will handle
 * driving forward and back, strafing, and turning (turning must be in
 * its own step) and AutoLiftToHeight which will bring the lift to a
 * specified height (Note: Once the step where this function is used has
 * completed, the lift will move down due to gravity. To avoid this,
 * create a new AutoLiftToHeight function to keep the lift at the desired
 * height. Also, the lift to height code isn't perfectly tuned yet,
 * if the autonomous stalls with the autoLiftToHeight function, help the
 * lift up.)
 *
 * Running the pickup or spinner does not require an object to be declared
 * or instantiated, an example is shown below.
 */

int isAuto = 1;

long int stepStartTime;

DriveToWP worlds1TurnToBump;
DriveToWP worlds1DriveToBump;
DriveToWP worlds1TurnToFirstPile;
DriveToWP worlds1DriveToFirstPile;
DriveToWP worlds1TurnToShoot1;
DriveToWP worlds1DriveToShoot1;
DriveToWP worlds1TurnToSecondPile;
DriveToWP worlds1DriveToSecondPile;
DriveToWP worlds1SlowToSecondPile;
DriveToWP worlds1TurnToShoot2;
DriveToWP worlds1DriveToShoot2;
DriveToWP worlds1BackToThirdPile;
DriveToWP worlds1TurnToThirdPile;
DriveToWP worlds1DriveToThirdPile;
DriveToWP worlds1BackToShoot;
DriveToWP worlds1TurnToShoot3;
DriveToWP worlds1DriveToShoot3;

DriveToWP worlds2TurnToBump;
DriveToWP worlds2DriveToBump;
DriveToWP worlds2TurnToFirstPile;
DriveToWP worlds2DriveToFirstPile;
DriveToWP worlds2TurnToShoot1;
DriveToWP worlds2DriveToShoot1;
DriveToWP worlds2BackToPile2;
DriveToWP worlds2TurnToPile2;
DriveToWP worlds2DriveToPile2;
DriveToWP worlds2BackToShoot2;
DriveToWP worlds2TurnToShoot2;
DriveToWP worlds2DriveToShoot2;
DriveToWP worlds2TurnToPile3;
DriveToWP worlds2DriveToPile3;
DriveToWP worlds2SlowToPile3;
DriveToWP worlds2TurnToShoot3;
DriveToWP worlds2DriveToShoot3;


/**
 * Runs at the start of autonomous. Steps should be initialized here.
 */
void autonomousInit()
{
	/**
	 * Here, the different steps are instantiated and details are
	 * given about them. By hovering over the function name, you can see a
	 * list of the arguments to pass in.
	 */

	if(autonomousSelection == WORLDS_1)
	{
		worlds1TurnToBump = initDriveToWP(robotDrive, 0, -50);
		worlds1DriveToBump = initDriveToWP(robotDrive, 6*12, 0);
		worlds1TurnToFirstPile = initDriveToWP(robotDrive, 0, -18);
		worlds1DriveToFirstPile = initDriveToWP(robotDrive, 24, 0);
			driveToWPSetMaxSpeed(&worlds1DriveToFirstPile, 40);
		worlds1TurnToShoot1 = initDriveToWP(robotDrive, 0, 51);
		worlds1DriveToShoot1 = initDriveToWP(robotDrive, 22, 0);
		worlds1TurnToSecondPile = initDriveToWP(robotDrive, 0, 97);
		worlds1DriveToSecondPile = initDriveToWP(robotDrive, 10, 0);
		worlds1SlowToSecondPile = initDriveToWP(robotDrive, 26, 0);
			driveToWPSetMaxSpeed(&worlds1SlowToSecondPile, 35);
		worlds1TurnToShoot2 = initDriveToWP(robotDrive, 0, -137);
		worlds1DriveToShoot2 = initDriveToWP(robotDrive, 10, 0);
		worlds1BackToThirdPile = initDriveToWP(robotDrive, -32, 0);
		worlds1TurnToThirdPile = initDriveToWP(robotDrive, 0, 52);
		worlds1DriveToThirdPile = initDriveToWP(robotDrive, 45, 0);
		worlds1BackToShoot = initDriveToWP(robotDrive, -36, 0);
		worlds1TurnToShoot3 = initDriveToWP(robotDrive, 0, -58);
		worlds1DriveToShoot3 = initDriveToWP(robotDrive, 28, 0);


	}
	else if(autonomousSelection == WORLDS_2)
	{
		worlds2TurnToBump = initDriveToWP(robotDrive, 0, -50);
		worlds2DriveToBump = initDriveToWP(robotDrive, 6*12, 0);
		worlds2TurnToFirstPile = initDriveToWP(robotDrive, 0, -18);
		worlds2DriveToFirstPile = initDriveToWP(robotDrive, 24, 0);
			driveToWPSetMaxSpeed(&worlds2DriveToFirstPile, 40);
		worlds2TurnToShoot1 = initDriveToWP(robotDrive, 0, 51);
		worlds2DriveToShoot1 = initDriveToWP(robotDrive, 22, 0);
		worlds2BackToPile2 = initDriveToWP(robotDrive, -27, 0);
		worlds2TurnToPile2 = initDriveToWP(robotDrive, 0, -65);
		worlds2DriveToPile2 = initDriveToWP(robotDrive, 17.5, 0);
			driveToWPSetMaxSpeed(&worlds2DriveToPile2, 50);
		worlds2BackToShoot2 = initDriveToWP(robotDrive, -18, 0);
		worlds2TurnToShoot2 = initDriveToWP(robotDrive, 0, 60);
		worlds2DriveToShoot2 = initDriveToWP(robotDrive, 27, 0);
		worlds2TurnToPile3 = initDriveToWP(robotDrive, 0, 97);
		worlds2DriveToPile3 = initDriveToWP(robotDrive, 10, 0);
		worlds2SlowToPile3 = initDriveToWP(robotDrive, 26, 0);
			driveToWPSetMaxSpeed(&worlds2SlowToPile3, 35);
		worlds2TurnToShoot3 = initDriveToWP(robotDrive, 0, -137);
		worlds2DriveToShoot3 = initDriveToWP(robotDrive, 14, 0);





	}
	autonomousInfo.lastStep = 0;
	autonomousInfo.step = 1;
	autonomousInfo.isFinished = 0;

	stepStartTime = millis();
}

/**
 * Runs continuously during autonomous, should exit relatively promptly.
 */
void autonomousPeriodic()
{
	if(autonomousInfo.step != autonomousInfo.lastStep)
	{
		stepStartTime = millis();
	}

	autonomousInfo.elapsedTime = millis() - stepStartTime;

	lcdPrint(uart1, 1, "Step: %d", autonomousInfo.step);

	switch(autonomousSelection)
	{
		case(WORLDS_1):
			switch(autonomousInfo.step)
			{
			case(1):
				driveToWP(&worlds1TurnToBump);
				turnShooterOn(&robotShooter);
				shootFender(&robotShooter);
				ballStopperDown(&robotStopper);

				autonomousInfo.isFinished = worlds1TurnToBump.isFinished;
				break;
			case(2):
				driveToWP(&worlds1DriveToBump);
				autonomousInfo.isFinished = worlds1DriveToBump.isFinished;
				break;
			case(3):
				driveToWP(&worlds1TurnToFirstPile);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished = worlds1TurnToFirstPile.isFinished;
				break;
			case(4):
				driveToWP(&worlds1DriveToFirstPile);
				autonomousInfo.isFinished = worlds1DriveToFirstPile.isFinished;
				break;
			case(5):
				driveToWP(&worlds1TurnToShoot1);
				autonomousInfo.isFinished = worlds1TurnToShoot1.isFinished;
				break;
			case(6):
				driveToWP(&worlds1DriveToShoot1);
				intake1Stop(&robotIntake);
				intake2Stop(&robotIntake);
				autonomousInfo.isFinished = worlds1DriveToShoot1.isFinished;
				break;
			case(7):
				ballStopperUp(&robotStopper);
				intake1In(&robotIntake);
				intake2In(&robotIntake);
				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 4000;
				break;



			case(8):
				driveToWP(&worlds1TurnToSecondPile);
				ballStopperDown(&robotStopper);
				autonomousInfo.isFinished = worlds1TurnToSecondPile.isFinished;
				break;
			case(9):
			driveToWP(&worlds1DriveToSecondPile);
			autonomousInfo.isFinished = worlds1DriveToSecondPile.isFinished;
			break;

			case(10):
			driveToWP(&worlds1SlowToSecondPile);
			autonomousInfo.isFinished = worlds1SlowToSecondPile.isFinished;
			break;

			case(11):
			driveToWP(&worlds1TurnToShoot2);
			autonomousInfo.isFinished = worlds1TurnToShoot2.isFinished;
			break;

			case(12):
			driveToWP(&worlds1DriveToShoot2);
			autonomousInfo.isFinished = worlds1DriveToShoot2.isFinished;
			break;

			case(13):
			ballStopperUp(&robotStopper);
			autonomousInfo.isFinished = autonomousInfo.elapsedTime > 3500;
			break;

			case(14):
			driveToWP(&worlds1BackToThirdPile);
			ballStopperDown(&robotStopper);
			autonomousInfo.isFinished = worlds1BackToThirdPile.isFinished;
			break;

			case(15):
			driveToWP(&worlds1TurnToThirdPile);
			autonomousInfo.isFinished = worlds1TurnToThirdPile.isFinished;
			break;

			case(16):
			driveToWP(&worlds1DriveToThirdPile);
			autonomousInfo.isFinished = worlds1DriveToThirdPile.isFinished && autonomousInfo.elapsedTime > 4000;
			break;

			case(17):
			driveToWP(&worlds1BackToShoot);
			autonomousInfo.isFinished = worlds1BackToShoot.isFinished;
			break;

			case(18):
			driveToWP(&worlds1TurnToShoot3);
			autonomousInfo.isFinished = worlds1TurnToShoot3.isFinished;
			break;

			case(19):
			driveToWP(&worlds1DriveToShoot3);
			autonomousInfo.isFinished = worlds1DriveToShoot3.isFinished;
			break;

			case(20):
			ballStopperUp(&robotStopper);
			intake1In(&robotIntake);
			intake2In(&robotIntake);
			autonomousInfo.isFinished = autonomousInfo.elapsedTime > 4000;
			break;

			default:
				isAuto = 0;
				break;
			}

		break;

		case(WORLDS_2):
			switch(autonomousInfo.step)
			{
			case(1):
					driveToWP(&worlds2TurnToBump);
					turnShooterOn(&robotShooter);
					shootFender(&robotShooter);
					ballStopperDown(&robotStopper);

					autonomousInfo.isFinished = worlds2TurnToBump.isFinished;
					break;
				case(2):
					driveToWP(&worlds2DriveToBump);
					autonomousInfo.isFinished = worlds2DriveToBump.isFinished;
					break;
				case(3):
					driveToWP(&worlds2TurnToFirstPile);
					intake1In(&robotIntake);
					intake2In(&robotIntake);
					autonomousInfo.isFinished = worlds2TurnToFirstPile.isFinished;
					break;
				case(4):
					driveToWP(&worlds2DriveToFirstPile);
					autonomousInfo.isFinished = worlds2DriveToFirstPile.isFinished;
					break;
				case(5):
					driveToWP(&worlds2TurnToShoot1);
					autonomousInfo.isFinished = worlds2TurnToShoot1.isFinished;
					break;
				case(6):
					driveToWP(&worlds2DriveToShoot1);
					intake1Stop(&robotIntake);
					intake2Stop(&robotIntake);
					autonomousInfo.isFinished = worlds2DriveToShoot1.isFinished;
					break;
				case(7):
					ballStopperUp(&robotStopper);
					intake1In(&robotIntake);
					intake2In(&robotIntake);
					autonomousInfo.isFinished = autonomousInfo.elapsedTime > 3500;
					break;
				case(8):
					driveToWP(&worlds2BackToPile2);
					ballStopperDown(&robotStopper);
					autonomousInfo.isFinished = worlds2BackToPile2.isFinished;
					break;
				case(9):
					driveToWP(&worlds2TurnToPile2);
					autonomousInfo.isFinished = worlds2TurnToPile2.isFinished;
					break;
				case(10):
					driveToWP(&worlds2DriveToPile2);
					autonomousInfo.isFinished = worlds2DriveToPile2.isFinished || autonomousInfo.elapsedTime > 4000;
					break;
				case(11):
					driveToWP(&worlds2BackToShoot2);
					autonomousInfo.isFinished = worlds2BackToShoot2.isFinished;
					break;
				case(12):
					driveToWP(&worlds2TurnToShoot2);
					autonomousInfo.isFinished = worlds2TurnToShoot2.isFinished;
					break;
				case(13):
					driveToWP(&worlds2DriveToShoot2);
					autonomousInfo.isFinished = worlds2DriveToShoot2.isFinished;
					break;
				case(14):
					ballStopperUp(&robotStopper);
					intake1In(&robotIntake);
					intake2In(&robotIntake);
					autonomousInfo.isFinished = autonomousInfo.elapsedTime > 3500;
					break;
				case(15):
					driveToWP(&worlds2TurnToPile3);
					ballStopperDown(&robotStopper);
					autonomousInfo.isFinished = worlds2TurnToPile3.isFinished;
					break;
				case(16):
					driveToWP(&worlds2DriveToPile3);
					autonomousInfo.isFinished = worlds2DriveToPile3.isFinished;
					break;

				case(17):
					driveToWP(&worlds2SlowToPile3);
					autonomousInfo.isFinished = worlds2SlowToPile3.isFinished;
				break;

				case(18):
					driveToWP(&worlds2TurnToShoot3);
					autonomousInfo.isFinished = worlds2TurnToShoot3.isFinished;
				break;

				case(19):
					driveToWP(&worlds2DriveToShoot3);
					autonomousInfo.isFinished = worlds2DriveToShoot3.isFinished;
				break;

				case(20):
					ballStopperUp(&robotStopper);
					autonomousInfo.isFinished = autonomousInfo.elapsedTime > 3500;
				break;


			default:
				isAuto = 0;
			}
		break;



		case(DO_NOTHING):
			isAuto = 0;
		break;
				default:
					isAuto = 0;
					break;

				break;



	}

	runShooter(&robotShooter);
	runBallStopper(&robotStopper);
	runIntake(&robotIntake);

	autonomousInfo.lastStep = autonomousInfo.step;

	//lcdPrint(uart1, 1, "Step: %d", autonomousInfo.step);

	if(autonomousInfo.isFinished)
	{
		autonomousInfo.step ++;
		autonomousInfo.isFinished = 0;
	}

}

void autonomous()
{
	lcdSetText(uart1, 1, "started");

	autonomousInit();

	//lcdSetText(uart1, 1, "initialized");

	while(isAuto)
	{
		autonomousPeriodic();

		if(isOnline())
		{
			if(!isAutonomous() || !isEnabled()) isAuto = 0;
		}

		delay(20);

		puts("Autonomous");
	}
}
