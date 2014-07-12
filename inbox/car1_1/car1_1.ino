/*********For Minidriver Board**********************
  * attention  - to digital pin 6  (simulate SS pin)
    PB2        - PWM_R
  * command    - to digital pin 11 (MOSI pin)
  * data       - to digital pin 12 (MISO pin)
  * clock      - to digital pin 13 (SCK pin)
****************************************************/

#include "Constants.h"
#include "IOpins.h"
#include <SPI.h>

unsigned long steer,power,flip = 550;
unsigned long time;
int lspeed, rspeed;
byte input=0;

const int servoUp   = 2600;
const int servoDown = 550;
int templspeed = 200, temprspeed = 200;
const int slaveSelectPin = 6;
unsigned char PS2buf[10];
//unsigned char i;
unsigned char countsPushTime = 0;
unsigned char stepLength = 1;

void setup()
{
  pinMode(Ldirpin,OUTPUT);
  pinMode(Rdirpin,OUTPUT);
  pinMode(Srvopin,OUTPUT);
  //Serial.begin(9600);
  initSPI();
}

void loop()
{
  //Serial.print(rspeed);
  //Serial.print(" : ");
  //Serial.println(lspeed);
  if(millis()-time>17)
  {
    time=millis();
    digitalWrite(Srvopin,HIGH);
    delayMicroseconds(flip);
    digitalWrite(Srvopin,LOW);

    digitalWrite(Ldirpin,(lspeed>0));
    analogWrite (Lpwmpin,abs(lspeed));
    digitalWrite(Rdirpin,(rspeed>0));
    analogWrite (Rpwmpin,abs(rspeed));

    input++;
    if(input>2) input=0;
  }

  if(Get_PS2Dat(PS2buf))
  //for(i=0;i<9;i++)
  //{
  //  Serial.print(PS2buf[i]);
  //}
  //Serial.println();
  //delay(250);
  delay(10);

  if(!(PS2buf[4] & (~0x7f) )) //按键左
  {
    if(255 != abs(templspeed))
    {
      templspeed++;
    }
    if(255 != abs(temprspeed))
    {
      temprspeed++;
    }
  }
  
  if(!(PS2buf[4] & (~0xdf) )) //按键右
  {
    if(templspeed != -255)
    {
      templspeed--;
    }
    if(temprspeed != -255)
    {
      temprspeed--;
    }
  }
  
  if(PS2buf[3] == 255)
  {
    lspeed = 0;
    rspeed = 0;
  }else{
  lspeed = templspeed;
  rspeed = temprspeed;
  }

  if(!(PS2buf[3] & (~0xef) )) //方向键上
  {
    lspeed = abs(lspeed);
    rspeed = abs(rspeed);
  }
  if(!(PS2buf[3] & (~0xbf) )) //方向键下
  {
    lspeed = -abs(lspeed);
    rspeed = -abs(rspeed);
  }
  if(!(PS2buf[3] & (~0x7f) )) //方向键左
  {
    lspeed = -abs(lspeed);
    rspeed = +abs(rspeed);
  }
  if(!(PS2buf[3] & (~0xdf) )) //方向键右
  {
    lspeed = abs(lspeed);
    rspeed = -abs(rspeed);
  }

  //if(!(PS2buf[3] & (~0xfe) )) //SELECT键
  //if(!(PS2buf[3] & (~0xf7) )) //START键

  if(!(PS2buf[4] & (~0xef) )) //按键上
  {
    countsPushTime++;
    if(countsPushTime > 10)
      if(stepLength != 10)
        stepLength++;
    if(flip != servoUp)
      flip+=stepLength;
    if(flip > servoUp)
      flip = servoUp;
  }else if((PS2buf[4] & (~0xef)) && (PS2buf[4] & (~0xbf)))
  {
    countsPushTime = 0;
    stepLength = 1;
  }
  if(!(PS2buf[4] & (~0xbf) )) //按键下
  {
    countsPushTime++;
    if(countsPushTime > 10)
      if(stepLength != 10)
        stepLength++;
    if(flip != servoDown)
      flip-=stepLength;
    if(flip < servoDown)
      flip = servoDown;
  }else if((PS2buf[4] & (~0xef)) && (PS2buf[4] & (~0xbf)))
  {
    countsPushTime = 0;
    stepLength = 1;
  }

  if(abs(lspeed)<30) lspeed=0;
  if(abs(rspeed)<30) rspeed=0;
}

void initSPI()
{
  pinMode(slaveSelectPin,OUTPUT);
  digitalWrite(slaveSelectPin,HIGH);

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
  digitalWrite(slaveSelectPin,LOW);
  delayMicroseconds(15);
  buf[0]=PS2_RWByte(0x01);delayMicroseconds(15); //延时再读取
  buf[1]=PS2_RWByte(0x42);delayMicroseconds(15);
  buf[2]=PS2_RWByte(0x00);delayMicroseconds(15);
  buf[3]=PS2_RWByte(0x00);delayMicroseconds(15);
  buf[4]=PS2_RWByte(0x00);delayMicroseconds(15);
  buf[5]=PS2_RWByte(0x00);delayMicroseconds(15);
  buf[6]=PS2_RWByte(0x00);delayMicroseconds(15);
  buf[7]=PS2_RWByte(0x00);delayMicroseconds(15);
  buf[8]=PS2_RWByte(0x00);delayMicroseconds(15);
  digitalWrite(slaveSelectPin,HIGH);
  if((buf[0]==0xff)&&(buf[1]==0x41)&&(buf[2]==0x5a))  //成功，普通模式
  return 1;
  if((buf[0]==0xff)&&(buf[1]==0x73)&&(buf[2]==0x5a))  //成功，摇杆扩展模式
  return 2;
  return 0;
}
