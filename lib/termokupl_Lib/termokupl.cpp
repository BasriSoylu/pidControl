#include "termokupl.h"




void termokupl_init(termokupl_t *termokupl, uint8_t CS, uint8_t SCK, uint8_t SO)
{
    termokupl->csPin = CS;
    termokupl->sckPin = SCK;
    termokupl->soPin = SO;


    pinMode(termokupl->csPin, OUTPUT);
    pinMode(termokupl->sckPin, OUTPUT);
    pinMode(termokupl->soPin, OUTPUT);
    digitalWrite(termokupl->csPin, HIGH);
}


byte spiRead(termokupl_t *termokupl)
{
    byte value = 0;

    for(int i = 7; i >= 0; i--)
    {
        digitalWrite(termokupl->sckPin, LOW);
        delayMicroseconds(10);

        if(digitalRead(termokupl->soPin))
        {
        value |= (1 << i);
        }

        digitalWrite(termokupl->sckPin, HIGH);
        delayMicroseconds(10);
    }

return value;
}





float readTermokuplValue(termokupl_t *termokupl)
{
    uint16_t value;

    digitalWrite(termokupl->csPin, LOW);
    delayMicroseconds(10);

    value = spiRead(termokupl);
    value <<= 8;
    value |= spiRead(termokupl);

    digitalWrite(termokupl->csPin, HIGH);

    if(value &0x04)
    {
        Serial.println("Termokupl Takili Değil!!!!");
        return NAN;
    }

    value >>= 3;

  return (value * 0.25);
}