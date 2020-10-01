#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	P2DIR |=0xFF;   //Defino los pines de salida (para display 8 segmentos)
	P1REN = BIT0;   P1REN = BIT1;   P1REN = BIT2;   P1REN = BIT3;   //Desabilitar resistencia pull-up para push button
	P2OUT = 0x00;   //Inicializo en cero
	
	for(;;)
	{
	    while((P1IN & 0x0F) == 0b00000000) {P2OUT = 0b00000000;}
	    while((P1IN & 0x0F) == 0b00000001) {P2OUT = 0b00000011;}
	    while((P1IN & 0x0F) == 0b00000010) {P2OUT = 0b00001100;}
	    while((P1IN & 0x0F) == 0b00000011) {P2OUT = 0b00110000;}
	    while((P1IN & 0x0F) == 0b00000100) {P2OUT = 0b00000100;}
	    while((P1IN & 0x0F) == 0b00000101) {P2OUT = 0b10101010;}
	    while((P1IN & 0x0F) == 0b00000110) {P2OUT = 0b11001100;}
	    while((P1IN & 0x0F) == 0b00000111) {P2OUT = 0b11000011;}
	    while((P1IN & 0x0F) == 0b00001000) {P2OUT = 0b00111100;}
	    while((P1IN & 0x0F) == 0b00001001) {P2OUT = 0b01010101;}
	    while((P1IN & 0x0F) == 0b00001010) {P2OUT = 0b00001111;}
	    while((P1IN & 0x0F) == 0b00001011) {P2OUT = 0b11110000;}
	    while((P1IN & 0x0F) == 0b00001100) {P2OUT = 0b11111111;}
	}
return 0;
}
