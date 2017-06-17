#ifndef _DTU_LED_
#define _DTU_LED_


#define LED_MAX_STR_LEN 50

typedef struct
{
	int currentColumn;
	int LEDOffset;
	int LEDTextOffset;
	int insertNewCharFlag;
	int videoBufferReplaceOffset;
	char LEDText[LED_MAX_STR_LEN];
	char video_buffer[5][6];
} LEDData;

void initLED(char LEDText[LED_MAX_STR_LEN], LEDData* data);
int strleng(char text[]);
void LEDSetStringByIndex(char str, int index, LEDData* data);
void LEDUpdate(LEDData* data);
void SetLEDText(char str[]);

#endif /*! _DTU_LED_ */
