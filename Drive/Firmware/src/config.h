#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

//ADC
#define SDA2 7
#define SCL2 6
#define ADC_CH2 ADS1X15_REG_CONFIG_MUX_SINGLE_2

//M1
#define I3 20
#define I4 18
#define EN2 19

//M2
#define I1 23
#define I2 21
#define EN1 20

//M3
#define I5 1
#define I6 5
#define EN3 0

//M4
#define I7 4
#define I8 2
#define EN4 3



#endif