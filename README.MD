Katana with touch Sensitivtiy
=====================================================

Overview
-----------
This project uses an Adafruit MPR121 capacitive touch sensor and a WS2812 LED strip to create a touch-controlled LED strip with a rainbow mode. The LED strip can be turned on and off, and the color can be changed, using two electrodes on the MPR121 sensor.

![Cyberpunk-2077-Katana](Cyberpunk-2077-Katana.avif)

Hardware Requirements
-----------------------
* Adafruit MPR121 capacitive touch sensor
* WS2812 LED strip (106 LEDs)
* Arduino-compatible board (Arduino Uno, I used a NodeMCU8266)

Software Requirements
-----------------------
* Arduino IDE
* Adafruit MPR121 library
* FastLED library

How to Use
--------------
1. Connect the MPR121 sensor to your Arduino board according to the datasheet.
2. Connect the WS2812 LED strip to your Arduino board, with the data pin connected to D0.
3. Upload the code to your Arduino board using the Arduino IDE.
4. Touch electrode 0 to turn the LED strip on and off.
5. Touch electrode 4 to change the color of the LED strip. The color will cycle through red, white, blue, green, and rainbow mode.
6. In rainbow mode, the LED strip will display a colorful, animated pattern.

Code Explanation
-----------------
The code uses the Adafruit MPR121 library to read the touch state of the two electrodes, and the FastLED library to control the WS2812 LED strip.

The `setup()` function initializes the MPR121 sensor and the LED strip, and sets the initial color to red.

The `loop()` function reads the touch state of the two electrodes, and updates the LED strip accordingly. If electrode 0 is touched, the LED strip is turned on or off. If electrode 4 is touched, the color of the LED strip is changed.

The `fadeIn()` and `fadeOut()` functions are used to create a smooth transition when the LED strip is turned on or off.

The `rainbow()` function is used to generate the colorful, animated pattern in rainbow mode.

Video
------
This is a remix of the work done by ReAmped, What I did was to use a touch sensor that enables user to switch on and off the leds and change colors on command. Do check out his
[demo video on YouTube](https://youtu.be/tmwMuNbyuO8)

License
---------
This project is licensed under the MIT License. See the LICENSE file for details.

Acknowledgments
----------------
This project uses code from the Adafruit MPR121 library and the FastLED library, which are licensed under the MIT License.