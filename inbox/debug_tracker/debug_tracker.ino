/**********OJ 3 grey sensor***********/
/**********www.openjumper.com********/
int L1;
int L2;
int R1;
int R2;

  void setup() {
    Serial.begin(9600);
  }
  void loop() {
    L2= analogRead(A0);
    L1= analogRead(A1);
    R1 = analogRead(A2);
    R2 =analogRead(A3);
    
    Serial.print("L2=");
    Serial.print(L2);
    Serial.print(";");
    Serial.print("L1=");
    Serial.print(L1);
    Serial.print(";");
    Serial.print("R1=");
    Serial.print(R1);
    Serial.print(";");
    Serial.print("R2=");
    Serial.println(R2);
    delay(1000);
  }
