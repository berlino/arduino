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
  Serial.begin(9600);
 }
void loop() 
{ 
  char num1,num2,num3,num4,num5,num6,num7;
  num1=digitalRead(8);    
  num2=digitalRead(9);
  num3=digitalRead(10);
  num4=digitalRead(11);
  num5=digitalRead(12);
  num6=digitalRead(2);
  num7=digitalRead(3);
                        // 用num1-7保存从左到右7个传感器的状态
  if(num1==0)          //第一个传感器检测到黑线用200的速度左转
  {
   turnL(250);   
   delayMicroseconds(2);
  }
 else if(num2==0)       //第二个传感器检测到黑线用150的速度左转
 {
   turnL(200);
   delayMicroseconds(2);
 }
  else if(num3==0)       //第三个传感器检测到黑线用150的速度左转
 {
   turnL(150);
   delayMicroseconds(2);
 }
 
 else if(num5==0)       //第五个传感器检测到黑线用150的速度右转
 {
    turnR(150);
   delayMicroseconds(2);
 }
 else if(num6==0)        //第六个传感器检测到黑线用200的速度右转
 {
    turnR(200);
   delayMicroseconds(2);
 }
  else if(num7==0)        //第七个传感器检测到黑线用250的速度右转  
 {
    turnR(250);
   delayMicroseconds(2);
 }
  else                     //其他状态小车直走
  {
   runfoward(180);
   delay(2);
  }
}
