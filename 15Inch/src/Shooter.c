/*
 * Shooter.c
 *
 *  Created on: Feb 7, 2016
 *      Author: Erik
 */

#include "main.h"

Shooter initShooter(PIDController controller, PantherMotor motor, int fenderSpeed,
		int halfCourtSpeed, RedEncoder encoder)
{
	PIDController newController = controller;

	newController.setPoint = 0;

	Shooter newShooter = {motor, 1, fenderSpeed, 0, millis(), newController,
			0, millis(), encoder, fenderSpeed, SHOOTER_FENDER, fenderSpeed,
			halfCourtSpeed};
	return newShooter;
}

void turnShooterOn(Shooter *shooter)
{
	(*shooter).turnedOn = 1;
	(*shooter).SP = (*shooter).speedWhenOn;
	puts("Shooter turned on.");
}

void turnShooterOff(Shooter *shooter)
{
	(*shooter).turnedOn = 0;
	(*shooter).lastChangeTime = millis();
}

void changeShooterSP(Shooter *shooter, int SP)
{
	switch((*shooter).shooterMode)
		{
		case(SHOOTER_HALF_COURT):
				(*shooter).halfCourtSpeed = SP;
				break;

		case(SHOOTER_FENDER): default:
				(*shooter).fenderSpeed = SP;
				break;
		}
}

void incrementShooterSP(Shooter *shooter, int amount)
{
	(*shooter).speedWhenOn += amount;

	switch((*shooter).shooterMode)
	{
	case(SHOOTER_HALF_COURT):
			(*shooter).halfCourtSpeed += amount;
			break;

	case(SHOOTER_FENDER): default:
			(*shooter).fenderSpeed += amount;
			break;
	}
}

void runShooter(Shooter *shooter)
{
	updateShooter(shooter);

	int speed;

	switch((*shooter).shooterMode)
	{
	case(SHOOTER_HALF_COURT):
		(*shooter).SP = (*shooter).halfCourtSpeed;
		break;

	case(SHOOTER_FENDER): default:
		(*shooter).SP = (*shooter).fenderSpeed;
		break;
	}

	if((*shooter).turnedOn)
	{
		(*shooter).SP = (*shooter).speedWhenOn;
		speed = (*shooter).SP;

		(*shooter).lastSpeed = (*shooter).SP;
	}
	else
	{
		int dT = (int) (millis() - (*shooter).lastChangeTime);

		if(dT > 50)
		{
			speed = (*shooter).lastSpeed - 10;
			(*shooter).lastSpeed = speed;
			(*shooter).lastChangeTime = millis();
		}
		else
		{
			speed = (*shooter).lastSpeed;
		}

		speed = limit(speed, 500, 0);
	}

	(*shooter).SP = speed;

	runShooterAtSpeed(shooter);
}

void shooterSetKP(Shooter *shooter, double kP)
{
	PIDsetkP(&((*shooter).controller), kP);
}

void shooterSetKI(Shooter *shooter, double kI)
{
	PIDsetkI(&((*shooter).controller), kI);
}

void shooterSetKD(Shooter *shooter, double kD)
{
	PIDsetkD(&((*shooter).controller), kD);
}

void shooterSetKF(Shooter *shooter, double kF)
{
	PIDsetkF(&((*shooter).controller), kF);
}

void shooterSetErrorEpsilon(Shooter *shooter, int errorEpsilon)
{
	PIDsetErrorEpsilon(&((*shooter).controller), errorEpsilon);
}

void updateShooter(Shooter *shooter)
{
	(*shooter).processVariable = (int) getRedEncoderVelocity((*shooter).encoder);

	//lcdPrint(uart1, 2, "Speed: %d", (*shooter).processVariable);
	lcdPrint(uart1, 1, "SP: %d", (*shooter).SP);

	lcdPrint(uart1, 2, "Error: %d", (*shooter).controller.setPoint - (*shooter).processVariable);

	if(abs((int) (*shooter).controller.setPoint - (*shooter).processVariable) > 1)
	{
		(*shooter).lastOffTime = millis();
	}

	lcdSetBacklight(uart1, isShooterUpToSpeed(shooter));
}

int isShooterUpToSpeed(Shooter *shooter)
{
	return (((millis() - (*shooter).lastOffTime)) > 100);
}

void runShooterAtSpeed(Shooter *shooter)
{
	int speed;

	if((*shooter).turnedOn && (*shooter).processVariable == 0)
	{
		//Open loop fall back if the encoder is not working correctly
		speed = (*shooter).SP * shooter->controller.kF;
	}
	else
	{
		(*shooter).controller.setPoint = (*shooter).SP;
		speed = PIDRunController(&((*shooter).controller),
				(*shooter).processVariable);
	}

	speed = limit(speed, 127, 0);

	setPantherMotor((*shooter).motor, speed);
}

void shootFender(Shooter *shooter)
{
	changeShooterMode(shooter, SHOOTER_FENDER);
}

void shootHalfCourt(Shooter *shooter)
{
	changeShooterMode(shooter, SHOOTER_HALF_COURT);
}

void changeShooterMode(Shooter *shooter, int shooterMode)
{
	(*shooter).shooterMode = shooterMode;

	switch(shooterMode)
	{
	case(SHOOTER_HALF_COURT):
		(*shooter).speedWhenOn = (*shooter).halfCourtSpeed;
		break;

	case(SHOOTER_FENDER):
		(*shooter).speedWhenOn = (*shooter).fenderSpeed;
		break;
	}

	if((*shooter).turnedOn == 1)
		turnShooterOn(shooter);
}
