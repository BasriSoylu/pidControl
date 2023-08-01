#ifndef _TERMOKUPL_H
#define _TERMOKUPL_H
#include "inttypes.h"
#include <Arduino.h>

typedef struct 
{
    uint8_t csPin;
    uint8_t sckPin;
    uint8_t soPin;
}termokupl_t;


void termokupl_init(termokupl_t *termokupl, uint8_t CS, uint8_t SCK, uint8_t SO);
byte spiRead(termokupl_t *termokupl);
float readTermokuplValue(termokupl_t *termokupl);




#endif