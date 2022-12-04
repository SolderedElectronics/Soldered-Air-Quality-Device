# Device for measuring air quality parameters

In order to have an insight into the air quality in the places where we live, we designed a simple device that measures the parameters that determine air quality, namely: temperature, humidity, pressure, CO2, and the concentration of small-sized particles that are dispersed throughout the air. To measure these parameters, we chose sensors: BME680, CCS811, and PMS7003. In order to display the data to the user, there is an LCD screen that can display 80 characters, 20 in each of the 4 lines. The sensors are controlled by the Dasduino Core, and to make the device portable, it can also run on a battery. Navigation through a simple interface is made possible by a rotary encoder, and the 3D-printed case places all the sensors in a small space and gives it that unique maker character.

# Wiring diagram
Sensors and other components are connected according to the wiring diagram shown below.

(add wiring diagram)

# 3D case
In order for all the sensors and electronics to be in one place and at the same time look nice, a case was designed that was printed on a 3D printer. In order for the air to flow through the case for the sensors to measure correctly, there are openings on the back and on the top and bottom.

(case.jpeg)

When we place all the sensors in the intended place in the case, it looks like this

(deviceInside.jpeg)

# How to use this device?
The device has a rotary encoder that controls the device. By turning the rotary encoder, we change the pages on which the readings are displayed. The device automatically refreshes the data every 5 seconds (it can be changed in the code by simply changing the constant), but if we want immediate reading and refreshing of the page, it is possible by pressing the button of the rotary encoder. BME680 and PMS7003 are relatively fast and with them a new reading will be obtained, while CCS811 is not so fast and if we refresh its measurements too quickly sometimes it will not be able to measure them and old measurements will be displayed. These times are of the order of several tenths, and this will not be noticed if the device refreshes itself. Depending on how many sensors are connected, we have a different number of pages, and the pages go in a circle, i.e. from the last page by turning forward, we switch to the first page and vice versa.

(image.jpg)

In the bottom right corner is the battery voltage. When the Dasduino is connected to 5V via the USB-c port, the voltage can vary because it is charging the battery. There is a switch on the device that turns the battery on and off from the circuit, i.e. when the device is connected to 5V, the battery will charge only if the switch is set to 1, otherwise, the battery will not charge.

(image.jpg)