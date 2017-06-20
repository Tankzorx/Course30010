#ifndef _DTU_LED_
#define _DTU_LED_

typedef struct
{
	int currentColumn;
	char video_buffer[5][6];
} LEDData;

void initLED(LEDData* data);
int strleng(char text[]);
void LEDSetStringByIndex(char str, int index, LEDData* data);
void LEDUpdate(LEDData* data);
void SetLEDText(char str[]);

#endif /*! _DTU_LED_ */
