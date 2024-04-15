#include<Servo.h>
Servo myservo; 
int pos=0;
void setup()
{
// put your setup code here, to run once: 
 myservo.attach(7);}//Attach signal chord to pin 7 (digital)
void loop() {
// put your main code here, to run repeatedly: 
 for(pos=0;pos<=180;pos++)
{
myservo.write(pos); delay (15);
}
delay (1000);
for (pos=180; pos>=0;pos--)
{
myservo.write (pos);

delay (15);
}
delay(1000);
}