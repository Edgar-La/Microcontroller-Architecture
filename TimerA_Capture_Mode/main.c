#include <msp430.h>


volatile unsigned t1=0, t2=0, cuenta_0=0, cuenta_1=0, cuenta_2=0, repeticiones=0;
//volatile unsigned long F;
//volatile char *R15;
int main(void)
{
    volatile unsigned int tiempo1, tiempo2;
    //char *R15;
    //R15 = (char *)0x1080;

    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    P1DIR |= 0xFF;               //Configuro puerto 1 como salidas
    P1OUT = 0x0;                  //Inicializo todas las salidas de P1 en 0
    P2DIR = 0xFE;               //Configuro puerto 2 como salidas excepto el bit 0
    P2OUT = 0x0;                  //Inicializo todas las salidas de P2 en 0
    //P2IN = 0x01;
    //P2REN = BIT0;
    P2SEL|= 0b0001;                  //Asigna P2.0 al timerA1
    //P2IE = 0x01;                              // Activa interruptor en P1.3


    //Configuracion del canal 0 del TimerA1
    //Captura en ambos flancos, CCIA, captura sincronizada, Interrupcion activa, modo captura, interrupcion activa
    TA1CCTL0=(CM_3 + CCIS_0 + SCS + CAP + CCIE);

    //Control de registro del TIMERA1
    //MCLK, /2, modo continuo, borra el timer. Arranca el conteo
    TA1CTL|=(TASSEL_1 + ID0 + MC1 + TACLR); //REVISAR REGISTRO EN PROTEUS
    //TA1CTL|=(TASSEL_2 + MC_2 + TAIE); //REVISAR REGISTRO EN PROTEUS


    //No se puede entrar a LPM3 por que se necesita el reloj SMCLK
    __bis_SR_register(GIE); // Entra a modo LPM0 con interrupciones habilitadas


    while(1)
    {
        tiempo1 = t1;
        tiempo2 = t2;
        repeticiones = cuenta_2;
    }
}


#pragma vector = TIMER1_A0_VECTOR
__interrupt void captura0 (void)
{
    //R15 = (char *)0x1080;
    if((TA1CCTL0 & CCI)==0)//Es flanco de subida
    {
        t1=TA1CCR0;                         //Guardo el valor del timer al apretar boton
        P1OUT = 0b01;                       //Enciendo para verficar que oprimo
        cuenta_1 = cuenta_0;
        TA1CCTL0 &= ~CCIFG;               //Bajo la bandera
    }

    if((TA1CCTL0 & CCI)!=0) //flanco de bajada
    {
        t2 = TA1CCR0;                         //Guardo el valor del timer al soltar boton
        P1OUT = 0b00;                       //Apago para verficar que suelto
        //T = t2 - t1;
        cuenta_2 = cuenta_0 - cuenta_1;
        TA1CCTL0 &= ~(CCIFG);               //Bajo la bandera
        //*R15 = T;
    }

// __bic_SR_register_on_exit(LPM0_bits); // borra los bits del LPM0
//para que al salir sea en modo activo
}


#pragma vector = TIMER1_A1_VECTOR
__interrupt void t0captura0 (void)
{
    if(TA1IV == TA1IV_TAIFG)                //Utilizo vector de interrupcion con bandera
        cuenta_0++;                         //Para verficar las veces que se llena el over
}
