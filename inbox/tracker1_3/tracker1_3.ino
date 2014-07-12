/**********OJ 3 grey sensor***********/
/**********www.openjumper.com********/
int L1;
int L2;
int R1;
int R2;
int sum;
#define left_up 5
#define left_down 3
#define right_up 9
#define right_down 6

int state=1;

void setup() {
    digitalWrite(2,HIGH);
    digitalWrite(4,HIGH);
    //Serial.begin(9600);
  }
void loop() {
    L2= digitalRead(10);
    L1= digitalRead(11);
    R1 = digitalRead(12);
    R2 =digitalRead(13);
    
    sum=L1+L2+R1+R2;
    if(sum>2)
    {
      //Serial.println("Stop");
      analogWrite(left_up,0);
      analogWrite(left_down,0);
      analogWrite(right_up,0);
      analogWrite(right_down,0);
      if(state==0)
      {
        while(1);
      }
      if(state==1)
      {
        analogWrite(left_up,100);
        analogWrite(left_down,0);
        analogWrite(right_up,0);
        analogWrite(right_down,100);
        delay(800);
      }
      if(state==2)
      {
        analogWrite(left_up,80);
        analogWrite(left_down,0);
        analogWrite(right_up,80);
        analogWrite(right_down,0);
        delay(100);
      }
    }
    if(sum==0)
    {
      //Serial.println("Go straight");
      analogWrite(left_up,80);
      analogWrite(left_down,0);
      analogWrite(right_up,80);
      analogWrite(right_down,0);
    }
    
    if(sum==1)
    {
      if(R2==1)
      {
        //Serial.println("Turn sharp left");
        analogWrite(left_up,80);
        analogWrite(left_down,0);
        analogWrite(right_up,0);
        analogWrite(right_down,0);
      }
      if(R1==1)
      {
        //Serial.println("Turn little left");
        analogWrite(left_up,60);
        analogWrite(left_down,0);
        analogWrite(right_up,0);
        analogWrite(right_down,0);
      }
      if(L2==1)
      {
        //Serial.println("Turn sharp right");
        analogWrite(right_up,80);
        analogWrite(right_down,0);
        analogWrite(left_up,0);
        analogWrite(left_down,0);
      }
      if(L1==1)
      {
        //Serial.println("Turn little right");
        analogWrite(right_up,60);
        analogWrite(right_down,0);
        analogWrite(left_up,0);
        analogWrite(left_down,0);
      }
    }
      
    delay(10);
  }
