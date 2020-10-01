#include <msp430.h>
#include <intrinsics.h> // Intrinsic functions

//Funciones prototipo
void Apretar();
void Soltar();


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P2DIR |=0xFF;   //Defino los pines de salida (para display 8 segmentos)
    P1REN = BIT3;   //Desabilitar resistencia pull-up para push button
    P2OUT = 0x3F;   //Inicializo en cero

    for(;;)
    {
        Apretar();      //Ciclado hasta que se oprima
        P2OUT = 0x06;      //1

        Soltar();            //Ciclado hasta que se suelte
        Apretar();      //Ciclado hasta que se oprima
        P2OUT = 0x5B;      //2

        Soltar();            //Ciclado hasta que se suelte
        Apretar();      //Ciclado hasta que se oprima
        P2OUT = 0x4F;      //3

        Soltar();            //Ciclado hasta que se suelte
        Apretar();      //Ciclado hasta que se oprima
        P2OUT = 0x66;      //4

        Soltar();            //Ciclado hasta que se suelte
        Apretar();      //Ciclado hasta que se oprima
        P2OUT = 0x6D;      //5

        Soltar();            //Ciclado hasta que se suelte
        Apretar();      //Ciclado hasta que se oprima
        P2OUT = 0x7D;      //6

        Soltar();            //Ciclado hasta que se suelte
        Apretar();      //Ciclado hasta que se oprima
        P2OUT = 0x07;      //7

        Soltar();            //Ciclado hasta que se suelte
        Apretar();      //Ciclado hasta que se oprima
        P2OUT = 0x7F;      //8

        Soltar();            //Ciclado hasta que se suelte
        Apretar();      //Ciclado hasta que se oprima
        P2OUT = 0x6F;      //9

        Soltar();            //Ciclado hasta que se suelte
        Apretar();      //Ciclado hasta que se oprima
        P2OUT = 0x3F;      //0

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
