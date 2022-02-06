#include <lpc214x.h>
#include "LPC2148_delay.h"

#define RS 0x01000000;
#define EN 0x02000000;

void Lcd_Command(char cmd)                          
{
	IOCLR1 =0XFF<<16;
	IOSET1 = cmd<<16;
	IOCLR1 = RS;
	IOSET1 =  EN;
	delay(10);
	IOCLR1 = EN;
}

void Lcd_Data(char Data)
{
	IOCLR1 = 0XFF<<16;
	IOSET1 = Data<<16;
	IOSET1 = RS;
	IOSET1 =  EN;
	delay(10);
	IOCLR1 = EN;
}

void Lcd_String(const unsigned char *Str)
{
	while(*Str)
	{
		Lcd_Data(*Str++);
	}
}

void Lcd_Intialization()
{
	Lcd_Command(0x38);
	Lcd_Command(0x06);
	Lcd_Command(0x0c);
}

int main()
{
	PINSEL2 = 0x00000000;
	IODIR1 = 0x3FF<<16;
	
	Lcd_Intialization();
	
	while(1)
	{
		Lcd_Command(0x80);
		Lcd_String("LYCASOFT");
	}
}