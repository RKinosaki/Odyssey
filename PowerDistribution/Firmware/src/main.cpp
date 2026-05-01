#include <Arduino.h>
#include <config.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <INA219_WE.h>


int fet[5] = {FET_MAIN, FET_ALPHA, FET_BETA, FET_GAMMA, FET_DELTA};
INA219_WE ina = INA219_WE(&Wire);
static int sampleIndex = 0;

float currentSamples[FILTER_SAMPLE_SIZE] = {};
float currentAverage = 0;

float shuntVoltage;
float busVoltage;
float current;
float offsetCurrent = 0;

void setup(){
  delay(2000);
  Serial.begin(115200);
  Wire.begin(SDA, SCL);
  for (int i = 0; i<sizeof(fet)/sizeof(fet[0]); i++){
    pinMode(fet[i], OUTPUT);
    digitalWrite(fet[i], HIGH);
    Serial.println("FET " + String(i) + " Opened");
  }

  if(!ina.init()){
    Serial.println("INA219 Initialisation Error!");
    while(1){}
  }
  ina.setShuntSizeInOhms(0.01);

  delay(500);
  if((ina.getBusVoltage_V()+ina.getShuntVoltage_mV()/1000)<0.05){
    offsetCurrent = ina.getCurrent_mA();
  }
  
}

void calculateNewAverageCurrent(){
  for (int i = 0; i < FILTER_SAMPLE_SIZE; i++){
    Serial.print(String(currentSamples[i]));
    if (i != FILTER_SAMPLE_SIZE-1){
      
    Serial.print(", ");
    }
  }
  Serial.println();
  float sampleSum = currentAverage*FILTER_SAMPLE_SIZE;                //Finds Σn
  float newSum = sampleSum - currentSamples[sampleIndex];             //Removes Oldest Sample from Σn
  currentSamples[sampleIndex] = ina.getCurrent_mA() - offsetCurrent;  //measures current amd repleaces the oldest sample
  newSum += currentSamples[sampleIndex];                              //Adds the new sample to Σn
  currentAverage = newSum/FILTER_SAMPLE_SIZE;                         //Finds new average
  sampleIndex = (sampleIndex+1) % FILTER_SAMPLE_SIZE;                 //Increments the index, wraps around at end
}

void loop(){
  calculateNewAverageCurrent();
  if(currentAverage>0.13){
    digitalWrite(FET_ALPHA, LOW);
    Serial.println("Emergeny Stop!");
  }
  shuntVoltage = ina.getShuntVoltage_mV();
  busVoltage = ina.getBusVoltage_V();
  Serial.print("Current is: ");
  Serial.print(String(currentAverage/1000));
  Serial.println("A");

  Serial.print("Voltage is: ");
  Serial.print(String(busVoltage + shuntVoltage/1000));
  Serial.println("V");
  delay(1000);
}