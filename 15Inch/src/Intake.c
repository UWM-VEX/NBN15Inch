/*
 * Intake.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Erik
 */

#include "main.h"

Intake initIntake(PantherMotor frontMotor, PantherMotor middleMotor1,
		PantherMotor middleMotor2, PantherMotor backMotor)
{
	Intake newIntake = {frontMotor, middleMotor1, middleMotor2, backMotor,
			INTAKE_OFF, INTAKE_OFF, millis(), INTAKE_OFF};
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
		setPantherMotor((*intake).frontMotor, 0);
		setPantherMotor((*intake).middleMotor1, 0);
		break;

	case(INTAKE_IN):
		setPantherMotor((*intake).frontMotor, 127);
		setPantherMotor((*intake).middleMotor1, 127);

		break;

	case(INTAKE_OUT):
		setPantherMotor((*intake).frontMotor, -127);
		setPantherMotor((*intake).middleMotor1, -127);
		break;

	case(AUTO_INTAKE):
		setPantherMotor((*intake).frontMotor, 42);
		setPantherMotor((*intake).middleMotor1, 127);
		break;

	case(INTAKE_UNJAM):
		setPantherMotor((*intake).frontMotor, 127);
		setPantherMotor((*intake).middleMotor1, -70);
		break;
	}

	switch((*intake).backIntakeState)
	{
	case(INTAKE_OFF):
		setPantherMotor((*intake).backMotor, 0);
	setPantherMotor((*intake).middleMotor2, 0);
		break;

	case(INTAKE_IN):
		setPantherMotor((*intake).backMotor, 127);
	setPantherMotor((*intake).middleMotor2, 127);
		break;

	case(INTAKE_OUT):
		setPantherMotor((*intake).backMotor, -127);
		setPantherMotor((*intake).middleMotor2, -127);
		break;
	}
}

int isIntakeMacroOn(Intake *intake)
{
	return (*intake).frontIntakeState == INTAKE_UNJAM;
}
