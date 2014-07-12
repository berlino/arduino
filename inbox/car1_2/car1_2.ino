#include<SPI.h>

#define right_up 5
#define right_down 4
#define left_up 6
#define left_down 7
#define cs 10

unsigned char i;
unsigned char PS2buf[10];
unsigned char result;

void setup()
{
  pinMode(right_up,OUTPUT);
  pinMode(right_down,OUTPUT);
  pinMode(left_up,OUTPUT);
  pinMode(left_down,OUTPUT);
  initSPI();
  Serial.begin(9600);
}

void loop()
{
  result=Get_PS2Dat(PS2buf);
  //Serial.println(result);
  if(result==1)
  {
    //for(i=0;i<9;i++)
    //{
      //Serial.print(PS2buf[i]);
    //}
    //Serial.println();
    
    delay(200);
    
      if(!(PS2buf[3] & (~0xef) )) //方向键上
     {
        //Serial.println("Arrow up");
        forward();
     }
     
      if(!(PS2buf[3] & (~0xbf) )) //方向键下
     {
        //Serial.println("Arrow down");
        backward();
     }  
     
      if(!(PS2buf[3] & (~0x7f) )) //方向键左
      {
        //Serial.println("Arrow left");
        turn_left();
      }
      
      if(!(PS2buf[3] & (~0xdf) )) //方向键右
      {
        //Serial.println("Arrow right");
        turn_right();
      }
       if(!(PS2buf[3] & (~0xfe) )) //SELECT键
       {
        stop_now();
       }
      
  }
  delay(20);    
}


void initSPI()
{
  pinMode(cs,OUTPUT);
  digitalWrite(cs,HIGH);

  SPI.begin();
  SPI.setBitOrder(LSBFIRST);               //LSBFIRST or MSBFIRST先发
  SPI.setDataMode(SPI_MODE3);              //CPOL=1 CPHA=1
  SPI.setClockDivider(SPI_CLOCK_DIV64);    //
  delay(20);
}

//-----SPI，一个字节的读写
unsigned char PS2_RWByte(unsigned char dat)
{
  SPI.transfer(dat);    //command SPDR=dat;
  //while(!(SPSR&0x80));  //读SPSR，判断是否发送/接受完成！
  return(SPDR);         //SPI.transfer(0x00);  //value
}
/*
至少需要20ms的间隔时间访问一次
 buf至少需要9个空间
 返回0,失败
 1：成功，普通模式
 2：成功，摇杆扩展模式
 */
unsigned char Get_PS2Dat(unsigned char *buf)
{
  unsigned char i;
  digitalWrite(cs,LOW);
  delayMicroseconds(15);
  buf[0]=PS2_RWByte(0x01);
  delayMicroseconds(15); //延时再读取
  buf[1]=PS2_RWByte(0x42);
  delayMicroseconds(15);
  buf[2]=PS2_RWByte(0x00);
  delayMicroseconds(15);
  buf[3]=PS2_RWByte(0x00);
  delayMicroseconds(15);
  buf[4]=PS2_RWByte(0x00);
  delayMicroseconds(15);
  buf[5]=PS2_RWByte(0x00);
  delayMicroseconds(15);
  buf[6]=PS2_RWByte(0x00);
  delayMicroseconds(15);
  buf[7]=PS2_RWByte(0x00);
  delayMicroseconds(15);
  buf[8]=PS2_RWByte(0x00);
  delayMicroseconds(15);
  digitalWrite(cs,HIGH);
  if((buf[0]==0xff)&&(buf[1]==0x41)&&(buf[2]==0x5a))  //成功，普通模式
    return 1;
  if((buf[0]==0xff)&&(buf[1]==0x73)&&(buf[2]==0x5a))  //成功，摇杆扩展模式
    return 2;
  return 0;
}

void forward()
{
  analogWrite(right_up,100);
  digitalWrite(right_down,0);
  analogWrite(left_up,100);
  digitalWrite(left_down,0);
}

void backward()
{
  digitalWrite(right_up,0);
  digitalWrite(right_down,1);
  digitalWrite(left_up,0);
  digitalWrite(left_down,1);
  delay(200);
  stop_now();
}

void turn_left()
{
  analogWrite(right_up,100);
  digitalWrite(right_down,0);
  digitalWrite(left_up,1);
  digitalWrite(left_down,1);
}

void turn_right()
{
  digitalWrite(right_up,1);
  digitalWrite(right_down,1);
  analogWrite(left_up,100);
  digitalWrite(left_down,0);
}

void stop_now()
{
  digitalWrite(right_up,1);
  digitalWrite(right_down,1);
  digitalWrite(left_up,1);
  digitalWrite(left_down,1);
}

