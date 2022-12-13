/**
 ***************************************************
 *
 * @file        gui.h
 *
 * @brief       Header file for GUI class
 *
 * @copyright   GNU General Public License v3.0
 *
 * @author      Karlo Leksic for Soldered.com
 *
 ****************************************************/
#include "Arduino.h"
#include "BME680-SOLDERED.h"
#include "CCS811-SOLDERED.h"
#include "LCD-SOLDERED.h"
#include "PMS7003-SOLDERED.h"
#include "SoftwareSerial.h"
#include "Wire.h"

#ifndef __GUI_H__
#define __GUI_H__

class GUI
{
  public:
    GUI(LCD *lcd, BME680 *bme680, CCS_811 *ccs811Sensor, PMS7003 *pms, int *page, int *maxPage);
    void setPage(uint8_t page);
    void printBMEpage();
    void printCCSpage(void);
    void printPMSpage(uint8_t page);
    void insertNumbers(uint8_t page);
    void readBME();
    void readCCS();
    void readPMS();
    void readSensors();
    void printBMEvalues();
    void printCCSvalues();
    void printPMSvalues(uint8_t pg);
    void insertPageNum(void);
    void pageMark(void);
    void printBatteryPercentage();
    void displayBegin(void);
    void BMEbegin(void);
    void CCSbegin(void);
    void PMSbegin(void);
    byte BMEavailable();

  protected:
  private:
    LCD *lcd;              // Pointer to LCD screen objest
    BME680 *bme680;        // Pointer to BME680 sensor
    CCS_811 *ccs811Sensor; // Pointer to CCS811 sensor
    PMS7003 *pms;          // Pointer to PMS7003

    // Variables to store current page and number of max pages
    int *page, *maxPage;
    // Variables for CCS sensor measurements
    int CO2, TVOC;
    // Variables for BME sensor measurements
    float bmeTemp, bmeHumidity, bmePressure, bmeGas;
    // Variables for PMS sensor measurements
    int pmsPM01, pmsPM25, pmsPM10, pmsn0p3, pmsn0p5, pmsn1p0, pmsn2p2, pmsn5p0, pmsn10p0;
};

#endif