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
 * @brief           Set the wanted page on the LCD, automatically read sensor data and print on it.
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

    // Set the cursor position to the right place on the screen and print the labels for the BME page on the LCD
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
    // Variables for bme values
    float bmeTemp, bmeHumidity, bmePressure, bmeGas, tempOffset = 0;

    if (page > 2) // Those are PMS pages so we need to read the PMS values if the page number is greater than 2
    {
        pms->read(); // PMS reads values and stores them in their variables
    }

    // Select the page depending on the page argument
    switch (page)
    {
    case 1:
        bme680->readSensorData(bmeTemp, bmeHumidity, bmePressure, bmeGas); // readBME
        printBMEvalues(bmeTemp - TEMP_OFFEST, bmeHumidity, bmePressure);   // Printing it to the LCD on the right place
        break;

    case 2:
        if (ccs811Sensor->dataAvailable()) //  Check to see if data is ready
        {
            ccs811Sensor->readAlgorithmResults(); // Read Alorithm only reads data into internal registers of sensor,
                                                  // doesnt return anything
            CO2 = ccs811Sensor->getCO2();
            TVOC = ccs811Sensor->getTVOC();

            printCCSvalues(CO2, TVOC); // Printing it to the LCD on the right place
        }
        else
        {
            printCCSvalues(-1, -1);
        }
        break;

    case 3:
        if (pms)
        {
            // Printing it to the LCD on the right place
            printPMSvalues(1, pms->pm01, pms->pm25, pms->pm10, pms->n0p3, pms->n0p5, pms->n1p0, pms->n2p5, pms->n5p0,
                           pms->n10p0);
        }
        else
        {
            // Set -1 to indicate that there is an error
            printPMSvalues(1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
        }
        break;

    case 4:
        if (pms)
        {
            // Printing it to the LCD on the right place
            printPMSvalues(2, pms->pm01, pms->pm25, pms->pm10, pms->n0p3, pms->n0p5, pms->n1p0, pms->n2p5, pms->n5p0,
                           pms->n10p0);
        }
        else
        {
            // Set -1 to indicate that there is an error
            printPMSvalues(2, -1, -1, -1, -1, -1, -1, -1, -1, -1);
        }
        break;

    case 5:
        if (pms)
        {
            // Printing it to the LCD on the right place
            printPMSvalues(3, pms->pm01, pms->pm25, pms->pm10, pms->n0p3, pms->n0p5, pms->n1p0, pms->n2p5, pms->n5p0,
                           pms->n10p0);
        }
        else
        {
            // Set -1 to indicate that there is an error
            printPMSvalues(3, -1, -1, -1, -1, -1, -1, -1, -1, -1);
        }
        break;
    }
}

/**
 * @brief           Print values that BME reads in the right place on the page.
 *
 * @param temp      The temperature we want to display.
 *
 * @param hum       The humidity we want to display.
 *
 * @param pressure  The pressure we want to display.
 *
 * @return          None.
 */
void GUI::printBMEvalues(float temp, float hum, float pressure)
{
    if (!BMEavailable())
    {
        // If the sensor read proprely, print read values and round them to 1 decimal
        lcd->setCursor(13, 0);
        lcd->print(temp, 1);

        lcd->setCursor(13, 1);
        lcd->print(hum, 1);

        lcd->setCursor(9, 2);
        lcd->print(pressure, 1);
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
 * @param ccsCO2    The CO2 concentration value to display.
 *
 * @param ccsTVOC   The TVOC value to display.
 *
 * @return          None.
 */
void GUI::printCCSvalues(int ccsCO2, int ccsTVOC)
{
    if (ccsCO2 == -1)
    {
        // If there is any error, print old values
        lcd->setCursor(10, 0);
        lcd->print(CO2);

        lcd->setCursor(10, 1);
        lcd->print(TVOC);
    }
    else
    {
        // If not, print the CCS values
        lcd->setCursor(10, 0);
        lcd->print(ccsCO2);

        lcd->setCursor(10, 1);
        lcd->print(ccsTVOC);
    }
}

/**
 * @brief           Prints values that PMS read in the right place on each page.
 *
 * @param page      Page of the PMS sensor on which we want to display read values. There are 3 pages, from 1 to 3.
 *
 * @param pm1       The concentration of the pm1 particules to display.
 *
 * @param pm25       The concentration of the pm25 particules to display.
 *
 * @param pm10       The concentration of the pm10 particules to display.
 *
 * @param n0p3       The concentration of the n0p3 particules to display.
 *
 * @param n0p5       The concentration of the n0p5 particules to display.
 *
 * @param n1p0       The concentration of the n1p0 particules to display.
 *
 * @param n2p5       The concentration of the n2p5 particules to display.
 *
 * @param n5p0       The concentration of the n5p0 particules to display.
 *
 * @param n10p0       The concentration of the n10p0 particules to display.
 *
 * @return          None.
 */
void GUI::printPMSvalues(byte page, int pm1, int pm25, int pm10, int n0p3, int n0p5, int n1p0, int n2p5, int n5p0,
                         int n10p0)
{
    if (pm1 == -1)
    {
        // Above we send -1 to this function if there was any error so there print it
        lcd->clear();
        lcd->setCursor(0, 0);
        lcd->print("Error reading sensor");
    }

    // Select the page depending on the page argument and print the values
    switch (page)
    {
    case 1:
        lcd->setCursor(10, 0);
        lcd->print(pm1);

        lcd->setCursor(10, 1);
        lcd->print(pm25);

        lcd->setCursor(10, 2);
        lcd->print(pm10);
        break;

    case 2:
        lcd->setCursor(7, 0);
        lcd->print(n0p3);

        lcd->setCursor(7, 1);
        lcd->print(n0p5);

        lcd->setCursor(7, 2);
        lcd->print(n1p0);
        break;

    case 3:
        lcd->setCursor(8, 0);
        lcd->print(n2p5);

        lcd->setCursor(8, 1);
        lcd->print(n5p0);

        lcd->setCursor(8, 2);
        lcd->print(n10p0);
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
