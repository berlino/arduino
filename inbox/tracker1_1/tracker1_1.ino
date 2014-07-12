void motor(char pin,char pwmpin,char state,int val)
{
    pinMode(pin, OUTPUT);   
 
  if(state==1)
  {  
    analogWrite(pwmpin,val);
    digitalWrite(pin,1);
   }
  else if(state==2)
 {  
   analogWrite(pwmpin,val);
   digitalWrite(pin,0);
 }
 else if(state==0)
 {
    analogWrite(pwmpin,0);
    digitalWrite(pin,0);
 }
}
 
void runfoward(int i)   //前进
{
  motor(4,5,1,i);
  motor(7,6,1,i);
}
void runback(int j)    //后退
{
   motor(4,5,2,j);
   motor(7,6,2,j); 
}
void turnL(int m)     //左转
{
  motor(4,5,1,m);
  motor(7,6,0,m);
}
void turnR(int n)      //右转 
{
  motor(4,5,0,n);
  motor(7,6,1,n);
}
void stop()            //停止
{
  motor(4,5,0,0);
  motor(7,6,1,0); 
}
void setup()
{
}
void loop()
{
   runfoward(180); 
   delay(1000);
   runback(180);
   delay(1000);
   turnL(180);
   delay(1000);
   turnR(180);
   delay(1000);
}
