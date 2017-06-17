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
	int LEDTextLen = strleng(LEDText);
	PEDD = 0; // ALL BITS TO OUTPUT. (Data direction)
	PGDD = 0;
	data->insertNewCharFlag = 0;
	data->currentColumn = 0;
	data->LEDOffset = 0;
	data->LEDTextOffset = 0;
	data->videoBufferReplaceOffset = 0;
	
	for (i = 0; i < LEDTextLen; i++)
	{
		data->LEDText[i] = LEDText[i];
	}

	for (i = 0; i < 5; i++)
	{
		LEDSetStringByIndex(data->LEDText[i],i, data);
	}
}

void LEDUpdate(LEDData* data) {
    char columnArray[5] = { 0x1E, 0x1D, 0x1B, 0x17, 0x0F };
	PEOUT = columnArray[data->currentColumn];

	if (data->insertNewCharFlag == 1)
	{

		if (data->LEDTextOffset == strleng(data->LEDText))
		{
			data->LEDTextOffset = 0;
		}
		LEDSetStringByIndex(data->LEDText[data->LEDTextOffset], data->videoBufferReplaceOffset, data);
		if (data->videoBufferReplaceOffset == 4)
		{
			data->videoBufferReplaceOffset = -1;
		}
		data->insertNewCharFlag = 0;
		data->videoBufferReplaceOffset = data->videoBufferReplaceOffset + 1;
		data->LEDTextOffset = data->LEDTextOffset + 1;
	}


	PGOUT = *(&(data->video_buffer[0][0]) + ((data->LEDOffset + (5 - data->currentColumn)) % (30))); 
	PEOUT &= 0x1F;
	PEOUT |= 0x80; // Send clock signal.

	PGOUT = *(&(data->video_buffer[0][0]) + ((data->LEDOffset + 6 + (5 - data->currentColumn)) % (30))); 
	PGOUT &= 0x7F;
	PGOUT |= 0x80; // Send clock signal.

	PGOUT = *(&(data->video_buffer[0][0]) + ((data->LEDOffset + 12 + (5 - data->currentColumn)) % (30))); 
	PEOUT &= 0x1F;
	PEOUT |= 0x20; // Send clock signal.

	PGOUT = *(&(data->video_buffer[0][0]) + ((data->LEDOffset + 18 + (5 - data->currentColumn)) % (30))); 
	PEOUT &= 0x1F;
	PEOUT |= 0x40; // Send clock signal.


	data->currentColumn = (data->currentColumn + 1);

	if (data->currentColumn == 5) {
		data->currentColumn = 0;
	}

}