//Librerias
#include <msp430.h> 
#include "lcdLib.h"
#include <stdio.h>


volatile long valFromADC = 0;
volatile int valTemp;

void ADC10Init()
{
    //Confiuro el ADC10 para lectura del sensor de temperatura
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;// + ADC10IE;
    ADC10CTL1 = INCH_3 + SHS_0 + ADC10DIV_2 + ADC10SSEL_0 + CONSEQ_0;
    //ADC10CTL1 = INCH_3 + ADC10DIV_2 + ADC10SSEL_0 + CONSEQ_0;
    ADC10AE0 |= BIT3;
}

void tempInit()
{
    ADC10CTL0=SREF_1 + REFON + ADC10ON + ADC10SHT_3 ; //1.5V ref,Ref on,64 clocks for sample
    ADC10CTL1=INCH_9 + ADC10DIV_3; //temp sensor is at 10 and clock/4
}

void Edgar()
{
    ADC10CTL0 = 0b0100000000010000;          //Uso de referencia externa. Pongo ADC10 On
    ADC10CTL1 = 0b0000000000000000;          //Como todo. es cero puedo omitir linea, pero es para ser explicito
    ADC10AE0 |= 0b00010001;                  //Indico que PIN 0 y 1 son analogicos
                                                 //El PIN 0 es el que voy a samplear
}
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	//ADC10Init();
	//tempInit();
	Edgar();
	//P1SEL |= BIT0 + BIT3;
	//ADC10AE0 |= 0b00010001;


	//ADC10CTL0 |= ENC + ADC10SC;      //enable conversion and start conversion
int Temp_num;
char Temp[10];


//Inicio la pantalla lcd
	lcdInit();
	lcdSetText("Temperatura de:", 0, 0);



    for(;;)
    {
        ADC10CTL0 |= ENC + ADC10SC;
        /*
        valFromADC = ADC10MEM;
        valTemp = (valFromADC*1.5)/1023;
        */
        valTemp = ADC10MEM;

        //Temp_num = (ADC10MEM/1023)*150;
        //Temp_num = ADC10MEM * 0.146627566;
        //Temp_num = tempOut();
        //Temp_num = ADC10MEM;
        //Temp_num = ((Temp_num * 27069L - 18169625L)>>16);
        valTemp = ((valTemp * 27069L - 18169625L)>>16);
        sprintf(Temp, "%d", valTemp + 5);
        //gcvt(valTemp, 1, Temp);
        //if (Temp_num < 100)
        //lcdClear();
        //strcat(Temp, "*C");
        lcdSetText(Temp, 5, 1);
    }

}
