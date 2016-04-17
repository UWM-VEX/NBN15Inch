/*
 * OI.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Erik
 */

#include "main.h"

int OIGetDriveLeft()
{
	return joystickGetAnalog(1, 3);
}

int OIGetDriveRight()
{
	return joystickGetAnalog(1, 2);
}

int OIGetIntake1In()
{
	return joystickGetDigital(2, 8, JOY_DOWN);

}

int OIGetIntake1Out()
{
	return joystickGetDigital(2, 8, JOY_UP);
}

int OIGetIntake2In()
{
	return joystickGetDigital(2, 7, JOY_DOWN);
}

int OIGetIntake2Out()
{
	return joystickGetDigital(2, 7, JOY_UP);
}

int OIGetIntakeMacroTrigger()
{
	return joystickGetDigital(2, 8, JOY_RIGHT);
}

int OIShooterOn()
{
	return joystickGetDigital(2, 6, JOY_DOWN);
}

int OIShooterOff()
{
	return joystickGetDigital(2, 5, JOY_DOWN);
}

int OIShooterUp()
{
	return joystickGetDigital(2, 6, JOY_UP);
}

int OIShooterDown()
{
	return joystickGetDigital(2, 5, JOY_UP);
}

int OIBallStopperUp()
{
	return joystickGetAnalog(2, 1) > 25;
}

int OIBallStopperDown()
{
	return joystickGetAnalog(2, 1) < -25;
}

int OIFireAtWill()
{
	return joystickGetAnalog(2, 3) > 25
		|| joystickGetDigital(1, 5, JOY_UP);
}

int OISpitAtWill()
{
	return joystickGetAnalog(2, 3) < -25
		|| joystickGetDigital(1, 5, JOY_DOWN);
}

int OIFenderShoot()
{
	return joystickGetDigital(2, 7, JOY_RIGHT);
}

int OIHalfCourtShoot()
{
	return joystickGetDigital(2, 7, JOY_LEFT);
}

int OIReduceDrive()
{
	return joystickGetDigital(1,6,JOY_DOWN);
}

int OIDriveStraightBack()
{
	return joystickGetDigital(1, 8, JOY_DOWN);
}
