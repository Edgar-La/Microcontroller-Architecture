//Librerias ----------------------------------------------------
#include <msp430.h>
#include <intrinsics.h>

//Funciones prototipo-------------------------------------------
void iniciar_proceso();
void delay(int time_);
void senal_acustica();

//Funcion main--------------------------------------------------
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P1DIR |= 0x1E;
	P2DIR |= 0x1B;
	P1REN = BIT0;
	P1OUT = 0x00;
	P2OUT = 0x00;

	for(;;)
	{
	    iniciar_proceso();      //Espera hasta que se oprima boton inicio
	    P2OUT = 0x08;           //Coemienza BR
	    delay(8000);

	    P2OUT = 0x00;           //Detengo BR
	    P1OUT = 0x04;           //Sensor b
	    delay(8000);

	    P1OUT = 0x00;           //Apago sensor b
	    P2OUT = 0x02;           //On Rele
	    delay(8000);

	    //P2OUT = 0x00;           //Off rele
	    //P1OUT = 0x00;
	    //delay(100);
	    P2OUT = 0b00010000;           //Off rele y comienza BL
	    delay(8000);

	    P2OUT = 0x00;           //Detengo BL
	    P1OUT = 0x08;           //Sensor c
	    delay(8000);

	    P1OUT = 0x00;           //Apago sensor c
	    P2OUT = 0x01;           //Comienza SR
	    delay(8000);

	    P2OUT = 0x00;           //Detengo SR
	    P1OUT = 0x02;           //Sensor a
	    delay(8500);

	    senal_acustica();       //Inicia senal acustica
	}

	
	return 0;
}

//Definicion de funciones---------------------------------------
void iniciar_proceso()
{
    while((P1IN & 0x01) != 0);
}

int count;
void delay(int time_)
{
    for (count=1; count<time_; count++)
    {}
}

void senal_acustica()
{
    int sound=0;
    for (sound=0; sound<=5; sound++)
    {
        P1OUT = 0b00010000;
        delay(3000);
        P1OUT = 0b00000000;
        delay(2000);
    }

}
