/*
 * BallStopper.h
 *
 *  Created on: Jan 4, 2016
 *      Author: Erik
 */

#ifndef INCLUDE_BALLSTOPPER_H_
#define INCLUDE_BALLSTOPPER_H_

struct BallStopper{

	int extend;

}typedef BallStopper;

BallStopper initBallStopper(int extend);
void ballStopperUp(BallStopper stopper);
void ballStopperDown(BallStopper stopper);

#endif /* INCLUDE_BALLSTOPPER_H_ */
