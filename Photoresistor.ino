#define reading A0
#define led 8
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int reading_data=analogRead(reading);
  if(reading_data<50)
  {digitalWrite(led,HIGH);delay(2);}
  Serial.println(reading_data);
}