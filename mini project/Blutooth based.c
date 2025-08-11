#include<lpc21xx.h>
#define LCD 0xff000
#define RS 1<<10
#define E 1<<11

void UART0_CONFIG(void)
{
 PINSEL0=0X5;
 U0LCR=0X83;
 U0DLL=97;
 U0DLM=0x03;
 U0LCR=0X03;	
}
unsigned char UART0_RX(void)
{
  
 while((U0LSR>>&1)==0);
 return U0RBR;
  
}

void str(unsigned char *s)
{
  while(*s)
  UART0_TX(*s++);		
}

void str(unsigned char *s)
{
	while(*s)
	{
		DATA(*s++);
	}
}
void init(void)
{
	IODIR0=LCD|RS|E;
	COMMAND(0X01);
	COMMAND(0X02);
	COMMAND(0X0C);
	COMMAND(0X38);
}
void COMMAND(unsigned char A)
{
	IOCLR0=LCD;
	IOSET0=(A)<<11;
	IOCLR0=RS;
	IOSET0=E;
	DELAY(20);
	IOCLR0=E;
}
void DATA(unsigned char A)
{
	IOCLR0=LCD;
	IOSET0=(A)<<11;
	IOSET0=RS;
	IOSET0=E;
	DELAY(20);
	IOCLR0=E;
}
void DELAY(int ms)
{
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}



void pwm(unsigned char n)
{

   PWMMR0=100000;
	 PINSEL1=0X0400; //pwm 5 port0.9  
   PINSEL0=0X100000; //PWM6 port0.21
switch(n)
{	
 case'f':
 COMMAND(0X01); 
 str("forword fast");	 
 PWMMR6=90000;
 PWMMR5=90000;
 PWMLER=0X020;
 break;
 
 case'm':
 COMMAND(0X01);	 
 str("midium");		 
 PWMMR6=40000;
 PWMMR5=40000;
 PWMLER=0X020;
 break;
 
 case's':
 COMMAND(0X01);	 
 str("stop");	 
 PWMMR6=10;
 PWMMR5=10;
 PWMLER=0X020;
 break;
}
}

int main()
{
  
	 unsigned char rxbyte;
   UART0_CONFIG();
	 rxbyte=UART0_RX();
	while(1)
	{
	 pwm(rxbyte);
	 init();
	 COMMAND(0X80);
	}  

}
