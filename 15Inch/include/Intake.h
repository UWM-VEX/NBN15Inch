/*
 * Intake.h
 *
 *  Created on: Oct 29, 2015
 *      Author: Erik
 */

#ifndef INCLUDE_INTAKE_H_
#define INCLUDE_INTAKE_H_

#define INTAKE_OFF 0
#define INTAKE_IN 1
#define INTAKE_OUT 2
#define AUTO_INTAKE 3
#define INTAKE_UNJAM 4

struct Intake{

	PantherMotor frontMotor;
	PantherMotor middleMotor1;
	PantherMotor middleMotor2;
	PantherMotor backMotor;
	int leftLimitSwitch;
	int rightLimitSwitch;
	int frontIntakeState;
	int backIntakeState;
	long macroTriggerTime;
	int preMacroState;

}typedef Intake;

/**
 * Use in initIO method.
 */
Intake initIntake(PantherMotor frontMotor, PantherMotor middleMotor1,
		PantherMotor middleMotor2, PantherMotor backMotor);
void intake1In(Intake *intake);
void intake1Out(Intake *intake);
void intake1Auto(Intake *intake);
void intake1Stop(Intake *intake);
void intake2In(Intake *intake);
void intake2Out(Intake *intake);
void intake2Stop(Intake *intake);
void intakeTriggerMacro(Intake *intake);
int isIntakeMacroOn(Intake *intake);
void runIntake(Intake *intake);

#endif /* INCLUDE_INTAKE_H_ */
