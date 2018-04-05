const int rs_pin = 12;
const int en_pin = 11;
const int data_pin[] = {5,4,3,2};
int analog_in = A0;
int adcValue = 0;


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
  
  pinMode(analog_in,INPUT);
  
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
  sendLCD(0x80, false);
  //read analog value
  adcValue = analogRead(analog_in);
  
  sendLCD(0x53, true);
  sendLCD(0x45, true);
  sendLCD(0x4E, true);
  sendLCD(0x53, true);
  sendLCD(0x4F, true);
  sendLCD(0x52, true);
  sendLCD(0x3A, true);
  
  int div = 1000;
  int m = adcValue;
  for(int i=3;i>=0;i--)
  {
     int x = m/div;
     int dis = 0x30+x;
     sendLCD(dis, true);
     m = m%div;
     div = div/10;
  }
  
  sendLCD(0xC0, false);
  
  sendLCD(0x56, true);
  sendLCD(0x4F, true);
  sendLCD(0x4C, true);
  sendLCD(0x54, true);
  sendLCD(0x41, true);
  sendLCD(0x47, true);
  sendLCD(0x45, true);
  sendLCD(0x3A, true);
  
  
  int volt = (float)adcValue*500.00/1023.00;
  int e = volt/100;
  int f = (volt%100)/10;
  int g = volt%10;
  
  sendLCD(0x30+e, true);
  sendLCD(0x2E, true);
  
  sendLCD(0x30+f, true);
  sendLCD(0x30+g, true);

 delay(100);
}
