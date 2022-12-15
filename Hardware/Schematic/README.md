![schematic](https://user-images.githubusercontent.com/80395378/207919256-e3b7d9b5-aca6-479f-8404-6642e3403a64.jpg)

The sensors and other components are connected according to the schematic. The BME680, CCS811, and the LCD support easyC so connected to the Dasduino through it for simplicity. The order of connection of easyC is not important and it does not have to be connected in the same order as in the wiring diagram. PMS7003 is connected to the PMS adapter and the same adapter to the Dasduino. It is important to note that we have to connect the serial communication through a logic level converter because the PMS uses 3.3V logic levels and the Dasduino uses 5V logic levels. The adapter independently raises the voltage to 5V, which powers the PMS sensor itself, so we don't have to take this in mind. To measure the battery voltage, it is necessary to make a voltage divider that will lower the battery voltage to the range from 0 to 1.1V so that it can be measured correctly using an internal reference, and for this, resistances R1 = 10K and R2 = 3.3K were used. If we were to measure the voltage using a 5V reference, as the battery would discharge, the reference voltage would be lower and lower and the battery reading would always be incorrect. By using an internal reference, we solved that problem because it is always fixed. To stabilize the voltage, a C1 = 100 uF capacitor was added in parallel to the battery. A switch has been added to the circuit so that it disconnects the + pole of the battery instead of going directly to the Dasduino, and it is important to note that the battery cannot be charged if the switch is off.

# Used electronic components

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