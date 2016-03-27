/*
 * RedEncoder.c
 *
 *  Created on: Feb 10, 2016
 *      Author: Erik
 */

#include "main.h"

RedEncoder initRedEncoder(Encoder encoder, long refreshTime)
{
	long currentTime = micros();
	int currentEncoder = encoderGet(encoder);
	double velocity = 0;
	RedEncoder newEncoder = {encoder, &currentTime, &currentEncoder, &velocity, refreshTime};
	return newEncoder;
}

int getRedEncoder(RedEncoder encoder)
{
	return encoderGet(encoder.encoder);
}

double getRedEncoderVelocity(RedEncoder encoder)
{
	if(micros() - (*encoder.lastReadTime) > encoder.refreshTime)
	{
		if(micros() - (*encoder.lastReadTime) < 1000000)
		{
			int currentEncoder = encoderGet(encoder.encoder);

			//lcdPrint(uart1, 2, "%d", currentEncoder - *encoder.lastEncoder);

			double velocity = (double) ((double) (currentEncoder - (*encoder.lastEncoder)) /
				(double) (micros() - (*encoder.lastReadTime)));

			*encoder.lastEncoder = encoderGet(encoder.encoder);

			*encoder.lastReadTime = micros();

			velocity *= 100000;

			//lcdPrint(uart1, 2, "%f", velocity);

			*encoder.velocity = velocity;
		}
		else
		{
			(*encoder.lastEncoder) = encoderGet(encoder.encoder);
			(*encoder.lastReadTime) = micros();
			(*encoder.velocity) = 0;
			lcdSetText(uart1, 2, "Timeout");
		}

	}

	//lcdPrint(uart1, 1, "%f", *encoder.velocity);

	return *encoder.velocity;
}
