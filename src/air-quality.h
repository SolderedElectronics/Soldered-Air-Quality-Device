#include "Arduino.h"
#include "BME280-SOLDERED.h"
#include "CCS811-SOLDERED.h"
#include "LCD-SOLDERED.h"
#include "PMS7003-SOLDERED.h"
#include "SoftwareSerial.h"
#include "Wire.h"

// Device settings - Put 0 if you don't want to use these sensors
#define USE_PMS_SENSOR 1
#define USE_CCS_SENSOR 1

#define TEMP_OFFEST 0 // Set the temperature offset if you want to calibrate the sensor

#define BATTERY_FULL 970 // Analog read when the battery is fully charged
#define BATTERY_LOW  830 // Analog read when the battery is low

#define REFRESH_DATA_TIME 5000 // Refresh sensors readings every 5000 ms

// Rotary Encoder Inputs
#define clock            7  // Clock pin connected to D7
#define data             9  // Data pin connected to D9
#define rotaryEncoderBtn 10 // rotaryEncoderBtn button pin connected to D10

// PMS7003
#define PMS_RX 11 // RX pin of the MPS7003 for serial comunication
#define PMS_TX 12 // TX pin of the MPS7003 for serial comunication

#define ONBOARD_LED 8 // The pin on the Dasduino conected to the LED

#define BATTERY_MEASURE_PIN                                                                                            \
    0 // The pin on the Dasduino which is connected voltage divider for measuring battery voltage

class GUI
{
  public:
    GUI(LCD *lcd, BME280 *bme280, CCS_811 *ccs811Sensor, PMS7003 *pms, int *page, int *maxPage);
    void setPage(uint8_t page);
    void printBMEpage();
    void printCCSpage(void);
    void printPMSpage(uint8_t page);
    void insertNumbers(uint8_t page);
    void printBMEvalues(float temp, float hum, float pressure);
    void printCCSvalues(int ccsCO2, int ccsTVOC);
    void printPMSvalues(uint8_t pg, int pm1, int pm25, int pm10, int n0p3, int n0p5, int n1p0, int n2p5, int n5p0,
                        int n10p0);
    void insertPageNum(void);
    void pageMark(void);
    void printBatteryPercentage();
    void displayBegin(void);
    void BMEbegin(void);
    void CCSbegin(void);
    void PMSbegin(void);
    byte BMEavailable(void);

  protected:
  private:
    LCD *lcd;
    BME280 *bme280;
    CCS_811 *ccs811Sensor;
    PMS7003 *pms;
    int *page, *maxPage;
};
