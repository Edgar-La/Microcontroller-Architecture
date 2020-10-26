#include <msp430.h>
#include "intrinsics.h"
#include "lcdLib.h"                                     //Se modifico para que tenga salidas en Puerto 3

int main( void )
{
   WDTCTL = WDTPW + WDTHOLD;                            // Stop watchdog timer to prevent time out reset

   ADC10CTL0 = SREF_2 + REFBURST + ADC10ON; //Las eqtiquetas indican lo que hace
   ADC10AE0 |= BIT0+BIT4;                               //Indico los pines que voy a samplear
   P1DIR |= 0b11100000;                                     //Indico la salida de LEDs de temperatura

   int Temp_num;
   char Temp[16];


   //Inicio la pantalla lcd
   lcdInit();
   lcdSetText("Inicializando...", 0, 0);

   for (;;)
   {
      ADC10CTL0 |= ENC + ADC10SC;             //Activo e inicio la conversión


      //Temp_num = ADC10MEM*(150/1023);
      //Temp_num = ADC10MEM*(0.146627566);
      Temp_num = (ADC10MEM*0.2326)-87.33;
      sprintf(Temp, "%d", Temp_num);
      strcat(Temp, "*C ");
      lcdSetText("Temperatura de:", 0, 0);
      lcdSetText(Temp, 0, 1);


      if (Temp_num > 75)
          P1OUT = 0b00100000;                        //Temp. Alta, LED rojo ON
      else if (Temp_num >= 25 && Temp_num <= 75)
          P1OUT = 0b01000000;                        //Temp. Media, LED verde ON
      else if (Temp_num < 25)
          P1OUT = 0b10000000;                        //Temp. Baja, LED azul ON
      else
          P1OUT &= ~0b11100000; ;                     //Si o si, todos OFF
   }
}

