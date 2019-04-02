# ESPHelper32
### This project has been merged with https://github.com/ItKindaWorks/ESPHelper ###
Please use that library instead as this code is no longer being maintained


A library to make using WiFi and MQTT on the ESP32 easy.

This is a port of the ESPHelper library originally written for the ESP8266. For more information,
check out that library [here](https://github.com/ItKindaWorks/ESPHelper)

The library also features the ability to use the ArduinoOTA system for OTA updates. There are a number of wrapper
methods for enabling/disabling OTA and changing the OTA hostname and password.

Please take a look at the examples included with this library to get an idea of how it works. 

Note:
-----
This library does requre the use of these libraries (so make sure they're installed as well!):
 *
 [Metro](https://www.pjrc.com/teensy/td_libs_Metro.html)
 *
 [pubsubclient](https://github.com/knolleary/pubsubclient)

 In addition to those libraries, make sure that you have the ESP32 core installed. That can be found [here](https://github.com/espressif/arduino-esp32)
