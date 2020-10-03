#include <msp430.h>
#include <intrinsics.h> // Intrinsic functions

//Funciones prototipo
void Inicio_proceso();
void delay(int time_);      //Prototype delay function
void senal_acustica();


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |=0b1110;
    P2DIR |=0b0111;;   //Defino los pines de salida (para sensores y maquinaria)
    P1REN = BIT0;   //Desabilitar resistencia pull-up para push button
    P1OUT = 0x00;
    P2OUT = 0x00;   //Inicializo en cero los sensores y maquinaria
int t_delay =31000;
    for(;;)
    {
        Inicio_proceso();      //Ciclado hasta que se oprima
        P1OUT = 0b0010;
        P2OUT = 0b0001;      //Comienza cilindro
        delay(t_delay);

        P1OUT = 0b0100;      //Enciende sensor 'B'
        P2OUT = 0b0011;      //Enciende rele, sigue cilindro
        delay(t_delay);

        P1OUT = 0b1000;      //Enciende sensor 'C'
        P2OUT = 0b0010;      //Desactivo cilindro, sigue rele.
        delay(t_delay);

        P1OUT = 0b0100;      //Vuelve a pasar por sensor 'B'
        P2OUT = 0b0000;      //Apago rele.
        delay(t_delay);

        P1OUT = 0b0010;
        senal_acustica();

        P1OUT = 0b0000;

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
