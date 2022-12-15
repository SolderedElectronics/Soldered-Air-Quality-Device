# Device for measuring air quality parameters

In order to have an insight into the air quality in the places where we live, we designed a simple device that measures the parameters that determine air quality, namely: temperature, humidity, pressure, CO2, and the concentration of small-sized particles that are dispersed throughout the air. To measure these parameters, we chose sensors: BME680, CCS811, and PMS7003. In order to display the data to the user, there is an LCD screen that can display 80 characters, 20 in each of the 4 lines. The sensors are controlled by the Dasduino Core, and to make the device portable, it can also run on a battery. Navigation through a simple interface is made possible by a rotary encoder, and the 3D-printed case places all the sensors in a small space and gives it that unique maker character.

![Air quality device](https://user-images.githubusercontent.com/80395378/205492621-1f41e716-84cb-40cd-bf39-39e6127fc348.jpg)

# Wiring diagram
Sensors and other components are connected according to the wiring diagram shown below.

![schematic](https://user-images.githubusercontent.com/80395378/207919256-e3b7d9b5-aca6-479f-8404-6642e3403a64.jpg)

## Used electronic components

* Dasduino CORE - [link](https://soldered.com/product/dasduino-core-2/)
* Enviromental & air quality sensor BME680 breakout - [link](https://soldered.com/product/senzor-kvalitete-zraka-i-okoline-bme680-2/)
* Air quality sensor CCS811 breakout - [link](https://soldered.com/product/senzor-kvalitete-zraka-ccs811-2/)
* PMS7003 senzor PM10, PM2.5 - [link](https://soldered.com/hr/proizvod/pms7003-senzor-pm10-pm2-5/) + PMS7003 sensor adapter - [link](https://soldered.com/product/adapter-za-pms7003-senzor-2/)
* Logic level converter board - [link](https://soldered.com/product/pretvarac-logickih-razina-2/)
* LCD display16x4 white/blue - [link](https://soldered.com/product/lcd-ekran-16x4-bijelo-plavi-2/) + I2C LCD driver board - [link](https://soldered.com/hr/proizvod/i2c-lcd-driver-board/)
* Rotary encoder 20mm with pushbutton - [link](https://soldered.com/product/rotary-encoder-20mm-s-pushbuttonom-2/)
* Li-ion battery 1800mAh 3.7V - [link](https://soldered.com/product/li-ion-baterija-1800mah-3-7v-2/)
* SPST panel switch elongated - [link](https://soldered.com/product/spst-panel-prekidac-duguljasti-2/)
* Resistor 10K (it's situated in [Resistor kit 400](https://soldered.com/product/set-otpornika-400-2/))
* Resistor 3.3K (it's situated in [Resistor kit 400](https://soldered.com/product/set-otpornika-400-2/))
* Ceramic capacitor 100nF 50V - [link](https://soldered.com/product/keramicki-kondenzator-100nf-50v-2/)

## Consumable material for assembling:
* PLA Soldered purple filament
* M3 Threaded inserts
* 9x Screw M3 5mm HEX - [link](https://soldered.com/product/vijak-m3-5mm-hex-2/)
* 4x Screw M3 12mm HEX - [link](https://soldered.com/product/vijak-m3-12mm-hex-2/)
* Prototyping wire AWG25 - [link](https://soldered.com/product/ica-za-prototipiranje-10m-crvena-awg25-2/)
* 3x easyC cable 10cm - [link](https://soldered.com/product/easyc-kablic-10cm-2/)
* Heatshrink - [link](https://soldered.com/product/set-termobuzira-2/)

# 3D case
In order for all the sensors and electronics to be in one place and at the same time look nice, a case was designed that was printed on a 3D printer. In order for the air to flow through the case for the sensors to measure correctly, there are openings on the back and on the top and bottom.

![3d case](https://user-images.githubusercontent.com/80395378/205492653-ce953e9f-a88d-4713-8ed8-0de51e9584e5.jpg)

When we place all the sensors in the intended place in the case, it looks like this

![Device inside with bme680](https://user-images.githubusercontent.com/80395378/206113455-f1681e16-3fd0-4634-a585-58af407c7d01.jpg)

# How to use this device?
The device has a rotary encoder that controls the device. By turning the rotary encoder, we change the pages on which the readings are displayed. The device automatically refreshes the data every 5 seconds (it can be changed in the code by simply changing the constant), but if we want immediate reading and refreshing of the page, it is possible by pressing the button of the rotary encoder. BME680 and PMS7003 are relatively fast and with them a new reading will be obtained, while CCS811 is not so fast and if we refresh its measurements too quickly sometimes it will not be able to measure them and old measurements will be displayed. These times are of the order of several tenths, and this will not be noticed if the device refreshes itself. Depending on how many sensors are connected, we have a different number of pages, and the pages go in a circle, i.e. from the last page by turning forward, we switch to the first page and vice versa.

![Page2](https://user-images.githubusercontent.com/80395378/205492702-76d5aeb6-906b-446c-8a0a-c1e958f46927.jpg)
![Page3](https://user-images.githubusercontent.com/80395378/205492715-528fa439-4bd2-4577-850b-38a90cfe1cad.jpg)
![Page4](https://user-images.githubusercontent.com/80395378/205492723-6b6feabd-3105-4cf5-ae0b-19ea03025730.jpg)

In the bottom right corner is the battery voltage. When the Dasduino is connected to 5V via the USB-c port, the voltage can vary because it is charging the battery. There is a switch on the device that turns the battery on and off from the circuit, i.e. when the device is connected to 5V, the battery will charge only if the switch is set to 1, otherwise, the battery will not charge.

![Device From Above](https://user-images.githubusercontent.com/80395378/205492684-263042f3-78b5-4c0f-afb1-acce2410f5a6.jpg)