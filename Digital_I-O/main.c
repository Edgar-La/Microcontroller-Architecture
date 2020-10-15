//Libreria
#include <msp430.h> 


//Funcion main
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	ADC10CTL0 = 0b0100000000010000;          //Uso de referencia externa. Pongo ADC10 On
	ADC10CTL1 = 0b0000000000000000;          //Como todo es cero puedo omitir linea, pero es para ser explicito
	ADC10AE0 |= 0b00010001;                  //Indico que PIN 0 y 1 son analogicos
	                                         //El PIN 0 es el que voy a samplear

	P1DIR |= 0b10000000;                     //Indico la salida del LED en P1.7

	//Ciclo infinito
	for(;;)
	{
	    ADC10CTL0 |= 0b0011;                 //Activo conversion y la inicio.


	    //ADC10MEM -> Registro donde se guarda la conversion
	    if(ADC10MEM < 1023)                  //Tamaño 1023 porque es aprox el tamaño completo del numero (10 bits)
	        P1OUT &= ~0b10000000;            //LED apagado. Compuerta AND negativa
	    else
	        P1OUT |= 0b10000000;             //LED encendido si o si.
	}


return 0;
}
