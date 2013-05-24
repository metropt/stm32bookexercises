#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "ST7735.h"

void fillScreen(uint16_t color);

int main(void)
{
    ST7735_init();
    while(1){
      
      fillScreen(RED);
      Delay(1000);
      fillScreen(GREEN);
      Delay(1000);
      fillScreen(BLUE);
      Delay(1000);
      
    }
    return 0;
}

void fillScreen(uint16_t color){
  uint8_t x,y;
  ST7735_setAddrWindow(0, 0, ST7735_width-1, ST7735_height-1, MADCTLGRAPHICS);
  for(x=0; x<ST7735_width; x++){
    for(y=0; y<ST7735_height; y++){
      ST7735_pushColor(&color, 1);
    }
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  while(1);
}
#endif