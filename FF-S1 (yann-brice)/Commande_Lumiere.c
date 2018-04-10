#include "c8051F020.h"
#include "Config_Initiale.h"
#include "Declarations_GPIO_BSE.h"


#define SYSCLK 22118400


int Lum_ON10=0; //création variables globales pour utilisation dans interruption
int Lum_OFF10=0;
int Lum_Nbre_Glob=0;
int Intensite_Glob=0;
int i = 0;
int j = 0;
	
void Lumiere(unsigned char Intensite, unsigned char Lum_ON, unsigned char Lum_OFF, unsigned char Lum_Nbre)
	{    
    Lum_ON10 = 10*Lum_ON; //adaptation des temps car interruption de 10ms
    Lum_OFF10 = 10*Lum_OFF - 1;
    Lum_Nbre_Glob = Lum_Nbre;
    Intensite_Glob = Intensite;
	}
	
	
	
	
void Lumiere_Stop(void)
	{
		PCA(0); //extinction
	}
	
	
void Interrupt_Timer2() interrupt 5
{
	//P0 ^= 0x04; // test interruption 10ms
	
   if (Lum_Nbre_Glob!=0) //on continue l'interruption pour le nombre de cycle voulu
   {
        if (Lum_ON10 != 0) //phase allumage
        {
            PCA(Intensite_Glob);
            Lum_ON10 = Lum_ON10-1;
						i = i+1; //mise en mémoire de la durée d'allumage pour réutilisation lors du procahin cycle
        }
        else
        {
            Lumiere_Stop();
            Lum_OFF10 = Lum_OFF10-1;
						j = j+1; //mise en mémoire durée extinction
					
						if (Lum_OFF10 == 0)
						{
								Lum_Nbre_Glob = Lum_Nbre_Glob - 1;
								Lum_ON10 = i; //affectation aux valeurs initiales
								Lum_OFF10 = j;
								i = 0; //reinitialisation pour utilisation ulterieure
								j = 0;
								
						}
        }
        
   }

	 
	TF2 = 0; // Mise à zero du drapeau
}

	