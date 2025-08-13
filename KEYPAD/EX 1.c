#include<lpc21xx.h>
#define LCD 0xff
#define RS 1<<8
#define E 1<<9
void DELAY(int );
void init(void);
void DATA(unsigned char );
void COMMAND(unsigned char );
void str(unsigned char *);
void integer(int);


#define c0 (IOPIN0&(1<<20))
#define c1 (IOPIN0&(1<<21))
#define c2 (IOPIN0&(1<<22))
#define c3 (IOPIN0&(1<<23))
#define r0 1<<24
#define r1 1<<25
#define r2 1<<26
#define r3 1<<27
unsigned char key_lut[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
int keyscan(void);
int main()
{
 int res;
 init();
 str("4x4 keyboard");

while(1)
 {
  COMMAND(0X0C);
	res=keyscan();
  DATA((res/10)+48);
  DATA((res%10)+48);	 
 }
}
int keyscan(void)
{
 unsigned char row,col;	
 IODIR0=r0|r1|r2|r3;
 while(c0&c1&c2&c3==1);
 IOCLR0=r0|r1|r2|r3;
 //row0
 IOCLR0=r0;
 IOSET0=r1|r2|r3;
 while(c0&c1&c2&c3==0)
 {
  row=0;
	break; 
 }
 //row1
 IOCLR0=r1;
 IOSET0=r0|r2|r3;
 while(c0&c1&c2&c3==0)
 {
  row=1;
	break; 
 }	
 //row1
 IOCLR0=r2;
 IOSET0=r0|r1|r3;
 while(c0&c1&c2&c3==0)
 {
  row=2;
	break; 
 }	
 //row2
 IOCLR0=r3;
 IOSET0=r0|r1|r2;
 while(c0&c1&c2&c3==0)
 {
  row=3;
	break; 
 }
if(c0==0)
col=0;
else if(c1==0)
col=1;
else if(c2==0)
col=2;
else
col=3;
DELAY(100);

while(c0&c1&c2&c3==0);

return key_lut[row][col];
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
	IOSET0=A;
	IOCLR0=RS;
	IOSET0=E;
	DELAY(20);
	IOCLR0=E;
}
void DATA(unsigned char A)
{
	IOCLR0=LCD;
	IOSET0=A;
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
void integer(int n)
{
  unsigned char s[5];
	int i=0;
	
	if(n=='0')
	DATA(n);
	
	else if(n<0)
	{
		DATA('-');
		n=-n;
	}

  while(n>0)
	{
	 s[i++]=(n%10);
	 n=n/10;
	}
	
	for(--i;i>=0;i--)
	{
		DATA((s[i])+48);
	}
	
}

