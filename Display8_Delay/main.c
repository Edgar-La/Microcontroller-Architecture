#include <msp430.h>

void delay(int time_);      //Prototype delay function

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P2DIR |=0xFF;   //Defino los pines de salida (para display 8 segmentos)

	int i=0;
	int	OUTPUTS[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7F, 0x6F, 0x3F};
	
    for(;;) //Infinite loop
    {
        for (i=0; i<10; i++)
        {
            delay(3000);
            P2OUT = OUTPUTS[i];
        }
    }
	return 0;
}


int counter;
void delay(int time_)
{
    for (counter=1; counter<time_; counter++)
    {}
}
