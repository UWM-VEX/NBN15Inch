/*
 * Intake.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Erik
 */

#include "main.h"

Intake initIntake(PantherMotor leftMotor, PantherMotor rightMotor,
		PantherMotor backMotor, int leftLimitSwitch,
		int rightLimitSwitch)
{
	pinMode(leftLimitSwitch, INPUT);
	pinMode(rightLimitSwitch, INPUT);

	Intake newIntake = {leftMotor, rightMotor, backMotor,
			leftLimitSwitch, rightLimitSwitch};
	return newIntake;
}

void intake1In(Intake intake)
{
	setPantherMotor(intake.leftMotor, 127);

	if(digitalRead(intake.leftLimitSwitch) && digitalRead(intake.rightLimitSwitch))
	{
		setPantherMotor(intake.rightMotor, 0);
	}
	else
	{
		setPantherMotor(intake.rightMotor, 0);
	}
}

void intake1Out(Intake intake)
{
	setPantherMotor(intake.leftMotor, -127);
	setPantherMotor(intake.rightMotor, -127);
}

void intake1Stop(Intake intake)
{
	setPantherMotor(intake.leftMotor, 0);
	setPantherMotor(intake.rightMotor, 0);
}

void intake2In(Intake intake)
{
	setPantherMotor(intake.backMotor, 127);
}

void intake2Out(Intake intake)
{
	setPantherMotor(intake.backMotor, -127);
}

void intake2Stop(Intake intake)
{
	setPantherMotor(intake.backMotor, 0);
}
