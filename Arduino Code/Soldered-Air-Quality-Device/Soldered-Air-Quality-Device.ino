/*
    The air quality sensor is a device that measures particulate concentration in the air and determines air quality.
    It also measures temperature, humidity and pressure.

    settings.h is a file that contains parameters for device configuration. You can configure
    which sensors want to use by simply put 0 to the certain define. BME680 is used by default and you can't disable
    them while CCS811 and PMS7003 are optional. You can also adjust refresh time, battery high and low levels values,
    temperature offset to calibrate the BME680 sensor, rotary encoder pins, and PMS7003 pins.

    gui.h is a header file that contains class GUI class definition.

    gui.cpp contains all functions from the GUI class which is used to display measurements on the screen and initialize
    sensors.

    Make sure to install next libraries:
    Soldered-LCD: https://github.com/SolderedElectronics/Soldered-LCD-library
    Soldered-BME280: https://github.com/SolderedElectronics/Soldered-BME280-BME680-Gas-Sensor-Arduino-Library
    Soldered-CCS811: https://github.com/SolderedElectronics/Soldered-CCS811-Air-Quality-Sensor-Arduino-Library
    Soldered-PMS7003: https://github.com/SolderedElectronics/Soldered-PMS7003-Particle-Sensor-Arduino-Library

    12 December 2022 by Soldered
*/

#include "src/gui.h"      // Include GUI class definition and its methods
#include "src/settings.h" // Include users settings

int page = 0, prevPage;            // Use those variables to select a page
int currentStateClock;             // Store the status of the rotary encoder clock pin (HIGH or LOW)
int lastStateClock;                // Store the PREVIOUS status of the rotary encoder clock pin (HIGH or LOW)
unsigned long lastButtonPress = 0; // Use this to store if the ROTARY_BUTTON_PIN button was pressed or not
unsigned long lastRefresh = 0;     // Use this to store last screen refresh

int maxPage = 1;  // Max number of pages, 1 for the BME that it's always in use, later is added more if needed
int pageOrder[5]; // The array which decides the order of pages we display

unsigned long time1; // Time measurement for button click

BME680 bme680;               // Define BME sensor object
CCS_811 ccs811Sensor;        // Define CCS811 sensor object
LCD lcd(20, 4);              // Define LCD object
PMS7003 pms(PMS_RX, PMS_TX); // Define PMSx003, RX, TX

GUI gui(&lcd, &bme680, &ccs811Sensor, &pms, &page, &maxPage);

void setup()
{
    // Set analog reference to 1.1V to measure battery voltage if you use this option
    if (MEASURING_BATTERY_VOLTAGE)
    {
        analogReference(INTERNAL);
    }

    // Turn the onboard LED off because we don't use it
    pinMode(LEDWS_BUILTIN, OUTPUT);
    digitalWrite(LEDWS_BUILTIN, LOW);

    // Begin I2C comunication
    Wire.begin();

    // Initialize LCD and turn the backlight on
    gui.displayBegin();

    // Set encoder and button pins as inputs with pullups
    pinMode(ROTARY_CLOCK_PIN, INPUT_PULLUP);
    pinMode(ROTARY_DATA_PIN, INPUT_PULLUP);
    pinMode(ROTARY_BUTTON_PIN, INPUT_PULLUP);

    // Read the initial state of clock pin of rotary encoder (it could be HIGH or LOW)
    lastStateClock = digitalRead(ROTARY_CLOCK_PIN);

    // Initialize BME
    gui.BMEbegin();

    if (USE_CCS_SENSOR) // Initialize CCS811
    {
        gui.CCSbegin();
        maxPage += 1; // Add 1 to max pages because the CCS needs 1 page
    }

    if (USE_PMS_SENSOR) // Initialize serial communication with PMS sensor
    {
        gui.PMSbegin();
        maxPage += 3; // Add 3 to max pages because the PMS needs 3 page
    }

    // Depending on how many pages we have, we know which sensor is used and set pages
    // Below are the indexes for each page:
    // index 1 - BME first page (1/1)
    // index 2 - CCS first page (1/1)
    // index 3 - PMS first page (1/3)
    // index 4 - PMS second page (2/3)
    // index 5 - PMS third page (3/3)
    switch (maxPage)
    {
    // Set order pages depending on which sensors using
    case 1:               // Only BME is used
        pageOrder[0] = 1; // BME first page
        break;
    case 2: // Using BME and CCS
        pageOrder[0] = 1;
        pageOrder[1] = 2;
        break;
    case 4: // Using BME and PMS
        pageOrder[0] = 1;
        pageOrder[1] = 3;
        pageOrder[2] = 4; // PMS first page
        pageOrder[3] = 5;
        break;
    case 5: // Using all 3 sensors
        pageOrder[0] = 1;
        pageOrder[1] = 2;
        pageOrder[2] = 3;
        pageOrder[3] = 4;
        pageOrder[4] = 5;
        break;
    }

    // Capture time for the values refresh
    lastRefresh = time1 = millis();

    // Delay to see splash screen
    delay(2000);

    // Read the sensors to have data to display
    gui.readSensors();

    // Set default home page
    gui.setPage(1);

    // Set the previous page to know when the page is changed
    prevPage = page;
}

void loop()
{

    // Read the current state of the rotary encoder CLK pin
    currentStateClock = digitalRead(ROTARY_CLOCK_PIN);

    // If last and current state of the rotary encoder Clock are different, then "pulse occurred"
    // React to only 1 state change to avoid double count
    if (currentStateClock != lastStateClock && currentStateClock == 1)
    {
        // If the data state is different than the Clock state then
        // the encoder is rotating "CCW" so we decrement
        if (digitalRead(ROTARY_DATA_PIN) != currentStateClock)
        {
            page--;

            // Prevent going to the negative numbers
            if (page < 0)
            {
                page = maxPage - 1;
            }
        }
        else
        {
            // Encoder is rotating CW so increment
            page++;

            // Prevent going to the more than 5 pages
            if (page > maxPage - 1)
            {
                page = 0;
            }
        }
    }

    // We save last Clock state for next loop
    lastStateClock = currentStateClock;

    // Read the button state
    int btnState = digitalRead(ROTARY_BUTTON_PIN);

    // If we detect LOW signal, button is pressed
    if (btnState == LOW)
    {
        // if 50ms have passed since last LOW pulse, it means that the
        // button has been pressed, released and pressed again
        if ((unsigned long)(millis() - lastButtonPress) > 50)
        {
            // If button is pressed, refresh screen
            if ((unsigned long)(millis() - lastRefresh) > 2000)
            {
                // Take measurements only once if the button is pressed more than one time in 2 seconds
                gui.readSensors();
                gui.setPage(pageOrder[page]);
                lastRefresh = time1 = millis();
            }
            else
            {
                // Only refresh the screen if the button is pressed more than one time in 2 sec
                gui.setPage(pageOrder[page]);
            }
        }

        // Remember last button press event
        lastButtonPress = millis();
    }

    // Put in a slight delay to help debounce the reading
    delay(1);

    // If the page is changing, change content
    if (prevPage != page)
    {
        gui.setPage(pageOrder[page]);
        prevPage = page;
    }

    // Refresh sensor readings every 5 seconds without blocking the code
    if ((unsigned long)(millis() - time1) > REFRESH_DATA_TIME)
    {
        // Set sensor readings depending on the page we are
        gui.readSensors();
        gui.setPage(pageOrder[page]);

        // Reset timer after refreshing
        time1 = millis();
    }
}
