# Description

Application for an ESP8266. Displays an Menu on an OLED-Display.
The data will be fetched form an REST-Api and changes will be send immediately.

# Features

* Menue (up to 1 Submenu)
* Input
  * Rotary Encoder
  * (_Buttons_)
* Auto-Sleep Mode to Save Power

# Hardware

To use the Auto-Sleep function the following circit is used to wake the ESP up.
![PCB-Autosleep-Wake](/RST_BUTTON_Schaltplan.jpg)

# Usages

Controller for [esp8266-fastled-webserver](https://github.com/jasoncoon/esp8266-fastled-webserver)

