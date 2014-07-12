void setup() {
  system("telnetd -l /bin/sh");
  system("ifconfig eth0 > /dev/ttyGS0");
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
