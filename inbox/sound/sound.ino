uint8_t bytes[]={0xFD,0x00,0x06,0x01,0x00,0xC4,0xE3,0xBA,0xC3};
char buffer;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  //Serial.println("Start:");
  if(Serial.available()>0)
  {
    buffer=Serial.read();
    Serial.println(buffer);
    delay(100);
    if(buffer=='J')
    {
      Serial.write(bytes,sizeof(bytes));
      delay(100);
      if(Serial.available()>0)
      {
        buffer=Serial.read();
        Serial.print(buffer);
      }
      if(Serial.available()>0)
      {
        buffer=Serial.read();
        Serial.print(buffer);
      }
    }
  }
  delay(1000);
}

