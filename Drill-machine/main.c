//Librerias ----------------------------------------------------
#include <msp430.h>
#include <intrinsics.h> // Intrinsic functions

//Funciones prototipo-------------------------------------------
void iniciar_proceso();
void delay(int time_);
void senal_acustica();

//Funcion main--------------------------------------------------
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= 0b00101110;      //Defino salidas puerto 1
	P2DIR |= 0x1B;      //Defino salidas puerto 2
	P1REN = BIT0;       //Desactivo resistencia pull up Puerto 1 bit O
	P1OUT = 0x00;       //Inicializo salida en cero
	P2OUT = 0x00;       //Inicializo salida en cero



int tr = 30000;
	for(;;) //Ciclo infinito
	{
	    iniciar_proceso();            //Espera hasta que se oprima boton inicio
	    //P1OUT = 0b0010;             //Sensor 'a'
	    //delay(tr);

	    P2OUT = 0b1000;               //Comienza BR
	    delay(tr);

	    P1OUT = 0b0100;               //LLega a sensor b y
	    P2OUT = 0b00010010;           // activo Rele y bajanda lenta
	    delay(tr);

	    P1OUT = 0b1000;           //Sensor c
	    P2OUT = 0b0000011;           //Subida rapida y sigue activo rele.
	    delay(tr);

	    P1OUT = 0b00000010;           //Se activa sensor a
	    P2OUT = 0b00000000;           //Detengo subida rapida y rele.
	    delay(tr);

	    P1OUT = 0b00000000;           //Apago sensor a
	    senal_acustica();             //Inicia senal acustica
	}

return 0;
}





//Definicion de funciones---------------------------------------
void iniciar_proceso()
{
    while((P1IN & 0x01) != 0); //Ciclado hasta que el operario aprieta Inicio
    while((P1IN & 0x01) == 0); //Ciclado hasta que operario libere Inicio
}
////////////////////////////////////////////////////////////////
int count;
void delay(int time_)
{
    for (count=1; count<time_; count++)
    {}
}
////////////////////////////////////////////////////////////////
void senal_acustica()
{
    int sound = 0;
    for (sound = 1; sound <= 5; sound++)
    {
        P1OUT = 0b00100000;      //Enciende señal acustica
        delay(4000);
        P1OUT = 0b00000000;      //Apaga señal acustica
        delay(3000);
    }
}
