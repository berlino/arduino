#include<Manchester.h>

#define TX_PIN 13

uint8_t moo = 1;
void setup()
{
  man.setupTransmit(TX_PIN,MAN_1200);
}

void loop()
{
  man.transmit(moo);
  moo=++moo%2;
}
