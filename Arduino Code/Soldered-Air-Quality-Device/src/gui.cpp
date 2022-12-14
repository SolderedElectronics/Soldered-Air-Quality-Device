/**
 ***************************************************
 *
 * @file        gui.cpp
 *
 * @brief       Functions for measuring and displaying the readings on the LCD
 *
 * @copyright   GNU General Public License v3.0
 *
 * @author      Karlo Leksic for Soldered.com
 *
 ****************************************************/

#include "gui.h"
#include "settings.h"

/**
 * @brief           Constructor of the GUI class.
 *
 * @param *_lcd     Pointer to the LCD object used for display sensor values.
 *
 * @param *_bme680  Pointer to the BME680 sensor used for measure temperature, humidity and pressure.
 *
 * @param *_ccs811Sensor Pointer to the CCS811 sensor used for measure Co2 and TVOC.
 *
 * @param *_pms     Pointer to the PMS7003 sensor used for measuring particle concentration in the air.
 *
 * @param *_page    Pointer to current page
 *
 * @param *_maxPage Pointer to the variable of the max number of pages
 */
GUI::GUI(LCD *_lcd, BME680 *_bme680, CCS_811 *_ccs811Sensor, PMS7003 *_pms, int *_page, int *_maxPage)
{
    lcd = _lcd;
    bme680 = _bme680;
    ccs811Sensor = _ccs811Sensor;
    pms = _pms;
    page = _page;
    maxPage = _maxPage;
}

/**
 * @brief           Sets the wanted page on the LCD and prints the sensor data on it.
 *
 * @param page      The number of page we want to display.
 *
 * @return          None.
 */
void GUI::setPage(byte page)
{
    switch (page)
    {
    case 1:               // Page 1 is the page for the BME sensor
        printBMEpage();   // Print BME page on the LCD
        insertNumbers(1); // Print sensor measurements on the LCD
        break;
    case 2:               // Page 3 is the page for the CCS sensor
        printCCSpage();   // Print CCS page on the LCD
        insertNumbers(2); // Print sensor measurements on the LCD
        break;
    case 3:               // Page 4 is the first of three pages for the PMS sensor
        printPMSpage(1);  // Print PMS page on the LCD
        insertNumbers(3); // Print sensor measurements on the LCD
        break;
    case 4:               // Page 5 is the second of three pages for the PMS sensor
        printPMSpage(2);  // Print PMS page on the LCD
        insertNumbers(4); // Print sensor measurements on the LCD
        break;
    case 5:               // Page 6 is the third of three pages for the PMS sensor
        printPMSpage(3);  // Print PMS page on the LCD
        insertNumbers(5); // Print sensor measurements on the LCD
        break;
    }

    insertPageNum(); // Print page number
    if (MEASURING_BATTERY_VOLTAGE)
    {
        printBatteryPercentage(); // Print battery percentage
    }
}

/**
 * @brief           Display content of the BME page: names of measurements and measurement units. Sensor values are
 *                  displayed separately.
 *
 * @return          None
 */
void GUI::printBMEpage()
{
    // Clear the display before the page is printing
    lcd->clear();

    // Set the cursor position to the right place on the screen and print the labels and measurement units for the BME
    // page on the LCD
    lcd->setCursor(0, 0);
    lcd->print("Temperature:");
    lcd->setCursor(19, 0);
    lcd->print("C");

    lcd->setCursor(0, 1);
    lcd->print("Humidity:");
    lcd->setCursor(19, 1);
    lcd->print("%");

    lcd->setCursor(0, 2);
    lcd->print("Presure:");
    lcd->setCursor(17, 2);
    lcd->print("hPa");

    pageMark(); // Prints the place to insert the page number
}

/**
 * @brief           Print content of the CCS page: names of measurements and measurement units. Sensor values are
 *                  printed separately.
 *
 * @return          None.
 */
void GUI::printCCSpage()
{
    // Clear the display before the page is printing
    lcd->clear();

    // Set the cursor position to the right place on the screen and print the labels for the CCS page on the LCD
    lcd->setCursor(0, 0);
    lcd->print("CO2:");
    lcd->setCursor(17, 0);
    lcd->print("ppm");

    lcd->setCursor(0, 1);
    lcd->print("tVOC:");
    lcd->setCursor(15, 1);
    lcd->print("ug/m3");

    pageMark(); // Prints the place to insert the page number
}

/**
 * @brief           Print content of the each PMS page: names of measurements and measurement units. Sensor values are
 *                  printed separately.
 *
 * @param page      The number of PMS page we want to display. There are 3 PMS pages (1 - 3).
 *
 * @return          None.
 */
