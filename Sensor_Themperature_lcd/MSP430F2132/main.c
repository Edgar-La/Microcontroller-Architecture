#include <msp430.h>
#include "intrinsics.h"
#include "lcdLib.h"                                     //Se modifico para que tenga salidas en Puerto 3

int main( void )
{
   WDTCTL = WDTPW + WDTHOLD;                            // Stop watchdog timer to prevent time out reset

   ADC10CTL0 = SREF_2 + ADC10SHT_2 + ADC10ON + ADC10IE; //Las eqtiquetas indican lo que hace
   ADC10AE0 |= BIT0+BIT4;                               //Indico los pines que voy a samplear
   P1DIR |= 0b0111;                                     //Indico la salida de LEDs de temperatura

   int Temp_num;
   char Temp[16];


   //Inicio la pantalla lcd
   lcdInit();
   lcdSetText("Inicializando...", 0, 0);

   for (;;)
   {
      ADC10CTL0 |= ENC + ADC10SC;             //Activo e inicio la conversión

      __low_power_mode_0();//__bis_SR_register(CPUOFF + GIE);// LPM0, ADC10_ISR will force exit

      if (ADC10MEM > 511)
          P1OUT = 0b0001;                       //Temp. Alta, LED rojo ON
      else if (ADC10MEM > 170 && ADC10MEM < 511)
          P1OUT = 0b0010;                       //Temp. Media, LED verde ON
      else if (ADC10MEM < 170)
          P1OUT = 0b0100;                       //Temp. Baja, LED azul ON
      else
          P1OUT &= ~0b0111;                     //Si o si, todos OFF


      Temp_num = ADC10MEM;
      //Temp_num = Temp_num*(150/1023);
      Temp_num = Temp_num*(0.146627566);
      sprintf(Temp, "%d", Temp_num);
      strcat(Temp, "*C ");
      lcdSetText("Temperatura de:", 0, 0);
      lcdSetText(Temp, 0, 1);
   }
}

#pragma vector=ADC10_VECTOR                     //ADC10 interrupt service routine
__interrupt void ADC10_ISR(void)
{
   __low_power_mode_off_on_exit();              //Sale de interrupcion
}
