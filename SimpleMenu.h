#ifndef SIMPLEMENU_H
#define SIMPLEMENU_H

// DEFINITIONS FOR DISPLAYLIBARY
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>

#define TITLE_COLOR WHITE
#define TEXT_COLOR  WHITE

class SimpleMenu
{
public:
    SimpleMenu(Adafruit_SSD1306 &_display);

    void SetData  (char *data);
    //char* GetData();
    
    void Redraw();
    void ShowMsg  (String message);

private:
    Adafruit_SSD1306 *display=nullptr;
    const int maxLines = 4;

    JsonObject jsonRoot;
    const size_t jsonCapacity =  JSON_ARRAY_SIZE(8) + JSON_ARRAY_SIZE(16) + JSON_ARRAY_SIZE(30) + 
      4*JSON_OBJECT_SIZE(3) + 3*JSON_OBJECT_SIZE(4) + 2*JSON_OBJECT_SIZE(5) + 7*JSON_OBJECT_SIZE(6) + 1480;

    void _ShowList();
    void _SetTitle(String title);
    void _AddPoint_Boolean();
    void _AddPoint_Int();
    void _AddPoint_Selection();
};

#endif // SIMPLEMENU_H
