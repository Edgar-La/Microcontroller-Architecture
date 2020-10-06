#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= 0b1000000;         // Defino salidas puerto 1
	P1REN = BIT0;               // Desactivo resistencia pull-up del BIT0.
	P1SEL = 0x01;	            //Configurar los sel para que P1.0 se utilizado como la entrada del timer A
	P1OUT = 0x00;               //Limpiar puerto

	TACTL = 0b0000000001100000; //Configuro el timer A (TACTL) ////TACTL |= 0x0060; es lo mismo
	int clics = 10;
	volatile unsigned int i;
	for (;;)
	{
	    TAR = 0;                  //Se inicializo el TAR (Registro del Timer A)
	    while (TAR != clics/2);   //Espero a que llegue a la cuenta deseada
	    P1OUT = 0b01000000;       //Si ya llega a 5, se enciende el LED

	    i = 65000;
	    do(i--);
	    while (i |= 0);
	    P1OUT = 0;
	}
return 0;
}
