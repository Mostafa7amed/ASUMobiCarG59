const int LED =13;
const int Pushbutton =2;
int val;
void setup()
{
pinMode(LED,OUTPUT);
pinMode(Pushbutton,INPUT);  
}
void loop()
{
  val= digitalRead(Pushbutton);
if(val ==HIGH)
{
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  delay(1000); 
}
else { digitalWrite(LED,LOW);}
}

