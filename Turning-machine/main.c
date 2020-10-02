#include <msp430.h>
#include <intrinsics.h> // Intrinsic functions

//Funciones prototipo
void Inicio_proceso();
void delay(int time_);      //Prototype delay function
void senal_acustica();


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |=0x0C;
    P2DIR |=0x07;   //Defino los pines de salida (para sensores y maquinaria)
    P1REN = BIT0;   //Desabilitar resistencia pull-up para push button
    P1OUT = 0x00;
    P2OUT = 0x00;   //Inicializo en cero los sensores y maquinaria

    for(;;)
    {
        Inicio_proceso();      //Ciclado hasta que se oprima
        P2OUT = 0x01;      //Comienza cilindro
        delay(7000);

        P1OUT = 0x04;      //Enciende sensor 'B'
        delay(7000);

        P2OUT = 0x03;      //Activa rele motor
        delay(7000);

        P1OUT = 0x0C;      //Enciende sensor 'C'
        delay(8000);
//------------------------------------------------
        P1OUT = 0x04;      //Cilindro se detuvo, Se apaga sensor 'C'
        delay(7000);

        P2OUT = 0x01;      //Se desactiva rele motor
        delay(7000);

        P1OUT = 0x00;      //Se apaga sensor 'B'
        delay(7000);

        P2OUT = 0x00;       //Apago LED cilindro
        delay(8000);
        senal_acustica();

    }

return 0;
}
//----------------------------------------------------------------
//Definicion de funciones

void Inicio_proceso()
{
    while ((P1IN & 0x01) != 0);
}

int counter;
void delay(int time_)
{
    for (counter=1; counter<time_; counter++)
    {}
}

void senal_acustica()
{
    int sound = 0;
    for (sound = 0; sound <= 5; sound++)
    {
        P2OUT = 0x04;      //Enciende señal acustica
        delay(3000);
        P2OUT = 0x00;      //Apaga señal acustica
        delay(2000);
    }
}
