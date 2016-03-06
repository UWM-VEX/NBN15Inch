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
			leftLimitSwitch, rightLimitSwitch, INTAKE_OFF, INTAKE_OFF, millis(), INTAKE_OFF};
	return newIntake;
}

void intake1In(Intake *intake)
{
	(*intake).frontIntakeState = INTAKE_IN;
}

void intake1Out(Intake *intake)
{
	(*intake).frontIntakeState = INTAKE_OUT;
}

void intake1Auto(Intake *intake)
{
	(*intake).frontIntakeState = AUTO_INTAKE;
}

void intake1Stop(Intake *intake)
{
	(*intake).frontIntakeState = INTAKE_OFF;
}

void intake2In(Intake *intake)
{
	(*intake).backIntakeState = INTAKE_IN;
}

void intake2Out(Intake *intake)
{
	(*intake).backIntakeState = INTAKE_OUT;
}

void intake2Stop(Intake *intake)
{
	(*intake).backIntakeState = INTAKE_OFF;
}

void intakeTriggerMacro(Intake *intake)
{
	(*intake).preMacroState = (*intake).frontIntakeState;
	(*intake).macroTriggerTime = millis();
	(*intake).frontIntakeState = INTAKE_UNJAM;
}

void runIntake(Intake *intake)
{
	switch((*intake).frontIntakeState)
	{
	case(INTAKE_OFF):
		setPantherMotor((*intake).leftMotor, 0);
		setPantherMotor((*intake).rightMotor, 0);
		break;

	case(INTAKE_IN):
		setPantherMotor((*intake).leftMotor, 127);

		if(!digitalRead((*intake).leftLimitSwitch) && !digitalRead((*intake).rightLimitSwitch))
		{
			setPantherMotor((*intake).rightMotor, 0);
		}
		else
		{
			setPantherMotor((*intake).rightMotor, 127);
		}

		break;

	case(INTAKE_OUT):
		setPantherMotor((*intake).leftMotor, -127);
		setPantherMotor((*intake).rightMotor, -127);
		break;

	case(AUTO_INTAKE):
		setPantherMotor((*intake).leftMotor, 42);
		setPantherMotor((*intake).rightMotor, 127);
		break;

	case(INTAKE_UNJAM):
		//if(millis() - (*intake).macroTriggerTime < 1000)
		//{
			setPantherMotor((*intake).leftMotor, 127);
			setPantherMotor((*intake).rightMotor, -70);
		//}
		//else
		//{
		//	(*intake).frontIntakeState = (*intake).preMacroState;
		//	runIntake(intake);
		//}
	}

	switch((*intake).backIntakeState)
	{
	case(INTAKE_OFF):
		setPantherMotor((*intake).backMotor, 0);
		break;

	case(INTAKE_IN):
		setPantherMotor((*intake).backMotor, 127);
		break;

	case(INTAKE_OUT):
		setPantherMotor((*intake).backMotor, -127);
		break;
	}
}

int isIntakeMacroOn(Intake *intake)
{
	return (*intake).frontIntakeState == INTAKE_UNJAM;
}
