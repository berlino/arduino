#include <TimerOne.h>

#define TX 13
int busy=0; //0 for no data ,1 for data
int state=0;//0 for the first period ,1 for the second period

int data[]={0,1,0,1,0,0,1,1};
int pointer=0;
#define LENGTH 8

void setup() 
{
  pinMode(TX, OUTPUT);    
  
  Timer1.initialize(50); 
  Timer1.attachInterrupt( timerIsr ); 
}
 
void loop()
{
}
void timerIsr()
{
    if(busy==1)
    {
      if((state==0 && data[pointer]==0)||( state==1 && data[pointer]==1))
      {
        digitalWrite(TX,HIGH);
      }
      if((state==0 && data[pointer]==1) || (state==1 && data[pointer]==0))
      {
        digitalWrite(TX,LOW);
      }
    }
    else
    {
      digitalWrite(TX,LOW);
    }
    state=(state+1)%2;
    pointer=(pointer+1)%LENGTH;
}
