#include <stm32f10x.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#include "eeprom.h"
#include "spi.h"

#define EEPROM_PORT GPIOC
#define EEPROM_CS GPIO_Pin_10
#define EEPROM_SPEED SPI_SLOW
#define EEPROM_SPI SPI2

#define WIP(x) ((x) & 1)

void eepromInit(){
  spiInit(SPI2);
  
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin=EEPROM_CS;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(EEPROM_PORT,&GPIO_InitStructure);
  
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 1); 
}

void eepromWriteEnable(){
  uint8_t cmd = cmdWREN;
  
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 0);
  spiReadWrite(EEPROM_SPI, 0, &cmd, 1, EEPROM_SPEED);
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 1);
}

void eepromWriteDisable(){
  uint8_t cmd = cmdWRDI;
  
  while (WIP(eepromReadStatus()));
  
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 0);
  spiReadWrite(EEPROM_SPI, 0, &cmd, 1, EEPROM_SPEED);
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 1);
}

uint8_t eepromReadStatus(){
  uint8_t cmd[] = {cmdRDSR, 0xff};
  uint8_t res[2];
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 0);
  spiReadWrite(EEPROM_SPI, res, cmd, 2, EEPROM_SPEED);
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 1);
  return res[1];
}

void eepromWriteStatus(uint8_t status){
  uint8_t cmd[] = {cmdWRSR, status};
  
  while (WIP(eepromReadStatus()));
  
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 0);
  spiReadWrite(EEPROM_SPI, 0, cmd, 2, EEPROM_SPEED);
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 1);
}

int eepromWrite(uint8_t *buf, uint8_t cnt, uint16_t offset){
  uint8_t cmd[] = {cmdWRITE};
  
  if(cnt > (0x20 - (0x1f & offset)))
    cnt = 0x20 - (0x1f & offset);
    
  while (WIP(eepromReadStatus()));
  
  eepromWriteEnable();
  
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 0);
  spiReadWrite(EEPROM_SPI, 0, cmd, 1, EEPROM_SPEED);
  spiReadWrite16(EEPROM_SPI, 0, &offset, 1, EEPROM_SPEED);
  spiReadWrite(EEPROM_SPI, 0, buf, cnt, EEPROM_SPEED);
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 1);
  
  return cnt;
}

int eepromRead(uint8_t *buf, uint8_t cnt, uint16_t offset){
  uint8_t cmd[] = {cmdREAD};
  
  while (WIP(eepromReadStatus()));
  
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 0);
  spiReadWrite(EEPROM_SPI, 0, cmd, 1, EEPROM_SPEED);
  spiReadWrite16(EEPROM_SPI, 0, &offset, 1, EEPROM_SPEED);
  spiReadWrite(EEPROM_SPI, buf, 0, cnt, EEPROM_SPEED);
  GPIO_WriteBit(EEPROM_PORT, EEPROM_CS, 1);
  
  return cnt;
}