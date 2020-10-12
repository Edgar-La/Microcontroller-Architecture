//Librerias utilizadas
#include <msp430.h>
#include <intrinsics.h> // Intrinsic functions

//Funciones prototipo
void externo();
void interno();

//Funcion main
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

//////////////Aqui es donde se modifica que comparador se va a utilizar/////////////

	externo();
	//interno();
	
///////////////////////////////////////////////////////////////////////////////////
return 0;
}

//Codificacion de la funcion para comarador externo
void externo()
{
    P1DIR |= 0b001000;          //P1.3 es salida
    P1REN = 0b11;               //Desactiva resistencias pull-up de P1.0 y P1.1
    P1OUT = 0b0000;             //Limpia salida del puerto 1

    CAPD = 0b0001011;
    P1SEL =0b0001011;           //Se indican los bits utilizados para hacer comparaciones
    CACTL2 = 0b1101;            //Compara voltajes de P1.0 y P1.1; Si tiene Output
    CACTL1 = 0b00001000;        //No intercambio; Ref a terminal ´+;Comparador_A+ On
}


//Codificacion de la funcion para comarador externo
void interno()
{
    P1DIR = 0b001000;           //P1.3 es salida
    P1REN = 0b01;               //Desactiva resistencias pull-up de P1.0 y P1.1
    P1OUT = 0b0000;             //Limpia salida del puerto 1

    CAPD = 0b1001001;
    P1SEL =0b1001001;           //Se indican los bits utilizados para hacer comparaciones
    CACTL2 = 0b00110101;        //Si tiene Output
    CACTL1 = 0b01011000;        //No intercambio; Ref a terminal +; Comparo con el 25% voltaje; Comparador_A+ On
}
