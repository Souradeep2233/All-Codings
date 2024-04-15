// Define pins for ultrasonic sensor
const int trigPin = 3;  // Trig pin of ultrasonic sensor
const int echoPin = 2; // Echo pin of ultrasonic sensor

// Define pin for buzzer
const int buzzerPin = 10; // Buzzer pin

// Variables for ultrasonic sensor
long duration;
int distance;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize buzzer pin
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigger pin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration from the echo pin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  // Print the distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check distance and activate buzzer if too close (e.g., less than 20 cm)
  if (distance < 20) {
    // Turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else {
    // Turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }

  // Delay before next reading
  delay(100); // Adjust delay as needed
}
