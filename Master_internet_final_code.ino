#include <Wire.h>
#include <DHT11.h>
#include <WiFi.h>
#include <ThingSpeak.h> // Include the ThingSpeak library

// WiFi credentials
const char* ssid = "Rick_X7Max";
const char* password = "umdu7901";

// ThingSpeak credentials
const unsigned long channelID = 2499092; // Replace with your ThingSpeak channel ID
const char* apiKey = "Y3IYOZ4LZNYLMJ3J"; // Replace with your ThingSpeak API Key

// Define analog pin for MQ-7 sensor
const int mq7Pin = 34;
// Define analog pin for MQ135 sensor
const int mq135Pin = 35;

// Create an instance of the DHT11 class.
DHT11 dht11(27);

// Define calibration values for MQ135 sensor for different gases (adjust based on sensor calibration)
const float ammoniaRo = 0.055;    // Ro value for Ammonia (NH₃)
const float benzeneRo = 0.035;     // Ro value for Benzene (C₆H₆)
const float co2Ro = 2.8;           // Ro value for Carbon Dioxide (CO₂)

WiFiClient client; // WiFi client object

void setup() {
  Serial.begin(9600); // Initialize serial communication

  // Connect to WiFi
  connectWiFi();

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Read MQ-7 sensor value
  int mq7SensorValue = analogRead(mq7Pin);
  float coConcentration = analogToPPM(mq7SensorValue);

  // Read MQ135 sensor value and calculate gas concentrations
  int mq135SensorValue = analogRead(mq135Pin);
  float ammoniaConcentration = calculateGasConcentration(ammoniaRo, mq135SensorValue);
  float benzeneConcentration = calculateGasConcentration(benzeneRo, mq135SensorValue);
  float co2Concentration = calculateGasConcentration(co2Ro, mq135SensorValue)/10;

  // Read DHT11 temperature and humidity values
  int temperature = 0;
  int humidity = 0;
  int dhtResult = dht11.readTemperatureHumidity(temperature, humidity);

  // Print sensor readings to serial monitor
  Serial.print("CO Concentration: ");
  Serial.print(coConcentration);
  Serial.println(" ppm");

  Serial.print("Ammonia Concentration: ");
  Serial.print(ammoniaConcentration);
  Serial.print(" ppm, Benzene Concentration: ");
  Serial.print(benzeneConcentration);
  Serial.print(" ppm, Carbon Dioxide (CO2) Concentration: ");
  Serial.print(co2Concentration);
  Serial.println(" ppm");

  if (dhtResult == 0) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\tHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println(DHT11::getErrorString(dhtResult));
  }

  // Update ThingSpeak channel with sensor data
  ThingSpeak.writeField(channelID, 3, coConcentration, apiKey); // Field 1: CO Concentration (ppm)
  ThingSpeak.writeField(channelID, 1, temperature, apiKey);     // Field 2: Temperature (°C)
  ThingSpeak.writeField(channelID, 2, humidity, apiKey); 
  ThingSpeak.writeField(channelID, 4, co2Concentration, apiKey); 
  ThingSpeak.writeField(channelID, 5 ,ammoniaConcentration, apiKey); 
  ThingSpeak.writeField(channelID, 6 ,benzeneConcentration, apiKey);     // Field 3: Humidity (%)

  // Wait for a few seconds before next reading
  delay(1000); // Adjust delay as needed
}

// Function to connect to WiFi
void connectWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
}

// Function to convert analog value to CO concentration in ppm (example calibration)
float analogToPPM(int sensorValue) {
  // Map sensor value (0-1023) to CO concentration (0-1000 ppm)
  float ppm = 1.02 * sensorValue / 1023.0;
  return ppm;
}

// Function to calculate gas concentration (ppm) based on Ro/Rs ratio for MQ135 sensor
float calculateGasConcentration(float ro, int sensorValue) {
  // Calculate Rs/Ro ratio
  float rsRoRatio = ((sensorValue * ro) / 1023.0) - ro;
  
  // Use an empirical formula to calculate gas concentration in ppm
  return pow(10, 1.01 * rsRoRatio);
}
