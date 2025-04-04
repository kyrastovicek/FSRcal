/*
Collecting voltage data

By: Kyra Stovicek
*/


#include <avr/interrupt.h>
#include <Arduino.h>
#include <math.h>
// User-defined settings

const int analogInPin = A5;  // Analog input pin that the potentiometer is attached to
int voltage_read;
float outputValue;

const int targetFrequency = 1000;  // Desired sampling frequency (Hz)
// Calculate Timer1 interrupt frequency
const int timerFrequency = targetFrequency; // Timer frequency
const int OCR1A_value = (16000000 / (8 * timerFrequency)) - 1; // Timer match value
void setup() {
  // Configure Timer1 for periodic interrupts
  Serial.begin(115200);
  TCCR1A = 0;  
  TCCR1B = (1 << WGM12) | (1 << CS11); // CTC mode, prescaler = 8
  OCR1A = OCR1A_value; // Set interrupt interval
  TIMSK1 = (1 << OCIE1A); // Enable Timer1 interrupt
  sei(); // Enable global interrupts
}
// Timer1 Interrupt Service Routine (runs at 'timerFrequency' Hz)
ISR(TIMER1_COMPA_vect) {
 voltage_read = analogRead(analogInPin);
  
  outputValue = map(voltage_read, 0, 1023, 0, 3.3);
  Serial.println(outputValue); 
}
void loop() {
  // Nothing needed here, everything is handled in the interrupt
}