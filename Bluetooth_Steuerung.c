
#include <reg51.h>

sbit LED=P1^0;

void UART_Init()
{
	TMOD = 0x20;		/* Timer 1, 8-bit auto reload mode */
	TH1 = 0xFD;		  /* 9600 baud rate */
	SCON = 0x50;		/* Mode 1, reception enable */
	TR1 = 1;		   
}

void UART_TxChar(char Data)
{
	SBUF = Data;
	while (TI==0);
	TI = 0;
}

char UART_RxChar()
{
	char dat;
	while (RI==0);
	RI = 0;
	dat = SBUF;
	return(dat);
}
	
void UART_SendString(char *str)
{
     int i;
     for(i=0;str[i]!=0;i++)
		{
         UART_TxChar(str[i]);
    }
}

void main()
{
	
	char Data_in;
	UART_Init();		
	P1 = 0;			
	LED = 0;		
	
	while(1)
	{
		Data_in = UART_RxChar();  
		if(Data_in == '1')
		{
			LED = 1;
			UART_SendString("LED_AN"); 
		}
		else if(Data_in == '2')
		{
			LED = 0;
			UART_SendString("LED_AUS"); 
		
		}
		else
			UART_SendString("Waehle richtige Option");
	}
	
}
