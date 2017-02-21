/*
 * ports.c
 *
 *  Created on: Aug 24, 2016
 *      Author: joest
 */
#include "RBELib/RBELib.h"

void setPinsDir(char port, int dir, char numPins, ...)
{
	if(port == 'A')
	{
		DDRA = (0xFF & dir);
	}

	if(port == 'B')
	{
		DDRB = (0xFF & dir);
	}

	if(port == 'C')
	{
		DDRC = (0xFF & dir);
	}

	if(port == 'D')
	{
		DDRD = (0xFF & dir);
	}

}

unsigned char getPinsVal(char port, int numPins, ...)
{
char X;

	return X;
}

void setPinsVal(char port, int val, int numPins, ...)
{
	if(port == 'A')
	{
		PORTA = (0xFF & val);
	}

	if(port == 'B')
	{
		PORTB = (0xFF & val);
	}

	if(port == 'C')
	{
		PORTC = (0xFF & val);
	}

	if(port == 'D')
	{
		PORTD = (0xFF & val);
	}
}
