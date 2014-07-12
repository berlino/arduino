int right_up=3;
int right_down=4;
int left_up=5;
int left_down=6;

void setup()
{
  pinMode(right_up,OUTPUT);
  pinMode(right_down,OUTPUT);
  pinMode(left_up,OUTPUT);
  pinMode(left_down,OUTPUT);
}

void loop()
{
  forward();
  while(1);
}

void forward()
{
  digitalWrite(right_up,1);
  digitalWrite(right_down,0);
  digitalWrite(left_up,1);
  digitalWrite(left_down,0);
}

void backward()
{
  digitalWrite(right_up,0);
  digitalWrite(right_down,1);
  digitalWrite(left_up,0);
  digitalWrite(left_down,1);
}

void turn_left()
{
  digitalWrite(right_up,1);
  digitalWrite(right_down,0);
  digitalWrite(left_up,0);
  digitalWrite(left_down,1);
}

void turn_right()
{
  digitalWrite(right_up,0);
  digitalWrite(right_down,1);
  digitalWrite(left_up,1);
  digitalWrite(left_down,0);
}
