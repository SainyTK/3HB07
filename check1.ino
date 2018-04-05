const int rs_pin = 12;
const int en_pin = 11;
const int data_pin[] = {5,4,3,2};

void write4bits(int value)
{
  delayMicroseconds(1);
  digitalWrite(en_pin,HIGH);
  
  for(int i=0;i<4;i++)
    digitalWrite(data_pin[i],(value >> i) & 1); 
  
  delayMicroseconds(1);
  digitalWrite(en_pin,LOW);
  
  delayMicroseconds(100);
}

void sendLCD(int value, bool isData)
{
  if(isData) 
    digitalWrite(rs_pin,HIGH);
  else 
    digitalWrite(rs_pin,LOW);
  
  delayMicroseconds(1);
  
  write4bits(value >> 4);
  write4bits(value);
}

void setupLCD()
{
  pinMode(rs_pin,OUTPUT);
  pinMode(en_pin,OUTPUT);
  
  for(int i=0 ; i<4 ; i++)
    pinMode(data_pin[i],OUTPUT);
    
  digitalWrite(rs_pin,LOW);
  digitalWrite(en_pin,LOW);
  
  delay(80);
  write4bits(0x03);
  delay(5);
  write4bits(0x03);
  delay(5);
  write4bits(0x03);
  delay(5);
  write4bits(0x02);
  delay(5);
  
  sendLCD(0x28, false);
  sendLCD(0x06, false);
  sendLCD(0x0F, false);
  sendLCD(0x01, false);
  delay(10);
}

void setup()
{
  setupLCD();
}

void loop()
{
  //tanakorn
  sendLCD(0x54, true); //t
  sendLCD(0x41, true); //a
  sendLCD(0x4E, true); //n
  sendLCD(0x41, true); //a
  sendLCD(0x4B, true); //k
  sendLCD(0x4F, true); //o
  sendLCD(0x52, true); //r
  sendLCD(0x4E, true); //n
  sendLCD(0x3A, true); //:
  //048
  sendLCD(0x30, true); //0
  sendLCD(0x34, true); //4
  sendLCD(0x38, true); //8
  
  sendLCD(0xC0, false); //new line
  
  //masran
  sendLCD(0x4D, true); //m
  sendLCD(0x41, true); //a
  sendLCD(0x53, true); //s
  sendLCD(0x52, true); //r
  sendLCD(0x41, true); //a
  sendLCD(0x4E, true); //n
  sendLCD(0x3A, true); //:
  //083
  sendLCD(0x30, true); //0
  sendLCD(0x38, true); //8
  sendLCD(0x33, true); //3
  
  while(1);
}
