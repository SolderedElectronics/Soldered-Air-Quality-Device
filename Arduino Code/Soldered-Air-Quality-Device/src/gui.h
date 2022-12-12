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
    LCD *lcd;
    BME680 *bme680;
    CCS_811 *ccs811Sensor;
    PMS7003 *pms;
    int *page, *maxPage;
    int CO2, TVOC;
    float bmeTemp, bmeHumidity, bmePressure, bmeGas;
    int pmsPM01, pmsPM25, pmsPM10, pmsn0p3, pmsn0p5, pmsn1p0, pmsn2p2, pmsn5p0, pmsn10p0;
};

#endif