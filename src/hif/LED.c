#include <eZ8.h>             // special encore constants, macros and flash routines
#include "LED.h"
#include "charset.h"



void LEDSetStringByIndex(char str, int index, LEDData* data) {
	int j;
	for (j = 1; j < 6; j++)
	{
		data->video_buffer[index][j] = character_data[(int) str - 0x20][j-1];
	}
	data->video_buffer[index][0] = 0; 
}

int strleng(char text[]) {
	int i;
	for (i = 0; text[i] != '\0'; i++){}
	return i;
}

void initLED(char LEDText[LED_MAX_STR_LEN], LEDData* data) {
	int i;
	//int LEDTextLen = strleng(LEDText);
	PEDD = 0; // ALL BITS TO OUTPUT. (Data direction)
	PGDD = 0;
	data->insertNewCharFlag = 0;
	data->currentColumn = 0;
	data->LEDOffset = 0;
	data->LEDTextOffset = 0;
	data->videoBufferReplaceOffset = 0;
	/*
	for (i = 0; i < LEDTextLen; i++)
	{
		data->LEDText[i] = LEDText[i];
	}

	for (i = 0; i < 5; i++)
	{
		LEDSetStringByIndex(data->LEDText[i],i, data);
	}*/
}

// void LEDUpdate(LEDData* data) {

// }