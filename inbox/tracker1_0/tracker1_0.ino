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
    Serial.println("turnL250");   
   delayMicroseconds(2);
  }
 else if(num2==0)       //第二个传感器检测到黑线用150的速度左转
 {
   Serial.println("turnL200");
   delayMicroseconds(2);
 }
  else if(num3==0)       //第三个传感器检测到黑线用150的速度左转
 {
   Serial.println("turnL150");
   delayMicroseconds(2);
 }
 
 else if(num5==0)       //第五个传感器检测到黑线用150的速度右转
 {
    Serial.println("turnR150");
   delayMicroseconds(2);
 }
 else if(num6==0)        //第六个传感器检测到黑线用200的速度右转
 {
    Serial.println("turnR200");
   delayMicroseconds(2);
 }
  else if(num7==0)        //第七个传感器检测到黑线用250的速度右转  
 {
    Serial.println("turnR250");
   delayMicroseconds(2);
 }
  else                     //其他状态小车直走
  {
    Serial.println("trunfoward180");
   delay(2);
  }
