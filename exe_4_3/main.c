#include <stm32f10x.h>

int main(void)
{

  __IO int button;

  //enable clock
  RCC->APB2ENR |= 0x10 | 0x04;
  
  //configure button
  GPIOA->CRL = 0x04;

  //configure led
  GPIOC->CRH = 0x01;

  while(1){
    button = ((GPIOA->IDR & 0x01) == 1);
    if(button){
      GPIOC->BSRR = 1 << 8;
    }else{
      GPIOC->BSRR = 1 << 24;
    }
  }

}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  while(1);
}
#endif
