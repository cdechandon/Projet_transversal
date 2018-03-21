#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"
#include "config_UART.h"
#include "CFG_Globale.h"
//parametres definis dans le sujet
#define BAUDRATE 19200 
#define SYSCLK 22118400


//fonction de config de la clk de UART0 (p81 cours UART)
void CFG_Clock_UART0(void) { 
	TR1=0;//timer stoppé
	TF1=0;//flag timer effacé
	CKCON |= 0x10; //timer1 utilisation en source d'horloge
	TMOD &= 0x0f; //auto reload
	TMOD |= 0x20; //choix du mode 8-bit et du Baud Gate control pour le Timer1
	TH1=-(SYSCLK/BAUDRATE/16); //voir schema p76 cours UART -> remonter le schema -> 271ns de periode -> 6*45ns
	ET1=0;//devalidation de l'interruption du timer1
	TR1=1; //timer1 demarré
}


void CFG_UART0(void) {
	SCON0 |= 0x70; //mise en mode 1 du SCON0
	SCON0 &= 0x7C; //RI0 actif
	PCON &= 0xbf; //SSTAT0 = 0
	PCON |= 0x80; //UART BAUDRATE divide by 2 disabled
	RCLK0 = 0; //Timer1 overflows used for recieve clock
	TCLK0 = 0; //Timer1 overflows used for transmit clock
	TI0 = 1; //Transmets interrupt flag
}

//fonction putchar, voir l'algorigramme p6 de la doc du projet
char putchar0(char c, char csg_tempo) {
	int i=0;
	do {
		if (TI0==1){ //registre SCON0 -> non adressable bit a bit, on met le drapeau de transmission de SCON0 a 1
			SBUF0 = c; //char c dans le registre de donnees de l'UART : SBUF0
			SCON0&=0xfd; //RAZ du drapeau
			return c; //caractere renvoye
		}
		else{ //si drapeau pas pret a transmettre
			for (i=0;i<250;i++) { //100us -> 45ns * 250 - en assembleur, plus de commandes utilisés pour faire un for donc 1 passage dans boucle fait beaucoup de coups d'horloge - on a fait une approximation 
				
			}
		  csg_tempo -- ; //decrementation de csg_tempo
		}
	}while (csg_tempo != 0); //while tant que csg_tempo n'est pas arrivé a 0
	return 0;
}

//transmission octet par octet (8051, car SBUF0 est buffer d'1 octet)
char Send_String0(char *char_ptr) {
	int i=0;
	char test;
	while (*char_ptr != 0x00) //tant qu'on est pas en bout de chaine
	{
		test = putchar0(*(char_ptr+i), 100); //on appelle putchar 
		i++; 
		if (test == 0x00) { //si l'UART est pas pret a transmettre un caractere (cf fonction putchar)
			return 0;
		}
	}
	return i; //nb de caracteres envoyes
}

//fonction reception d'un caractere (cf algorigramme dans la doc)
char Getchar0(void){
	char c;
	if((SCON0&0x01)==0x00) //selection du bit 1 de SCON0 , si il est a 0
	{
		return 0;
	}
	else{
		c=SBUF0; //lecture du caractere recu
		SCON0&=0xfe;
	return c;
	}
}

//fonction de test de l'UART
void test_UART0(void) {
	char c[10];
	c[0] = Getchar0(); //c prend la valeur du getchar
	c[1] = '\0';
	if (c!=0) {
		Send_String0(&c);
	}
}








//fonction de config de la clk de UART0 (p81 cours UART)
void CFG_Clock_UART1(void) { // a revoir
	TR1=0;//timer stoppé
	SCON1 &=0xFD;//flag timer effacé
	CKCON |= 0x10; //timer1 utilisation en source d'horloge
	TMOD &= 0x0f; //auto reload
	TMOD |= 0x20; //choix du mode 8-bit et du Baud Gate control pour le Timer1
	TH1=-(SYSCLK/BAUDRATE/16); //voir schema p76 cours UART -> remonter le schema -> 271ns de periode -> 6*45ns
	ET1=0;//devalidation de l'interruption du timer1
	TR1=1; //timer1 demarré
}


void CFG_UART1(void) {
	SCON1 |= 0x70; //mise en mode 1 UART1
	SCON1 &= 0x7C; //RI1 actif
	PCON &= 0xf7; //SSTAT1 = 0
	PCON |= 0x10; //UART BAUDRATE divide by 2 disabled
	RCLK0 = 0; //Timer1 overflows used for recieve clock
	TCLK0 = 0; //Timer1 overflows used for transmit clock
	SCON1 |= 0x02; //Transmets interrupt flag
}

//fonction putchar, voir l'algorigramme p6 de la doc du projet
char putchar1(char c, char csg_tempo) {
	int i=0;
	do {
		if ((SCON1&0x02)==0x02){ //registre SCON0 -> non adressable bit a bit, on met le drapeau de transmission de SCON0 a 1
			SBUF1 = c; //char c dans le registre de donnees de l'UART : SBUF1
			SCON1&=0xfd; //RAZ du drapeau
			return c; //caractere renvoye
		}
		else{ //si drapeau pas pret a transmettre
			for (i=0;i<250;i++) { //100us -> 45ns * 250 - en assembleur, plus de commandes utilisés pour faire un for donc 1 passage dans boucle fait beaucoup de coups d'horloge - on a fait une approximation 
				
			}
		  csg_tempo -- ; //decrementation de csg_tempo
		}
	}while (csg_tempo != 0); //while tant que csg_tempo n'est pas arrivé a 0
	return 0;
}

//transmission octet par octet (8051, car SBUF0 est buffer d'1 octet)
char Send_String1(char *char_ptr) {
	int i=0;
	char test;
	while (*(char_ptr+i) != 0x00) //tant qu'on est pas en bout de chaine
	{
		test = putchar1(*(char_ptr+i), 100); //on appelle putchar 
		i++; 
		if (test == 0x00) { //si l'UART est pas pret a transmettre un caractere (cf fonction putchar)
			return 0;
		}
	}
	return i; //nb de caracteres envoyes
}

//fonction reception d'un caractere (cf algorigramme dans la doc)
char Getchar1(void){
	char c;
	if((SCON1&0x01)==0x00) //selection du bit 1 de SCON1 , si il est a 0
	{
		return 0;
	}
	else{
		c=SBUF1; //lecture du caractere recu
		SCON1&=0xfe;
	return c;
	}
}

//fonction de test de l'UART
void test_UART1(void) {
	char c[10];
	c[0] = Getchar1(); //c prend la valeur du getchar
	c[1] = '\0';
	if (c!=0) {
		Send_String1(&c);
	}
}