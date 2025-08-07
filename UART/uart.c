#include<lpc21xx.h>
void uart0_config(void);
unsigned char uart0_rx(void);
void uart0_tx(unsigned char);
int main()
{
  unsigned char rxbyte;
  uart0_config();
  while(1){
  rxbyte=uart0_rx();
  rxbyte=rxbyte^32;
  uart0_tx(rxbyte);
	}
}
void uart0_config(void)
{
  PINSEL0=0X05;
  U0LCR=0X83;
  U0DLL=97;
  U0DLM=0;
  U0LCR=0X03;
}

void uart0_tx(unsigned char txbyte)
{
   while(((U0LSR>>5)&1)==0)
   U0THR=txbyte;
}
unsigned char uart0_rx(void)
{
 while((U0LSR&1)==0)
 return U0RBR;  
}




