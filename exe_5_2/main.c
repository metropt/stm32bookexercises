#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include "uart.h"

void Delay(uint32_t nTime);

int main(void)
{
  
  
  if(SysTick_Config(SystemCoreClock / 1000))
    while(1);
    
  uart_open(USART1,9600,0);
  
  char str[14] = "Hello World!\n\r";
  
  char buffer[100];
  __IO int count=0,i=0;
  
  while(1){
    
    //echo char
    //uart_putc(uart_getc(USART1),USART1);
    
    //echo line
    buffer[count]=uart_getc(USART1);
    count++;
    if(buffer[count-1]==0x0a){
      for(i=0;i<count;i++)
	uart_putc(buffer[i],USART1);
      count=0;
    }
    
  }
  
}

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime){
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void SysTick_Handler(void){
  if(TimingDelay != 0x00)
    TimingDelay--;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  while(1);
}
#endif