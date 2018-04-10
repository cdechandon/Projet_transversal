#include "C8051F020.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <configuration.h>
#include <config_fonction.h>

void Init_Device(void)
{
	Init_watchdog();
	Oscillator_Init();
	ADC_Init();
}