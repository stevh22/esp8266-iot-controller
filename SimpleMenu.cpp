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

void SimpleMenu::SetTitle(String title){
  
}

void SimpleMenu::SetData(String data){
  
}


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

String SimpleMenu::GetData(){
  return "StringWithNothingData";
}

void SimpleMenu::Redraw(){
  
}

void SimpleMenu::_AddPoint_Boolean(){
  
}

void SimpleMenu::_AddPoint_Int(){
  
}

void SimpleMenu::_AddPoint_Selection(){
  
}
