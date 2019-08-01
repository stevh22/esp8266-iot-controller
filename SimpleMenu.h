#ifndef SIMPLEMENU_H
#define SIMPLEMENU_H

// DEFINITIONS FOR DISPLAYLIBARY
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include "ArduinoJson-v6.11.3.h"

#define TITLE_COLOR WHITE
#define TEXT_COLOR  WHITE

class SimpleMenu
{
public:
    SimpleMenu(Adafruit_SSD1306 _display);

    void SetTitle (String title);
    void SetMsg   (String message);
    void SetData  (String data);
    String GetData();
    void Redraw();

private:
    Adafruit_SSD1306 *display=nullptr;

    void _AddPoint_Boolean();
    void _AddPoint_Int();
    void _AddPoint_Selection();
};

#endif // SIMPLEMENU_H
