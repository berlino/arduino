#define right_up 9
#define left_up 10
#define left_1 2
#define left_2 3
#define right_1 5
#define right_2 4

char dir;
int num1,num2,num3,num4;

void setup() 
{
  //Serial.begin(9600);
  pinMode(right_up,OUTPUT);
  pinMode(left_up,OUTPUT);
  pinMode(left_1,INPUT);
  pinMode(left_2,INPUT);
  pinMode(right_1,INPUT);
  pinMode(right_2,INPUT);
  forward(100);
}

void loop() 
{  
  num1=digitalRead(2);
  num2=digitalRead(3);
  num3=digitalRead(4);
  num4=digitalRead(5);
  if(num1==1)
    turn_right(200);
  if(num2==1)
    turn_right(100);
  if(num3==1)
    turn_left(100);
  if(num4==1)
    turn_left(200);
}

void forward(int num)
{
  analogWrite(right_up,num);
  delay(100);
  //digitalWrite(right_down,0);
  analogWrite(left_up,num);
  //digitalWrite(left_down,0);
}


void turn_left(int num)
{
  digitalWrite(right_up,0);
  //digitalWrite(right_down,1);
  analogWrite(left_up,num);
  //digitalWrite(left_down,0);
}

void turn_right(int num)
{
  analogWrite(right_up,num);
  //digitalWrite(right_down,0);
  digitalWrite(left_up,0);
  //digitalWrite(left_down,1);
}

void stop_now()
{
  digitalWrite(right_up,0);
  //digitalWrite(right_down,1);
  digitalWrite(left_up,0);
  //digitalWrite(left_down,1);
}
