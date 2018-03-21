#include <c8051f020.h>
#include "config_globale.h"
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
void oscillator_init (void)
{ 
	int i=0;
	OSCXCN = 0x67; // Crystal oscillator mode
	for (i = 0; i < 3000; i++)  // Wait for 1ms
	while ((OSCXCN & 0x80) == 0x00);  // Crystal oscillator valid flag check
	OSCICN = 0x08;  // Swicth from oscillator
}

void Reset_Sources_init(void)
{
	WDTCN = 0xDE; // desactivation du watchdog
	WDTCN = 0xAD;
}

void Init_Port(void)
{ 

	P0MDOUT &= 0x3C; // P0.0, P0.1, P0.6 et P0.7 O.D
	P0= 0x41; //P0.0 et P0.6 état haut
	P3        |= 0x80;
    XBR0      = 0x06;
    XBR2      = 0x44;
	P0MDOUT |= 0x41; // P0.0, P0.1, P0.6 et P0.7 O.D
	
}

void Init_Device(void) //appel d'une fonction unique dans le main
{ 
	EA=0;
	oscillator_init();
	Reset_Sources_init();
	Init_Port();
	EA=1;
}