void GUI::printPMSpage(byte page)
{
    // Clear the display before the page is printing
    lcd->clear();

    // Select the page depending on the page argument
    // Set the cursor position to the right place on the screen and print the labels for the PMS page on the LCD
    switch (page)
    {
    case 1:
        // Set cursor and print labels and measurement units for PM1.0, PM2.5, and PM10 on the right place on the screen
        lcd->setCursor(0, 0);
        lcd->print("PM1.0: ");
        lcd->setCursor(15, 0);
        lcd->print("ug/m3");

        lcd->setCursor(0, 1);
        lcd->print("PM2.5: ");
        lcd->setCursor(15, 1);
        lcd->print("ug/m3");

        lcd->setCursor(0, 2);
        lcd->print("PM10: ");
        lcd->setCursor(15, 2);
        lcd->print("ug/m3");
        break;

    case 2:
        // Set cursor and print labels and measurement units for N0.3, N0.5, and N1.0 on the right place on the screen
        lcd->setCursor(0, 0);
        lcd->print("N0.3: ");
        lcd->setCursor(13, 0);
        lcd->print("#/100cc");

        lcd->setCursor(0, 1);
        lcd->print("N0.5: ");
        lcd->setCursor(13, 1);
        lcd->print("#/100cc");

        lcd->setCursor(0, 2);
        lcd->print("N1.0: ");
        lcd->setCursor(13, 2);
        lcd->print("#/100cc");
        break;

    case 3:
        // Set cursor and print labels and measurement units for N2.5, N5.0, and N10 on the right place on the screen
        lcd->setCursor(0, 0);
        lcd->print("N2.5: ");
        lcd->setCursor(13, 0);
        lcd->print("#/100cc");

        lcd->setCursor(0, 1);
        lcd->print("N5.0: ");
        lcd->setCursor(13, 1);
        lcd->print("#/100cc");

        lcd->setCursor(0, 2);
        lcd->print("N10: ");
        lcd->setCursor(13, 2);
        lcd->print("#/100cc");
        break;
    }

    pageMark(); // Prints the place to insert the page number
}

/**
 * @brief           Function to insert only sensor measurements on display for each page.
 *
 * @param page      The page on which we want to insert numbers.
 *
 * @return          None.
 */
void GUI::insertNumbers(byte page)
{
    // Select the page depending on the page argument
    switch (page)
    {
    case 1:
        printBMEvalues();
        break;

    case 2:
        printCCSvalues();
        break;

    case 3:
        printPMSvalues(1);
        break;

    case 4:
        printPMSvalues(2);
        break;

    case 5:
        printPMSvalues(3);
        break;
    }
}

/**
 * @brief           Read BME sensor and store measurements in class variables.
 *
 * @return          None.
 */
void GUI::readBME()
{
    bme680->readSensorData(bmeTemp, bmeHumidity, bmePressure, bmeGas);
}

/**
 * @brief           Read PMS sensor and store measurements in class variables.
 *
 * @return          None.
 */
void GUI::readPMS()
{
    if (USE_PMS_SENSOR)
    {
        pms->read();
        if (pms)
        {
            pmsPM01 = pms->pm01;
            pmsPM25 = pms->pm25;
            pmsPM10 = pms->pm10;
            pmsn0p3 = pms->n0p3;
            pmsn0p5 = pms->n0p5;
            pmsn1p0 = pms->n1p0;
            pmsn2p2 = pms->n2p5;
            pmsn5p0 = pms->n5p0;
            pmsn10p0 = pms->n10p0;
        }
    }
}

/**
 * @brief           Read CCS sensor and store measurements in class variables.
 *
 * @return          None.
 */
void GUI::readCCS()
{
    if (USE_CCS_SENSOR)
    {
        if (ccs811Sensor->dataAvailable()) //  Check to see if data is ready
        {
            ccs811Sensor->readAlgorithmResults(); // Read Alorithm only reads data into internal registers of sensor,
                                                  // doesnt return anything
            CO2 = ccs811Sensor->getCO2();
            TVOC = ccs811Sensor->getTVOC();
        }
    }
}

/**
 * @brief           Read all sensors we use.
 *
 * @return          None.
 */
void GUI::readSensors()
{
    readBME();

    if (USE_CCS_SENSOR)
    {
        readCCS();
    }

    if (USE_PMS_SENSOR)
    {
        readPMS();
    }
}

/**
 * @brief           Print values that BME reads in the right place on the page.
 *
 * @return          None.
 */
void GUI::printBMEvalues()
{
    if (!BMEavailable())
    {
        // If the sensor read proprely, print read values and round them to 1 decimal
        lcd->setCursor(13, 0);
        lcd->print(bmeTemp + TEMP_OFFEST, 1);

        lcd->setCursor(13, 1);
        lcd->print(bmeHumidity, 1);

        lcd->setCursor(9, 2);
        lcd->print(bmePressure, 1);
    }
    else
    {
        // If failed to perform reading, print Err instead numbers
        lcd->setCursor(13, 0);
        lcd->print("Err");

        lcd->setCursor(13, 1);
        lcd->print("Err");

        lcd->setCursor(9, 2);
        lcd->print("Err");
    }
}

