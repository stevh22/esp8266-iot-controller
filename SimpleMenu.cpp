#include "simplemenu.h"

SimpleMenu::SimpleMenu(Adafruit_SSD1306 &_display){
  display = &_display;
}

void SimpleMenu::ShowMsg(String message){
  display->clearDisplay();
  display->setCursor(0,0);
  display->setTextSize(2);
  display->setTextColor(TEXT_COLOR);
  display->println("");
  display->println(message);
  display->display();
}

void SimpleMenu::SetData(char* data){
  DynamicJsonDocument doc(jsonCapacity);
  deserializeJson(doc, data);
  jsonRoot = doc.as<JsonObject>();

  String d = doc[1]["label"];

  display->clearDisplay();
  display->setCursor(0,0);
  display->println("INFO:"); 
  display->println(d);  
}

/*char* SimpleMenu::GetData(){
  return data;
}*/

/*void ShowMenu(String MenuArray[],int MenuSize){
  display.clearDisplay();
  display.setCursor(0,0);
  int maxLines = (SSD1306_LCDHEIGHT / (MENU_FONT_SIZE * 8))-1;
  MENU_SIZE = MenuSize-1;
  
  // Draw Titlebar
  display.setTextSize(MENU_FONT_SIZE);
  display.setTextColor(TITLE_COLOR);
  display.println(MenuArray[0]);

  // Draw Options
  display.setTextColor(TEXT_COLOR);
  for(int i=1;i<=maxLines;i++){
    if(i+DISPLAY_OFFSET > MENU_SIZE){break;}
    if(i+DISPLAY_OFFSET == CURSOR_POS){ display.print("> "); }else{ display.print("  "); }
    display.println(MenuArray[i+DISPLAY_OFFSET]);
  }
  display.display();
}*/

/*void ShowEntryInfo(String EntryTitle, String EntryInfo){
  display.clearDisplay();
  display.setCursor(0,0);
  int maxLines = (SSD1306_LCDHEIGHT / (MENU_FONT_SIZE * 8))-1;
  
  // Draw Titlebar
  display.setTextSize(MENU_FONT_SIZE);
  display.setTextColor(TITLE_COLOR);
  display.print(EntryTitle);
  display.println(":");

  // Draw Options
  display.setTextColor(TEXT_COLOR);
  display.print(EntryInfo);
  display.display();
}*/

void SimpleMenu::Redraw(){
  _ShowList();
}

void SimpleMenu::_ShowList(){
  for(int i=0;i < maxLines;i++){
    //display->println(jsonRoot[i]["label"]);  
  }  
}

void SimpleMenu::_SetTitle(String title){
  
}

void SimpleMenu::_AddPoint_Boolean(){
  
}

void SimpleMenu::_AddPoint_Int(){
  
}

void SimpleMenu::_AddPoint_Selection(){
  
}
