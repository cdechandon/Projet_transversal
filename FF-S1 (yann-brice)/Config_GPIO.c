#include <c8051f020.h>  

void Config_GPIO(void)
{
	XBR0 |= 0x08;
	P0MDOUT |= 0x40;
	XBR2 |= 0x40;
	
}