/**
 * @brief           Print values that CCS read in the right place on the page.
 *
 * @return          None.
 */
void GUI::printCCSvalues()
{
    lcd->setCursor(10, 0);
    lcd->print(CO2);

    lcd->setCursor(10, 1);
    lcd->print(TVOC);
}

/**
 * @brief           Prints values that PMS read in the right place on each page.
 *
 * @param page      Page of the PMS sensor on which we want to display read values. There are 3 pages, from 1 to 3.
 *
 * @return          None.
 */
void GUI::printPMSvalues(byte page)
{
    // Select the page depending on the page argument and print the measurements on the right place on the screen
    switch (page)
    {
    case 1:
        lcd->setCursor(10, 0);
        lcd->print(pmsPM01);

        lcd->setCursor(10, 1);
        lcd->print(pmsPM25);

        lcd->setCursor(10, 2);
        lcd->print(pmsPM10);
        break;

    case 2:
        lcd->setCursor(7, 0);
        lcd->print(pmsn0p3);

        lcd->setCursor(7, 1);
        lcd->print(pmsn0p5);

        lcd->setCursor(7, 2);
        lcd->print(pmsn1p0);
        break;

    case 3:
        lcd->setCursor(8, 0);
        lcd->print(pmsn2p2);

        lcd->setCursor(8, 1);
        lcd->print(pmsn5p0);

        lcd->setCursor(8, 2);
        lcd->print(pmsn10p0);
        break;
    }
}

/**
 * @brief           Insert page number in the right place.
 *
 * @return          None.
 */
void GUI::insertPageNum()
{
    if (MEASURING_BATTERY_VOLTAGE)
    {
        lcd->setCursor(6, 3);
        lcd->print(*page + 1);
    }
    else
    {
        lcd->setCursor(11, 3);
        lcd->print(*page + 1);
    }
}

/**
 * @brief           Prints the place for the page number in the last row.
 *
 * @return          None.
 */
void GUI::pageMark()
{
    if (MEASURING_BATTERY_VOLTAGE)
    {
        lcd->setCursor(0, 3);
        lcd->print("Page:  /");
        lcd->print(*maxPage);
    }
    else
    {
        lcd->setCursor(5, 3);
        lcd->print("Page:  /");
        lcd->print(*maxPage);
    }
}

/**
 * @brief           Initialize LCD and print splash screen.
 *
 * @return          None.
 */
void GUI::displayBegin()
{
    // Initialize LCD and turn on the backlight
    lcd->begin();
    lcd->backlight();

    // Set the cursor to the right position and print the splash screen
    lcd->setCursor(1, 1);
    lcd->print("Air quality sensor");
    lcd->setCursor(4, 2);
    lcd->print("by Soldered");
}

/**
 * @brief           Initialize the BME sensor and take measurements.
 *
 * @return          None.
 */
void GUI::BMEbegin()
{
    bme680->begin();
    bme680->readSensorData(bmeTemp, bmeHumidity, bmePressure, bmeGas);
}

/**
 * @brief           Initialize the CCS sensor and take measurements.
 *
 * @return          None.
 */
void GUI::CCSbegin()
{
    if (ccs811Sensor->begin())
    {
        if (ccs811Sensor->dataAvailable())
        {
            // Read CCS
            ccs811Sensor->readAlgorithmResults(); // Read Alorithm only reads data into internal registers of sensor,
                                                  // doesnt return anything
            CO2 = ccs811Sensor->getCO2();         // Returns calculated CO2 reading
            TVOC = ccs811Sensor->getTVOC();       // Returns calculated TVOC reading
        }
    }
}

/**
 * @brief           Initialize PMS sensor and take measurements.
 *
 * @return          None.
 */
void GUI::PMSbegin()
{
    pms->begin();
    pms->read();
}

/**
 * @brief           Check if the BME responses on the I2C, if so, it is probably available
 *
 * @return          Wire.endTransmission code. 0 means successfully.
 */
byte GUI::BMEavailable()
{
    Wire.beginTransmission(0x76);

    byte err = Wire.endTransmission();
    return err;
}

/**
 * @brief           Calculate and print battery level in percent.
 *
 * @return          None.
 */
void GUI::printBatteryPercentage()
{
    // Measure and calculate battery level
    // Analog reference is set to 1.1V because it's fix and we will get proper readings
    // Battery Voltage [V] = ADC reading * Vref/1023 * (1 + (R1/R2))
    float batteryVoltage = analogRead(BATTERY_MEASURE_PIN) * 1.1 / 1023 * (1 + (BATTERY_R1 / BATTERY_R2));

    // Print baterry level
    lcd->setCursor(15, 3);
    lcd->print(batteryVoltage, 2);
    lcd->print("V");
}
