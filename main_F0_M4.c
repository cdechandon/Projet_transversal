#include "C8051F020.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <config_fonction.h>
#include <configuration.h>
#include <ADC.h>
//#include <DAC.h>

void main () {
	Init_Device(); //initialisation de la carte mere
	CFG_ADC(); //configuration du convertisseur Analogique/numérique
	
	while(1)
	{
		
		MES_Dist_AV(); //appel du télémètre avant
		//MES_Dist_AR();
	}
}


