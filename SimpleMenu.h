#ifndef SIMPLEMENU_H
#define SIMPLEMENU_H

// DEFINITIONS FOR DISPLAYLIBARY
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <ArduinoJson.h>

#define TITLE_COLOR               WHITE
#define TEXT_COLOR                WHITE
#define TEXT_SIZE                 1
#define MENU_TEXT_COLOR           WHITE
#define MENU_HIGHLIGHT_COLOR      BLACK
#define MENU_HIGHLIGHT_BACKCOLOR  WHITE
#define MENU_TEXT_SIZE            1.5
#define BACK_COLOR                BLACK
#define OPTION_STEP_SIZE          25
#define TRANSLATE_TEXT
#define SIMPLEMENU_TAG            "SimpelMenu"

class SimpleMenu
{
public:
    SimpleMenu(Adafruit_SSD1306 &_display);

    void SetData(const String data);
    void GetData(Stream &output);
    void GetChangedData(Stream &output);
    
    bool isMenuShown();
    bool isMsgShown();
    bool isOptionShown();
    bool isDataChanged();

    void NextMenuPos();
    void PrevMenuPos();
    void SelectMenuPos();
    void SetMenuPos(int pos=1);

    void OptionLeft();
    void OptionRight();
    
    void Redraw();
    void ShowMenu();
    void ShowMsg(String message="");
    
private:
    Adafruit_SSD1306 *display=nullptr;
    const int maxLines = 3;

    const size_t jsonCapacity =  JSON_ARRAY_SIZE(8) + JSON_ARRAY_SIZE(16) + JSON_ARRAY_SIZE(30) + 
      4*JSON_OBJECT_SIZE(3) + 3*JSON_OBJECT_SIZE(4) + 2*JSON_OBJECT_SIZE(5) + 7*JSON_OBJECT_SIZE(6) + 1480;
    DynamicJsonDocument jsondoc;
    JsonVariant jsonChanges;

    void _ClearDisplay();
    void _ShowOption(int option=-1);
    void _ShowList(int offset=0,int section=-1);
    void _DrawScrollBar(int points=1,int pos=1,int width=10);
    void _DrawVerticalBar(int x0, int y0, int x1, int y1, int val, int min_val, int max_val);
    void _DrawTitle(String title);
    void _AddPoint_Boolean();
    void _AddPoint_Int();
    void _AddPoint_Selection();

    String _GetDescr(String text);
    String _GetDescr(JsonDocument data);
    int _GetMenuSize(int section=-1);
    
    int _menuPos = 1;
    int _menuMaxPos = 1;
    int _menuDataIndex = 0;
    int _menuDataOffset = -1;
    bool _menuJumpScrool = false;
    
    String _lastMsg="";

    enum _optionType { opt_Boolean, opt_Number, opt_Select, opt_Submenu , opt_None};
    int _selectedOption = 0;
    int _selectedSection = -1;
    int _selectedOptionType = opt_None;
  
    bool _menuShown = false;
    bool _msgShown = false;
    bool _optionShown = false;
    bool _dataChanged = false;
};

#endif // SIMPLEMENU_H
