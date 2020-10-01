#include <msp430.h>
#include <intrinsics.h> // Intrinsic functions

//Funciones prototipo
void Apretar();
void Soltar();


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P1DIR |=0x41;   //Defino los pines de salida (Los LED's)
	P1REN = BIT3;   //Desabilitar resistencia pullup
    P1OUT = 0x00;

	for(;;)
	{
	    Apretar();      //Ciclado hasta que se oprima
	    P1OUT = 0x01;//Enciende LED verde (bit 0)

	    Soltar();            //Ciclado hasta que se suelte
	    Apretar();      //Ciclado hasta que se oprima
	    P1OUT = 0x40;//Enciende LED rojo (bit 6). Se apaga LED verde (bit 0)

	    Soltar();            //Ciclado hasta que se suelte
	    Apretar();      //Ciclado hasta que se oprima
	    P1OUT = 0x41;//Encienden LED's verde y rojo (bits 0 y 6)

	    Soltar();            //Ciclado hasta que se suelte
	    Apretar();      //Ciclado hasta que se oprima
	    P1OUT = 0x00;//Se apagan ambos LED's

	    Soltar();            //Ciclado hasta que se suelte
	}


return 0;
}



/*Funciones para verificar si se oprime oprime o libera el push button*/
void Apretar()
{
    while ((P1IN & 0x08) != 0);
}

void Soltar()
{
    while ((P1IN & 0x08)==0);
}
