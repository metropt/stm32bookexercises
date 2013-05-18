#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "eeprom.h"
#include "spi.h"


uint8_t txbuf[50], rxbuf[50];
uint16_t txbuf16[4], rxbuf16[4];

int main(void)
{
    int i, j;
    eepromInit();
    
    //for (i=0; i<8; i++) {
      for (j=0; j<34; j++)
	txbuf[j] = j;
      eepromWrite(txbuf, 30, 1000);
      //eepromWrite(txbuf, 32, 0);
      //eepromWrite(txbuf, 32, 32);
      eepromRead(rxbuf, 35, 1000);
      //GPIO_WriteBit(GPIOC, GPIO_Pin_10, 0);
      //spiReadWrite(SPI2, rxbuf, txbuf, 4, SPI_SLOW);
      //GPIO_WriteBit(GPIOC, GPIO_Pin_10, 1);
      //for (j=0; j<4; j++)
	//if (rxbuf[j] != txbuf[j])
	  //assert_failed(__FILE__, __LINE__);
    //}
    /*
    for (i=0; i<8; i++) {
      for (j=0; j<4; j++)
	txbuf16[j] = i*4 + j + (i<<8);
      GPIO_WriteBit(GPIOC, GPIO_Pin_10, 0);
      spiReadWrite16(SPI2, rxbuf16, txbuf16, 4, SPI_SLOW);
      GPIO_WriteBit(GPIOC, GPIO_Pin_10, 1);
      for (j=0; j<4; j++)
	if(rxbuf16[j] != txbuf16[j])
	  assert_failed(__FILE__, __LINE__);
    }*/
    
    return 0;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  while(1);
}
#endif