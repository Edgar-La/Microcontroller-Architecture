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

int tr = 8000;
	for(;;) //Ciclo infinito
	{
	    iniciar_proceso();      //Espera hasta que se oprima boton inicio
	    P2OUT = 0b00001000;           //Coemienza BR
	    delay(tr);

	    P2OUT = 0b00000000;           //Detengo BR
	    P1OUT = 0b00000100;           //Sensor b
	    delay(tr);

	    P1OUT = 0b00000000;           //Apago sensor b
	    P2OUT = 0b00000010;           //On Rele
	    delay(tr);

	    P2OUT = 0b00010000;           //Off rele y comienza BL
	    delay(tr);

	    P2OUT = 0b00000000;           //Detengo BL
	    P1OUT = 0b00001000;           //Sensor c
	    delay(tr);

	    P1OUT = 0b00000000;           //Apago sensor c
	    P2OUT = 0b00000001;           //Comienza SR
	    delay(tr);

	    P2OUT = 0b00000000;           //Detengo SR
	    P1OUT = 0b00000010;           //Sensor a
	    delay(tr + 500);

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

int count;
void delay(int time_)
{
    for (count=1; count<time_; count++)
    {}
}


void senal_acustica()
{
    int sound = 0;
    for (sound = 1; sound <= 5; sound++)
    {
        P1OUT = 0b00100000;      //Enciende señal acustica
        delay(3000);
        P1OUT = 0b00000000;      //Apaga señal acustica
        delay(2000);
    }
}
