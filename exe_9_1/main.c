#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_i2c.h>
#include "i2c.h"

uint8_t txbuf[4], rxbuf[4], demo[4]={1,2,3,4};
uint16_t txbuf16[4], rxbuf16[4];

int main(void)
{
    int i, j;

    I2C_LowLevel_Init(I2C1,100,12);
    
    for (i=0; i<4; i++) {
        I2C_Write(I2C1, demo, 4, 1);
    }
    
    return 0;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  while(1);
}
#endif
