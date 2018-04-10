#include <c8051f020.h>                    // SFR declarations
#include <intrins.h>  

#include <ADC.h>
//------------------------------------------------------------------------------

//*****************************************************************************
//FONCTIONS de MANIPULATION DU ADC0 - 

//Declaration des variables tension et distance en global
float tension;
float distance; 

//Configuration de l'adc
void CFG_ADC(void)
{
	 CFG_VREF();
   CFG_ADC0();
}

//Configuration de la tension de référence
void CFG_VREF(void){
	
	REF0CN &= 0xEF;
	REF0CN |=  0x03; //activation de la source de tension de reference
}


void CFG_ADC0(void){
	
	ADC0CF = 0xFF; //rapport AD0SC max car CLKSAR<2.5MHz et gain de 0.5 
	
	//AVANT
	AMX0SL =0x04;//Conversion sur AIN0.4
	AMX0CF =0x00;//AIN0 en sortie indépendante

	ADC0CN = 0x81;//initialisation de l'ADC0 control register
		
	REF0CN=0x03; //tension de reference
}



//MESURE DISTANCE AVANT
float MES_Dist_AV(void){
	ADC0CN |=0x10; //mise à 1 de AD0BUSY
	while(AD0INT==0); //boucle qui n s'arrete à la fin de la conversion
	
	AD0INT=0; // RAZ du drapeau
	
	tension=ADC0H*2.4/(1*254); //On récupère la tension à partir du télémètre
	
	//return ADC0H;
	convertion(); //Appel de la fonction conversion
	return distance; //retourne la distance calculée dans la fonction conversion
}	

//MESURE DISTANCE ARRIERE
 float MES_Dist_AR(void){
	ADC0CN |=0x10; //mise à 1 de AD0BUSY
	while(AD0INT==0); //boucle qui n s'arrete à la fin de la conversion
	
	AD0INT=0; // RAZ du drapeau
	
	tension=ADC0H*2.4/(1*254);
	
	//return ADC0H;
	convertion();
	return distance;
}

//FONCTION CONVERSION
float convertion (void) {
	
	if (tension>=0.6 && tension<=1.32){
		distance=(-tension+1.6304)/0.0214;  
	}
	else if(tension>=0 && tension<=0.6){
		distance=(-tension+0.8168)/0.0053;
	}
	else{
		distance=0;
	}
	
}


