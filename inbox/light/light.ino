String content = "";
char character;
  
void setup()
{
  Serial.begin(9600);
}

void loop()
  {
    while(Serial.available())
  {
      character = Serial.read();
      content.concat(character);
      delay(10);
  }

  if (content != "") 
  {
      Serial.write(65);
     //Serial.println(content);
     //content="";
  }
  content="";
}
