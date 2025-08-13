// lcd switch pressing 1st switch pressed
// 2nd switch pressed
// both switch pressed
//no input

#include<lpc21xx.h>
#define LCD 0xff
#define RS 1<<8
#define E 1<<9
#define LED1 1<<24
#define LED2 1<<25
#define sw1 10
void init(void);
void str(unsigned char *);
void DELAY(int );
void DATA(unsigned char );
void COMMAND(unsigned char );
int main()
{
 init();
 IODIR0=LED1|LED2;	
 COMMAND(0X80);	
while(1){
	if(((IOPIN0 >> sw1)& 1) == 0)
 {
 IOSET0=LED1;	 
 str("SWITCH 1 PRESSED");
 }
 else
	 IOSET0=LED1;
 }
	
 /*else if(((IOPIN0>>sw1)==0)&&((IOPIN0>>sw2)==0))
  str("BOTH PRESSED");

 else if((IOPIN0>>sw2)==0)
  str("SWITCH 2 PRESSED");
 
 else
  str("NO INPUT");
}*/
}
void init(void)
{
  IODIR0=LCD|RS|E;
  COMMAND(0X01);
	COMMAND(0X02);
	COMMAND(0X0C);
	COMMAND(0X38);
}
void COMMAND(unsigned char CMD)
{
  IOCLR0=LCD;
	IOSET0=CMD;
	IOCLR0=RS;
	IOSET0=E;
	DELAY(20);
	IOCLR0=E;
	
}
void DATA(unsigned char D)
{
  IOCLR0=LCD;
	IOSET0=D;
	IOSET0=RS;
	IOSET0=E;
	DELAY(20);
	IOCLR0=E;
	
}
void DELAY(int ms)
{
 T0PR=15000-1;
 T0TCR=0X01;
 while(T0TC<ms);
 T0TCR=0X03;
 T0TCR=0X00;	
}
void str(unsigned char*s)
{
  while(*s)
  DATA(*s++);
}
