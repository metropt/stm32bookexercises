#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "ST7735.h"
#include "glcdfont.c"

void fillScreen(uint16_t color);

int main(void)
{
    ST7735_init();
    while(1){
      
      fillScreen(WHITE);
      putChar('A',124,0,RED,WHITE);
      Delay(2000);
      
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

void putChar(uint16_t c, uint16_t x0, uint16_t y0, uint16_t color, uint16_t bg){
  uint8_t x,y,j=0;
  
  //starting point of char
  c *= 5;
  
  //array with the color of each pixel
  uint16_t temp[60];
  
  //set the position, use another madctl to easy draw the char
  ST7735_setAddrWindow(y0, x0, y0+9, x0+6, MADCTLCHAR);
  
  //for each array that made a char
  for(x=0; x<5; x++){
    //for each bit if set add color else add background color
    for(y=0; y<10; y++){
      if(ASCII[c+x] & (0x01 << y))
	temp[j] = color;
      else
	temp[j] = bg;
      j++;
    }
  }
  //last column
  for(x=0; x<10; x++){
    temp[j] = bg;
    j++;
  }
  //design
  ST7735_pushColor(temp, 60);
  
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  while(1);
}
#endif