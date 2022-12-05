/**
 ***************************************************
 *
 * @file        settings.h
 * 
 * @brief       Settings for the device
 * 
 * @copyright   GNU General Public License v3.0
 * 
 * @author      Karlo Leksic for Soldered.com
 * 
****************************************************/

// Sensors settings - Put 0 if you won't to use these sensors
#define USE_PMS_SENSOR 1 // This variable decides the usage of the PMS7003 sensor
#define USE_CCS_SENSOR 1 // This variable decides the usage of the CCS811 sensor

#define TEMP_OFFEST 0 // Set the temperature offset if you want to calibrate the sensor

#define BATTERY_FULL 970 // Analog read when the battery is fully charged
#define BATTERY_LOW  700 // Analog read when the battery is low

#define BATTERY_R1 10000 // The resistor 1 on the voltage divider for measure battery voltage in Ohms
#define BATTERY_R2 3300  // The resistor 2 on the viltage divider for measure battery voltage in Ohms

// Battery measuring enable - if you won't measure the battery, put 0 
#define MEASURING_BATTERY_VOLTAGE 1

// The pin on the Dasduino which is connected voltage divider for measuring battery voltage
#define BATTERY_MEASURE_PIN A0

#define REFRESH_DATA_TIME 5000 // Refresh sensors readings every 5000 ms

// Rotary Encoder Inputs
#define ROTARY_CLOCK_PIN  7  // Clock pin connected to D7
#define ROTARY_DATA_PIN   9  // Data pin connected to D9
#define ROTARY_BUTTON_PIN 10 // rotaryEncoderBtn button pin connected to D10

// PMS7003
#define PMS_RX 11 // RX pin of the MPS7003 for serial comunication
#define PMS_TX 12 // TX pin of the MPS7003 for serial comunication
