#include <Arduino.h>
#include <IntervalTimer.h>

IntervalTimer myTimer;
volatile bool flag = false;
const int analogInPin = A6;  // Analog input pin that the potentiometer is attached to
int voltage_read;
float outputValue;
float frequency = 1;
float period = (1/ frequency)*10e6;
unsigned long timestamp;
bool trigger = false;


void setup() {
  Serial.begin(115200);
  while (!Serial);
  // Serial.println(period);
  pinMode(34, INPUT); // trigger from instron to sync data well
  myTimer.begin(dataFlag, 100);  // microseconds
  pinMode(33, OUTPUT);   // trigger pin for instron setup
}

void loop() {
  if (Serial.read() ==  '1' && trigger == false) {
    digitalWrite(33, HIGH);
    delay(1000);
    digitalWrite(33, LOW);
    if (digitalRead(34) == HIGH && !trigger) {
      
      Serial.println("GO");
      trigger = true;
    }
  }
  if (flag) {
    timestamp = micros();
    voltage_read = analogRead(analogInPin);
    outputValue = map(voltage_read, 0, 1023, 0, 3300);
    Serial.print(timestamp);
    Serial.print(",");
    Serial.println(outputValue); 
    flag = false;
  }
  if (Serial.read() == '2'){
    trigger = false;
  }
}

void dataFlag() {
  flag = true;
}
