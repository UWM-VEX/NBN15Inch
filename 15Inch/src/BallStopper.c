/*
 * BallStopper.c
 *
 *  Created on: Jan 4, 2016
 *      Author: Erik
 */

#include "main.h"

BallStopper initBallStopper(int extend)
{
	pinMode(extend, OUTPUT);

	BallStopper newBallStopper = {extend};

	return newBallStopper;
}

void ballStopperUp(BallStopper stopper)
{
	digitalWrite((stopper).extend, HIGH);
}

void ballStopperDown(BallStopper stopper)
{
	digitalWrite((stopper).extend, LOW);
}
