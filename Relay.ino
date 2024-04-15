int relayPin=6;
#define interval 2000 
void setup() {
pinMode(relayPin, OUTPUT);
}
void loop()
{
digitalWrite(relayPin, HIGH); delay(interval); digitalWrite(relayPin, LOW); delay(interval);
}