#include "c8051F020.h"
#include <intrins.h>
#include "Declarations_GPIO_BSE.h"
#include "Commande_Lumiere.h"
#include "Config_Initiale.h"



void main()
{ 
	
	Init_Device();
	Init_PCA();
	Config_Timer2();
	Lumiere(100,5,5,30);
    
	while(1)
	{
	  
	}
}


