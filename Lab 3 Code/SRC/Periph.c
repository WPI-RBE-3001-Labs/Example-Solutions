/*
 * Periph.c
 *
 *  Created on: Aug 24, 2016
 *      Author: joest
 */


/*
 * Periph.c
 *
 *  Created on: Jul 16, 2014
 *      Author: ewillcox
 */

#include "RBELib/RBELib.h"




int GetAccelerationH48C(int axis){
	unsigned int in = 0;
	// Chip select pin to active-low
	PORTDbits._P7 = OFF;
	// Transceives the first byte with leading Zeros and then Start bit, mode bit, Dont care bit.
	spiTransceive(0b00000110);
	//Shifts  axis into the first two bits and sends zero bits for recieving
	in = spiTransceive((axis << 6));
	//Shifts the byte that was just read
	in = (in & 0x0F) << 8;
	//sends zeros and recieves the rest of the data
	in += spiTransceive(0x00);
	//Chip select Pin to Inactive-High
	PORTDbits._P7 = ON;
	//returns the data from the ADC/Accelerometer
	return (in);
}

//Address for CNTR reg
#define ENC_adrs_CNTR 0x20

//Clear command
#define ENC_cmd_CLR 0x00
//Read command
#define ENC_cmd_RD  0x40


void encInit(int chan){
  //Assert the appropriate encoder
  switch(chan){
  case 0: //p5
    ENCODER_SS_0 = 1;
    ENCODER_SS_0 = 0;
    break;
  case 1:  //p4
    ENCODER_SS_1 = 1;
    ENCODER_SS_1 = 0;
    break;
  default:
    printf("encInit() - Can't asset encoder %d\n\r", chan);
    break;
  }

  //Clear the encoder counts
  spiTransceive(ENC_cmd_CLR | ENC_adrs_CNTR);
}


signed long encCount(int chan){
  //3 temporary values for obtaining the final value
  signed long temp1 = 0;
  signed long temp2 = 0;
  signed long temp3 = 0;
  signed long temp4 = 0;
  //Final value
  signed long encData = 0;

  //Assert the encoder
  switch(chan){
  case 0:
    ENCODER_SS_0 = 1;
    ENCODER_SS_0 = 0;
    break;
  case 1:
    ENCODER_SS_1 = 1;
    ENCODER_SS_1 = 0;
    break;
  default:
    printf("encCount() - Can't asset encoder %d\n\r", chan);
    break;
  }

  //Send the read command
  spiTransceive(ENC_cmd_RD | ENC_adrs_CNTR);
  //Get the data in 3 packets
  //Starts with upper 8 bytes and continues downwards
  temp1 = spiTransceive(0x00);
  temp2 = spiTransceive(0x00);
  temp3 = spiTransceive(0x00);
  temp4 = spiTransceive(0x00);
  //Shift the data into the appropriate places and combine them to one value
  encData = (temp1 << 24) | (temp2 << 16) |
      (temp3 << 8) | (temp4);

  //Deassert the encoders
  ENCODER_SS_0 = 1;
  ENCODER_SS_1 = 1;

  return encData;
}

