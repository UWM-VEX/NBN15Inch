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
PropDriveToWayPoint drivetobar;
PropDriveToWayPoint backoffbar;
PropDriveToWayPoint turntocenter;
PropDriveToWayPoint drivetocenter;
PropDriveToWayPoint turntogoal;
PropDriveToWayPoint drivetogoal;
PropDriveToWayPoint backoffgoal;
PropDriveToWayPoint turntopile1;
PropDriveToWayPoint drivetopile1;
//PropDriveToWayPoint backoffpile1;
PropDriveToWayPoint turntogoal1;
PropDriveToWayPoint drivetogoal1;
PropDriveToWayPoint backoffgoal2;
PropDriveToWayPoint turntopile2;
PropDriveToWayPoint drivetopile2;
PropDriveToWayPoint turntoalign2;
PropDriveToWayPoint drivetocenter2;
PropDriveToWayPoint turntogoal2;
PropDriveToWayPoint drivetogoal2;

PropDriveToWayPoint _2drivetobar;
PropDriveToWayPoint _2backoffbar;
PropDriveToWayPoint _2turntogoal;
PropDriveToWayPoint _2turntopile1;
PropDriveToWayPoint _2drivetopile1;
PropDriveToWayPoint _2turntogoal1;
PropDriveToWayPoint _2drivetogoal1;

PropDriveToWayPoint FSUdrive;
PropDriveToWayPoint FSUturn;
PropDriveToWayPoint FSUblock;


int isAuto = 1;

