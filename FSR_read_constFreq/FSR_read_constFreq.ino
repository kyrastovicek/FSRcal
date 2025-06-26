/* Code to synchronize instron and FSR data collection
  You can change the sampling rate using the 2nd input in the myTimer.begin function
    Inputs: 34, Instron read
            A6, FSR read
    Outputs:
            33, Trigger Instron
            36, Light that Instron info was received
            37, Light that trigger was sent to Instron

    Written by Kyra Stovicek, kcs8@rice.edu            
*/

#include <Arduino.h>
#include <IntervalTimer.h>

IntervalTimer myTimer;
volatile bool flag = false;
const int analogInPin = A6;  // Analog input pin that the potentiometer is attached to
int voltage_read;
float outputValue;
float frequency = 1;
float period = (1 / frequency) * 10e6;
unsigned long timestamp;
bool trigger = false;


void setup() {
  Serial.begin(115200);
  // Serial.println(period);
  pinMode(34, INPUT);   // trigger from instron to sync data well
  pinMode(33, OUTPUT);  // trigger pin for instron setup
  trigger = false;
  pinMode(36, OUTPUT);  // got info from instron
  pinMode(37, OUTPUT);  // high low status of trigger pin for instron (Dout)
  digitalWrite(33, LOW);
  digitalWrite(37, LOW);
}

void loop() {
  int incomingByte = Serial.read();
  // Serial.println(incomingByte);

  if (digitalRead(34) == HIGH && !trigger) {
    digitalWrite(36, HIGH);
    Serial.println("GO");
    delay(1000);
    trigger = true;
    myTimer.begin(dataFlag, 100);  // microseconds
  } else if (digitalRead(34) == LOW && trigger) {
    flag = false;
    trigger = false;
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
}


void dataFlag() {
  flag = true;
}
