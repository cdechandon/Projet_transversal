#include <c8051f020.h>                    // SFR declarations
#include <intrins.h>   
#include "Config_Initiale.h"
//------------------------------------------------------------------------------


//*****************************************************************************
//FONCTIONS de Configuration globale du C8051F020 - 
//*****************************************************************************

SYSCLK=22118400;

void Init_Device(void)
{
	Reset_Sources_Init();
	Oscillator_Init();
	Config_XBAR();
	// EMI_Init();
	// Power_Control();
}

void Reset_Sources_Init(void)
{
	EA=0;
	WDTCN=0xDE;
	WDTCN=0xAD;
	EA=1;
}

void Oscillator_Init(void)
{
	int i=0;
	OSCXCN=0x67;
	for(i=0;i<3000;i++);
	while ((OSCXCN & 0x80) ==0);
	OSCICN = 0x0C;
}

	void Config_Timer2()
	{
		ET2 = 1;
		TF2 = 1;
		TR2 = 1;
		RCAP2L = 0xED; // base de temps de 10ms
		RCAP2H = 0xB7;
		
	}
	
	void Config_XBAR()
	{
		XBR2|= 0x40;
		XBR1 |= 0x80;
		P0MDOUT |= 0x05;
		XBR0 |= 0x08;
		P0 &= 0x00;
		
	}

void Init_PCA(void)
	{
	
		CR=1;
		//PCA0CN |= 0x40;  // desactivation du PCA
		PCA0MD |= 0x09;  // base temps = SYSCLK
		PCA0CPM0 |= 0xC2;  // mode PCA : modulation de l'impulsion 8-bits
			
	}


void PCA(unsigned char Intensite)
	{ 
		int Quantite_lumiere;
		Quantite_lumiere = 255*Intensite /100 ; // conversion du pourcentage en valeur de 0-255
		
		PCA0CPH0 = 255 - (char)Quantite_lumiere; 
		PCA0CN |= 0x41; 
        
		
	}
	
		

	