long int stepStartTime;

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
	if(alliance == BLUE)
	{
		drivetobar = initPropDriveToWayPoint(robotDrive, 119, 0);
		backoffbar = initPropDriveToWayPoint(robotDrive, -1.5, 0);
		turntocenter = initPropDriveToWayPoint(robotDrive, 0, 90);
		drivetocenter = initPropDriveToWayPoint(robotDrive, 16, 0);
		turntogoal = initPropDriveToWayPoint(robotDrive, 0, -90);
		drivetogoal = initPropDriveToWayPoint(robotDrive, 10, 0);
		backoffgoal = initPropDriveToWayPoint(robotDrive, -1.5, 0);
		turntopile1 = initPropDriveToWayPoint(robotDrive, 0, 180);
		drivetopile1 = initPropDriveToWayPoint(robotDrive, 32, 0);
		propDriveToWayPointSetMaxSpeed(&drivetopile1, 40);
		//backoffpile1 = initPropDriveToWayPoint(robotDrive, -10, 0);
		turntogoal1 = initPropDriveToWayPoint(robotDrive, 0, -180);
		drivetogoal1 = initPropDriveToWayPoint(robotDrive, 42, 0);
		backoffgoal2 = initPropDriveToWayPoint(robotDrive, -12, 0);
		turntopile2 = initPropDriveToWayPoint(robotDrive, 0, -90);
		drivetopile2 = initPropDriveToWayPoint(robotDrive, 24, 0);
		turntoalign2 = initPropDriveToWayPoint(robotDrive, 0, 180);
		drivetocenter2 = initPropDriveToWayPoint(robotDrive, 26, 0);
		turntogoal2 = initPropDriveToWayPoint(robotDrive, 0, -80);
		drivetogoal2 = initPropDriveToWayPoint(robotDrive, 13, 0);

		_2drivetobar = initPropDriveToWayPoint(robotDrive, 119, 0);
		_2backoffbar = initPropDriveToWayPoint(robotDrive, -1.5, 0);
		_2turntogoal = initPropDriveToWayPoint(robotDrive, 0, 10);
		_2turntopile1 = initPropDriveToWayPoint(robotDrive, 0, 180);
		_2drivetopile1 = initPropDriveToWayPoint(robotDrive, 34, 0);
		propDriveToWayPointSetMaxSpeed(&_2drivetopile1, 40);
		_2turntogoal1 = initPropDriveToWayPoint(robotDrive, 0, 180);
		_2drivetogoal1 = initPropDriveToWayPoint(robotDrive, 34, 0);

		FSUdrive = initPropDriveToWayPoint(robotDrive, 64, 0);
		FSUturn = initPropDriveToWayPoint(robotDrive, 0, -90);
		FSUblock = initPropDriveToWayPoint(robotDrive, 51, 0);
	}
	else
	{
		drivetobar = initPropDriveToWayPoint(robotDrive, 119, 0);
		backoffbar = initPropDriveToWayPoint(robotDrive, -1.5, 0);
		turntocenter = initPropDriveToWayPoint(robotDrive, 0, -90);
		drivetocenter = initPropDriveToWayPoint(robotDrive, 16, 0);
		turntogoal = initPropDriveToWayPoint(robotDrive, 0, 90);
		drivetogoal = initPropDriveToWayPoint(robotDrive, 10, 0);
		backoffgoal = initPropDriveToWayPoint(robotDrive, -1.5, 0);
		turntopile1 = initPropDriveToWayPoint(robotDrive, 0, -180);
		drivetopile1 = initPropDriveToWayPoint(robotDrive, 32, 0);
		propDriveToWayPointSetMaxSpeed(&drivetopile1, 40);
		//backoffpile1 = initPropDriveToWayPoint(robotDrive, -10, 0);
		turntogoal1 = initPropDriveToWayPoint(robotDrive, 0, 180);
		drivetogoal1 = initPropDriveToWayPoint(robotDrive, 42, 0);
		backoffgoal2 = initPropDriveToWayPoint(robotDrive, -12, 0);
		turntopile2 = initPropDriveToWayPoint(robotDrive, 0, 90);
		drivetopile2 = initPropDriveToWayPoint(robotDrive, 24, 0);
		turntoalign2 = initPropDriveToWayPoint(robotDrive, 0, -180);
		drivetocenter2 = initPropDriveToWayPoint(robotDrive, 26, 0);
		turntogoal2 = initPropDriveToWayPoint(robotDrive, 0, 80);
		drivetogoal2 = initPropDriveToWayPoint(robotDrive, 13, 0);

		_2drivetobar = initPropDriveToWayPoint(robotDrive, 119, 0);
		_2backoffbar = initPropDriveToWayPoint(robotDrive, -1.5, 0);
		_2turntogoal = initPropDriveToWayPoint(robotDrive, 0, -10);
		_2turntopile1 = initPropDriveToWayPoint(robotDrive, 0, -180);
		_2drivetopile1 = initPropDriveToWayPoint(robotDrive, 34, 0);
		propDriveToWayPointSetMaxSpeed(&_2drivetopile1, 40);
		_2turntogoal1 = initPropDriveToWayPoint(robotDrive, 0, -180);
		_2drivetogoal1 = initPropDriveToWayPoint(robotDrive, 34, 0);


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

	printf("Step: %d", autonomousInfo.step);

	switch(autonomousSelection)
	{
	case(MODE_1):
				switch(autonomousInfo.step)
				{
				case(1):

				propDriveToWayPoint(&drivetobar);

				ballStopperUp(&robotStopper);

				runBallStopper(&robotStopper);

				turnShooterOn(&robotShooter);

				runShooter(&robotShooter);

				//intake1In(&robotIntake);

				//runIntake(&robotIntake);

				//ballStopperUp(&robotStopper);

				//runBallStopper(&robotStopper);

				//turnShooterOn(&robotShooter);

				//runShooter(&robotShooter);

				//intake1Stop(&robotIntake);

				//lcdSetText(uart1, 2, "Step 1");

				autonomousInfo.isFinished = drivetobar.isFinished || autonomousInfo.elapsedTime > 8000;

				break;

				case(2):
					propDriveToWayPoint(&backoffbar);

					autonomousInfo.isFinished = backoffbar.isFinished;

					//lcdSetText(uart1, 2, "Step 2");

					break;

				case(3):
					propDriveToWayPoint(&turntocenter);

					autonomousInfo.isFinished = turntocenter.isFinished;

					//lcdSetText(uart1, 2, "Step 3");

					break;

				case(4):
				propDriveToWayPoint(&drivetocenter);

				autonomousInfo.isFinished = drivetocenter.isFinished;

				//lcdSetText(uart1, 2, "Step 4");

				break;

				case(5):
				propDriveToWayPoint(&turntogoal);

				autonomousInfo.isFinished = turntogoal.isFinished;

				//lcdSetText(uart1, 2, "Step 5");
				break;

				case(6):
				propDriveToWayPoint(&drivetogoal);

				autonomousInfo.isFinished = drivetogoal.isFinished;

				//lcdSetText(uart1, 2, "Step 6");
				break;

				case(7):
				runShooter(&robotShooter);

				intake1In(&robotIntake);

				intake2In(&robotIntake);

				runIntake(&robotIntake);

				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 5500;

				lcdSetText(uart1, 2, "Step 5");

				break;


				case(8):

				propDriveToWayPoint(&backoffgoal);

				autonomousInfo.isFinished = backoffgoal.isFinished;

				lcdSetText(uart1, 2, "Step 6");

				break;

				case(9):
					propDriveToWayPoint(&turntopile1);

					ballStopperDown(&robotStopper);

					runBallStopper(&robotStopper);

					autonomousInfo.isFinished = turntopile1.isFinished;

					lcdSetText(uart1, 2, "Step 7");

					break;

				case(10):
					propDriveToWayPoint(&drivetopile1);

					intake1Auto(&robotIntake);

					intake2In(&robotIntake);

					runIntake(&robotIntake);

					autonomousInfo.isFinished = drivetopile1.isFinished;

					lcdSetText(uart1, 2, "Step 8");

				break;

				/*case(9):
				propDriveToWayPoint(&backoffpile1);

				intake1Auto(&robotIntake);

				intake2In(&robotIntake);

				runIntake(&robotIntake);

				autonomousInfo.isFinished = backoffpile1.isFinished;

				lcdSetText(uart1, 2, "Step 9");

				break;

				*/

				case(11):

				propDriveToWayPoint(&turntogoal1);

				autonomousInfo.isFinished = turntogoal1.isFinished;

				lcdSetText(uart1, 2, "Step 10");

				break;

				case(12):

				propDriveToWayPoint(&drivetogoal1);

				intake1Stop(&robotIntake);

				intake2Stop(&robotIntake);

				runIntake(&robotIntake);

				autonomousInfo.isFinished = drivetogoal1.isFinished;

				lcdSetText(uart1, 2, "Step 11");

				break;

				case(13):

				ballStopperUp(&robotStopper);

				runBallStopper(&robotStopper);

				intake1Auto(&robotIntake);

				intake2In(&robotIntake);

				runIntake(&robotIntake);

				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 3000;

				lcdSetText(uart1, 2, "Step 2");

				break;

				case(14):
				propDriveToWayPoint(&backoffgoal2);

				ballStopperDown(&robotStopper);

				runBallStopper(&robotStopper);

				intake1Auto(&robotIntake);

				intake2In(&robotIntake);

				runIntake(&robotIntake);

				autonomousInfo.isFinished = backoffgoal2.isFinished;

				lcdSetText(uart1, 2, "Step 2");

				break;

				case(15):
				propDriveToWayPoint(&turntopile2);

				autonomousInfo.isFinished = turntopile2.isFinished;

				lcdSetText(uart1, 2, "Step 2");

				break;

				case(16):
				propDriveToWayPoint(&drivetopile2);

				autonomousInfo.isFinished = drivetopile2.isFinished;

				lcdSetText(uart1, 2, "Step 2");

				break;

				case(17):
				propDriveToWayPoint(&turntoalign2);

				autonomousInfo.isFinished = turntoalign2.isFinished;

				lcdSetText(uart1, 2, "Step 2");

				break;

				case(18):
				propDriveToWayPoint(&drivetocenter2);

				intake1Stop(&robotIntake);

				intake2Stop(&robotIntake);

				runIntake(&robotIntake);

				autonomousInfo.isFinished = drivetocenter2.isFinished;

				lcdSetText(uart1, 2, "Step 2");

				break;

				case(19):
				propDriveToWayPoint(&turntogoal2);

				autonomousInfo.isFinished = turntogoal2.isFinished;

				lcdSetText(uart1, 2, "Step 2");

				break;

				case(20):
				propDriveToWayPoint(&drivetogoal2);

				ballStopperUp(&robotStopper);

				runBallStopper(&robotStopper);

				autonomousInfo.isFinished = drivetogoal2.isFinished;

				lcdSetText(uart1, 2, "Step 2");

				break;

				case(21):
				runShooter(&robotShooter);

				intake1Auto(&robotIntake);

				intake2In(&robotIntake);

				runIntake(&robotIntake);

				autonomousInfo.isFinished = autonomousInfo.elapsedTime > 6000;

				lcdSetText(uart1, 2, "Step 5");

				break;


				default:
					isAuto = 0;
					break;

				}
	break;

	case(MODE_2):
			switch(autonomousInfo.step)
			{
			case(1):
			propDriveToWayPoint(&_2drivetobar);

			ballStopperUp(&robotStopper);

			runBallStopper(&robotStopper);

			turnShooterOn(&robotShooter);

			runShooter(&robotShooter);

			autonomousInfo.isFinished = _2drivetobar.isFinished;

			lcdSetText(uart1, 2, "Step 1");
			break;

			case(2):
			propDriveToWayPoint(&_2backoffbar);

			autonomousInfo.isFinished = _2backoffbar.isFinished;

			lcdSetText(uart1, 2, "Step 2");
			break;

			case(3):
			propDriveToWayPoint(&_2turntogoal);

			autonomousInfo.isFinished = _2turntogoal.isFinished;

			lcdSetText(uart1, 2, "Step 2");
			break;

			case(4):
			runShooter(&robotShooter);

			intake1In(&robotIntake);

			intake2In(&robotIntake);

			runIntake(&robotIntake);

			autonomousInfo.isFinished = autonomousInfo.elapsedTime > 5500;

			lcdSetText(uart1, 2, "Step 5");

			break;

			case(5):
			propDriveToWayPoint(&_2turntopile1);

			ballStopperDown(&robotStopper);

			runBallStopper(&robotStopper);

			autonomousInfo.isFinished = _2turntopile1.isFinished;

			lcdSetText(uart1, 2, "Step 2");
			break;

			case(6):
			propDriveToWayPoint(&_2drivetopile1);

			intake1Auto(&robotIntake);

			intake2In(&robotIntake);

			runIntake(&robotIntake);

			autonomousInfo.isFinished = _2drivetopile1.isFinished;

			lcdSetText(uart1, 2, "Step 2");
			break;

			case(7):
			propDriveToWayPoint(&_2turntogoal1);

			intake1Stop(&robotIntake);

			intake2Stop(&robotIntake);

			runIntake(&robotIntake);

			autonomousInfo.isFinished = _2turntogoal1.isFinished;

			lcdSetText(uart1, 2, "Step 2");
			break;

			case(8):
			propDriveToWayPoint(&_2drivetogoal1);

			ballStopperUp(&robotStopper);

			runBallStopper(&robotStopper);

			autonomousInfo.isFinished = _2drivetogoal1.isFinished;

			lcdSetText(uart1, 2, "Step 2");
			break;

			case(9):
			runShooter(&robotShooter);

			intake1In(&robotIntake);

			intake2In(&robotIntake);

			runIntake(&robotIntake);

			autonomousInfo.isFinished = autonomousInfo.elapsedTime > 10000;

			lcdSetText(uart1, 2, "Step 5");

			break;

			default:
				isAuto = 0;
			}
	break;

	case(FSU):
	switch(autonomousInfo.step)
	{
	case(1):
	propDriveToWayPoint(&FSUdrive);

	autonomousInfo.isFinished = FSUdrive.isFinished;

	lcdSetText(uart1, 2, "Step 1");
	break;

	case(2):
		propDriveToWayPoint(&FSUturn);

		autonomousInfo.isFinished = FSUturn.isFinished;

		lcdSetText(uart1, 2, "Step 2");
		break;

	case(3):
		propDriveToWayPoint(&FSUblock);

		autonomousInfo.isFinished = FSUblock.isFinished;

		lcdSetText(uart1, 2, "Step 3");
		break;

	default:
		isAuto = 0;
	}
	break;

	case(DO_NOTHING):
			isAuto = 0;
			break;

	}


	autonomousInfo.lastStep = autonomousInfo.step;

	if(autonomousInfo.isFinished)
	{
		autonomousInfo.step ++;
		autonomousInfo.isFinished = 0;
	}

}

void autonomous()
{
	autonomousInit();

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
