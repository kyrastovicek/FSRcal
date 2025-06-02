/*
Collecting voltage data

By: Kyra Stovicek
*/


#include <avr/interrupt.h>
#include <Arduino.h>
#include <math.h>
// User-defined settings

const int analogInPin = A6;  // Analog input pin that the potentiometer is attached to
int voltage_read;
float outputValue;


void setup() {
  // Configure Timer1 for periodic interrupts
  Serial.begin(115200);

}

void loop() {
  voltage_read = analogRead(analogInPin);
  
  outputValue = map(voltage_read, 0, 1023, 0, 3300);
  Serial.println(outputValue); 
}