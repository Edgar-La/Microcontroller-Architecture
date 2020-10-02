//Librerias ----------------------------------------------------
#include <msp430.h>
#include <intrinsics.h> // Intrinsic functions

//Funciones prototipo-------------------------------------------
void Activar_Desactivar();
void delay(int time_);
void conteo_piezas(int piezas_);
void S_acustica_y_M_embalajes();

//Funcion main--------------------------------------------------
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR |= 0b00000110;      //Defino salidas puerto 1
    P2DIR |= 0b00000111;      //Defino salidas puerto 2
    P1REN = BIT0;       //Desactivo resistencia pull up Puerto 1 bit O
    P1OUT = 0x00;       //Inicializo salida en cero
    P2OUT = 0x00;       //Inicializo salida en cero

    int Piezas = 10;

    for(;;) //Ciclo infinito
    {
        Activar_Desactivar();           //Espera hasta que se cierra switch
        conteo_piezas(Piezas);          //Ciclo para para las n-piezas
        S_acustica_y_M_embalajes();     //Inicia senal acustica y cambio de envase
    }

return 0;
}




//Definicion de funciones
////////////////////////////////////////////////////////////////
void Activar_Desactivar()
{
    while((P1IN & 0x01) != 0)       //Ciclado hasta que el operario aprieta Inicio
    {
       P1OUT = 0b0000;
       P2OUT = 0b0000;
    }
}

////////////////////////////////////////////////////////////////
int count;
void delay(int time_)
{for (count=1; count<time_; count++){}}

////////////////////////////////////////////////////////////////
void conteo_piezas(int piezas_)
{   int i;
    for(i = 0; i < piezas_; i++)
    {
        P2OUT = 0b0001;
        P1OUT = 0b0110;
        delay(4000);
        P1OUT = 0b0100;
        delay(3000);
        Activar_Desactivar();
    }
}

////////////////////////////////////////////////////////////////
void S_acustica_y_M_embalajes()
{   int sound = 0;
    P1OUT = 0b0000;
    for (sound = 1; sound <= 7; sound++)
    {
        P2OUT = 0b0110;      //Enciende señal acustica
        delay(4000);
        P2OUT = 0b0010;      //Apaga señal acustica
        delay(3000);
        Activar_Desactivar();
    }
}
