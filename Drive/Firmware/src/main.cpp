#include <Arduino.h>
#include <config.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1015 ads;


void setup() {
  delay(5000);

  pinMode(I5, OUTPUT);
  pinMode(I6, OUTPUT);
  pinMode(EN3, OUTPUT);
  Serial.begin(9600);

  Wire.begin();
  Wire.setClock(10000);
  delay(100);
  if (!ads.begin(0x48, &Wire)){
    Serial.println("ADS not initialised");
  }
  ads.startADCReading(2, false);
}

void loop() {
  if (ads.conversionComplete()){
    int16_t results = ads.getLastConversionResults();
    Serial.print("Voltage: ");
    Serial.print(ads.computeVolts(results));
    Serial.println(" V");
    ads.startADCReading(2, false);
  }
  Serial.println("Going Forwards...");
  digitalWrite(I5, LOW);
  digitalWrite(I6, HIGH);
  for(int i = 0; i<255; i+=32){
    analogWrite(EN3, i);
    Serial.println(i);
    delay(500);
  }
  Serial.println("Going Backwards...");
  digitalWrite(I5, HIGH);
  digitalWrite(I6, LOW);
  for(int i = 0; i<255; i+=32){
    analogWrite(EN3, i);
    Serial.println(i);
    delay(500);
  }
}