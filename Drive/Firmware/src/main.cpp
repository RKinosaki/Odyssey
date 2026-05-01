#include <Arduino.h>
#include <config.h>


void setup() {
  pinMode(I5, OUTPUT);
  pinMode(I6, OUTPUT);
  pinMode(EN4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Going Forwards...");
  digitalWrite(I5, LOW);
  digitalWrite(I6, HIGH);
  for(int i = 0; i<255; i+=32){
    analogWrite(EN4, i);
    Serial.println(i);
    delay(500);
  }
  Serial.println("Going Backwards...");
  digitalWrite(I5, HIGH);
  digitalWrite(I6, LOW);
  for(int i = 0; i<255; i+=32){
    analogWrite(EN4, i);
    Serial.println(i);
    delay(500);
  }
}