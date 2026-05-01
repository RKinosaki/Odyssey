#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

//FET PINS
#define FET_MAIN 1
#define FET_ALPHA 7
#define FET_BETA 8
#define FET_GAMMA 9
#define FET_DELTA 13

//I2C
#define SCL 11
#define SDA 12

//I2C Address
#define ADS_ADDR 0x48
#define INA_ADDR 0x40
#define LNA_ADDR 0X48

//IN219
#define FILTER_SAMPLE_SIZE  5

//ADC
#define ADC_PD_RATIO 0.15151515

#endif