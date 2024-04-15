#define red 7
#define blue 3
#define green 2
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  digitalWrite(red,HIGH);
  delay(100);
  digitalWrite(red,LOW);
  delay(100);
  
  digitalWrite(blue,HIGH);
  delay(100);
  digitalWrite(blue,LOW);
  delay(100);
  
  digitalWrite(green,HIGH);
  delay(100);
  digitalWrite(green,LOW);
}