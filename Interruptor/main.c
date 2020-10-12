//Librerias
#include <msp430.h> 
//#include <intrinsics.h> // Intrinsic functions

//Funcion prototipo
void Interruptor();

//Funcion main
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P1DIR |= 0b0001;                          // Definir salida en P1.0
  P1OUT =  0b0000;                          // Limpiar salida del puerto 1
  P1REN = BIT3;                             // Desactiva resistencia pullup de P1.3
  P1SEL = 0;                                // No es necesario por ahora
  P1IE = 0x08;                              // Activa interruptor en P1.3
  P1IES = 0x08;                             // Defino P1.3 como High/Low
  P1IFG = 0xFF^BIT3;                        //Indico donde va a estar la bandera

  //Ciclo infinito
  for(;;)
  {
      //Pregunto si la bandera está levantada, si sí llama la funcion
      if (P1IFG == 0xFF)
          Interruptor();
  }
return 0;
}

//Funcion interruptor
void Interruptor()
{
  P1OUT ^= 0x01;                            // Compuerta XOR para LED.
  P1IFG &= ~0x08;                           // Estado del boton
}
