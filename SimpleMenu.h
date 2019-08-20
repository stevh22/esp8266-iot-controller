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
#define TEXT_SIZE   2
#define BACK_COLOR  BLACK
//#define TRANSLATE_TEXT

class SimpleMenu
{
public:
    SimpleMenu(Adafruit_SSD1306 &_display);

    void SetData  (char *data);
    //char* GetData();
    void NextMenuPos();
    void PrevMenuPos();
    void SetMenuPos(int pos=1);
    
    void Redraw();
    void ShowMsg  (String message);

private:
    Adafruit_SSD1306 *display=nullptr;
    const int maxLines = 4;

    const size_t jsonCapacity =  JSON_ARRAY_SIZE(8) + JSON_ARRAY_SIZE(16) + JSON_ARRAY_SIZE(30) + 
      4*JSON_OBJECT_SIZE(3) + 3*JSON_OBJECT_SIZE(4) + 2*JSON_OBJECT_SIZE(5) + 7*JSON_OBJECT_SIZE(6) + 1480;
    DynamicJsonDocument jsondoc;

    void _ShowList(int offset=0);
    void _DrawScrollBar(int points=1,int pos=1,int width=10);
    void _DrawVerticalBar(int x0, int y0, int x1, int y1, int val, int max_val);
    void _SetTitle(String title);
    void _AddPoint_Boolean();
    void _AddPoint_Int();
    void _AddPoint_Selection();

    String _GetDescr(String text);
    String _GetDescr(JsonDocument data);
    
    int _menuPos = 0;
    int _menuMaxPos = 0;
    bool _menuJumpScrool = true;
};

#endif // SIMPLEMENU_H
