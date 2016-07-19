
#define RS485Transmit    HIGH
#define RS485Receive     LOW 
#define SLAVE   1

void setup() {
  // put your setup code here, to run once:

  pinMode(8, OUTPUT);
  digitalWrite(8, RS485Receive); //DE,RE=LOW, RX enabled
  Serial.begin (115200);   // TO MAX485
}

void loop() {
  // put your main code here, to run repeatedly:

  readCmd();

  /*
  int i;
  for (i=0; i<100; i++) {
    sendFeedback(i);
  }
  */
}

void readCmd()
{
 
  if (Serial.available() >= 4) 
  {
    char rT = (char)Serial.read(); //read target speed from mega
          if(rT == '{') //start byte
            {
              char commandArray[3];
              Serial.readBytes(commandArray,3);
              byte rA=commandArray[0]; //device address + command
              byte rH=commandArray[1]; //high byte
              char rP=commandArray[2]; //stop byte
              if(rP=='}' && rA==SLAVE)         
                {                 
                  sendFeedback(rH);
                }
            }
  }         
}

void sendFeedback(byte rH)
{
  digitalWrite(8, RS485Transmit); //DE,RE=HIGH, TX enabled

  char sT='{'; //send start byte
  byte sA = SLAVE;//address + command
  byte sH = rH;
  char sP= '}'; //send stop byte
  
  Serial.write(sT); 
  Serial.write(sA); 
  Serial.write(sH); 
  Serial.write(sP);
  delayMicroseconds(300);
  
  digitalWrite(8, RS485Receive); //DE,RE=LOW, RX enabled
}
