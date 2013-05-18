#ifndef EEPROM_H
#define EEPROM_H

enum eepromCMD { cmdREAD = 0x03, cmdWRITE = 0x02, cmdWREN = 0x06, cmdWRDI = 0x04, cmdRDSR = 0x05, cmdWRSR = 0x01 };

void eepromInit();
void eepromWriteEnable();
void eepromWriteDisable();
uint8_t eepromReadStatus();
void eepromWriteStatus(uint8_t status);
int eepromWrite(uint8_t *buf, uint8_t cnt, uint16_t offset);
int eepromRead(uint8_t *buf, uint8_t cnt, uint16_t offset);

#endif 
