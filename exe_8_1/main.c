#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_spi.h>
#include <stm32f10x_usart.h>

#include "xprintf.h"
#include "uart.h"
#include "ff.h"

FATFS Fatfs;
FIL Fil;
BYTE Buff[128];

void die(FRESULT rc){
  xprintf("Failed with rc=%u.\n",rc);
  for(;;);
}

void Delay(uint32_t nTime);

void myputchar(unsigned char c){
  uart_putc(c, USART1);
}

unsigned char mygetchar(){
  return uart_getc(USART1);
}

int main(void){

  FRESULT rc;
  UINT bw, br, i;
  
  if(SysTick_Config(SystemCoreClock / 1000))
    while(1);
    
  xfunc_in = mygetchar;
  xfunc_out = myputchar;
  
  uart_open(USART1,9600,0);

  f_mount(0, &Fatfs);

  xprintf("\nOpen an existing file (message.txt).\n");
  rc = f_open(&Fil, "MESSAGE.TXT", FA_READ);
  xprintf("\nresult:%u;\n",rc);

  if(!rc){
    xprintf("\nType the file content.\n");
    for(;;){
      rc = f_read(&Fil, Buff, sizeof Buff, &br);
      if(rc || !br)
        break;
      for(i=0; i<br; i++)
        myputchar(Buff[i]);
    }
    if (rc)
      die(rc);
    xprintf("\nClose the file.\n");
    rc=f_close(&Fil);
    if(rc)
      die(rc);
  }

  xprintf("\nCreate a new file (hello.txt).\n");
  rc = f_open(&Fil, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
  if(rc)
    die(rc);

  xprintf("\nWrite a text data. (Hello world!)\n");
  rc = f_write(&Fil, "Hello world!\r\n", 14, &bw);
  if(rc)
    die(rc);
  xprintf("%u bytes written.\n", bw);
  /*while(1){
    uart_putc('a',USART1);
    xputc('b');
    Delay(1000);
  }*/
}

DWORD get_fattime (){
  return 0;
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
