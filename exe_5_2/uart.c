#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include "uart.h"

int uart_open(USART_TypeDef* USARTx, uint32_t baud, uint32_t flags){
  
  USART_InitTypeDef USART_InitStructure; 
  GPIO_InitTypeDef GPIO_InitStructureTx; 
  GPIO_InitTypeDef GPIO_InitStructureRx;
  
  assert_param(IS_USART_123_PERIPH(USARTx));
  
  if (USARTx == USART1) {
  
    // Turn on clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
    
    //configure USART Tx
    GPIO_InitStructureTx.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructureTx.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructureTx.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructureTx);
    
    //configure USART Rx
    GPIO_InitStructureRx.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructureRx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructureRx);
    
    //Configure USART
    USART_StructInit (& USART_InitStructure );
    USART_InitStructure.USART_BaudRate = baud;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1,&USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
    
    return 0;
  } 
}

int uart_close(USART_TypeDef* USARTx){
  assert_param(IS_USART_123_PERIPH(USARTx));
}

int uart_putc(int c, USART_TypeDef* USARTx){
  assert_param(IS_USART_123_PERIPH(USARTx));

  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
  USART1->DR = (c & 0xff);
  return 0;
}

int uart_getc(USART_TypeDef* USARTx){
  assert_param(IS_USART_123_PERIPH(USARTx));
  
  while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
  return USARTx->DR & 0xff;
}