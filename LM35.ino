#define reading A5
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  int reading_data=analogRead(reading);
  Serial.println(reading_data*.5);
}