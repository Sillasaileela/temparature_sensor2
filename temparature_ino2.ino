#include<arduino.h>
const int sensorPin = A0; // LM35 sensor connected to analog pin A0
const int ledPin = 13;    // Onboard LED connected to digital pin 13

unsigned long previousMillis = 0; // Variable to store time
const long intervalLowTemp = 250; // Blink interval for low temperature (below 30 degrees)
const long intervalHighTemp = 500; // Blink interval for high temperature (above 30 degrees)
int temperature; // To store temperature readings

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time
  
  temperature = getTemperature(); // Read temperature
  
  if (temperature < 30) {
    if (currentMillis - previousMillis >= intervalLowTemp) {
      previousMillis = currentMillis; // Save the current time
      digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle LED state
    }
  } else {
    if (currentMillis - previousMillis >= intervalHighTemp) {
      previousMillis = currentMillis; // Save the current time
      digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle LED state
    }
  }
}

int getTemperature() {
  int sensorValue = analogRead(sensorPin); // Read sensor value
  float voltage = (sensorValue / 1023.0) * 5.0; // Convert to voltage (0 to 5V)
  float temperatureC = (voltage - 0.5) * 100.0; // Convert voltage to temperature in Celsius
  return (int)temperatureC; // Return temperature
}
