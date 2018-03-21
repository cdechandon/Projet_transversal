#include <c8051f020.h>
#include "config_globale.h"
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#include "config_UART.h"
#include "FO_M1.h"
#include "UART0_RingBuffer_lib.h"
	int compteur;
	char reception[6];	
	char Vit[4];
	struct COMMANDES commande;
void main (){	
	char  c;
	Init_Device();
	CFG_Clock_UART1();
	CFG_UART1();
	cfg_Clock_UART();
  cfg_UART0_mode1();
	
	init_Serial_Buffer();                            
  EA = 1;   
	
	while(1){
		compteur=0;
		while(c=serInchar()==0){}	//PB : Sort jamais de la boucle
			
		while((c!='\r') && c!=0){
			c=serInchar();
			reception[compteur]=c;
			compteur++;
		}
		reception[compteur]='\0';
		if( reception[0] == ('A') ) {
			commande.Etat_Mouvement = Avancer;
		}
		Vit[0]=reception[2];
		Vit[1]=reception[3];
		Vit[2]=reception[4];
		Vit[3]='\0';
		commande.Vitesse=Vit;
		
		serOutstring(Vit);
		serOutstring(reception);
}

  //Send_String1("digo 1:60000:100 2:60000:100\n\r");
while(1) {
    
	  /*if (BP ==0) {
		while ((c=serInchar())!=0) serOutchar(c);
		}	*/
	   //serOutstring("Test_Buffer_Circulaire");
	}
}