#include "C8051F020.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <config_fonction.h>

void Init_watchdog(void)
{
	 WDTCN = 0xDE;   				 //On desactive le Watchdog Timer   
	 WDTCN = 0xAD;  				 //En mettant WDTCN à 0xde puis 0xad (page 131) 
}

void Oscillator_Init(void)
{
    int i = 0; 
    OSCXCN    = 0x67;  
    for (i = 0; i < 3000; i++);   
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x0C;    
}

void ADC_Init(void)
{
    ADC0CN    = 0x84;
}