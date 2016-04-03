/*
 * RedEncoder.h
 *
 *  Created on: Feb 10, 2016
 *      Author: Erik
 */

#ifndef SRC_REDENCODER_H_
#define SRC_REDENCODER_H_

#include "main.h"

struct RedEncoder{

	Encoder encoder;
	unsigned long *lastReadTime;
	int *lastEncoder;
	double *velocity;
	unsigned long refreshTime;

}typedef RedEncoder;

RedEncoder initRedEncoder(Encoder encoder, unsigned long refreshTime);
int getRedEncoder(RedEncoder encoder);
double getRedEncoderVelocity(RedEncoder encoder);

#endif /* SRC_REDENCODER_H_ */
