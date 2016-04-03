/*
 * RedEncoder.c
 *
 *  Created on: Feb 10, 2016
 *      Author: Erik
 */

#include "main.h"

RedEncoder initRedEncoder(Encoder encoder, unsigned long refreshTime)
{
	RedEncoder newEncoder = {encoder, malloc(sizeof(unsigned long)), malloc(sizeof(int)), malloc(sizeof(double)), refreshTime};
	*newEncoder.lastReadTime = micros();
	*newEncoder.lastEncoder = encoderGet(encoder);
	*newEncoder.velocity = 0;
	return newEncoder;
}

int getRedEncoder(RedEncoder encoder)
{
	return encoderGet(encoder.encoder);
}

double getRedEncoderVelocity(RedEncoder encoder)
{
	if((unsigned int) (micros() - (*encoder.lastReadTime)) > (unsigned int) encoder.refreshTime)
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

	//lcdPrint(uart1, 1, "C%d", (unsigned int) micros());
	//lcdPrint(uart1, 2, "L%d", (unsigned int) micros() - *encoder.lastReadTime);
	//lcdPrint(uart1, 2, "%f", *encoder.velocity);

	return *encoder.velocity;
}
