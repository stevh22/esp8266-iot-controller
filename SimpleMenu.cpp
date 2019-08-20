#include "simplemenu.h"

SimpleMenu::SimpleMenu(Adafruit_SSD1306 &_display):display(&_display), jsondoc(DynamicJsonDocument(jsonCapacity)){

}

void SimpleMenu::SetData(char* data){
  deserializeJson(jsondoc, data);
  _menuMaxPos = _GetMenuSize();
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

bool SimpleMenu::isMenuShown(){
  return _menuShown;  
}

bool SimpleMenu::isMsgShown(){
  return _msgShown;  
}

bool SimpleMenu::isOptionShown(){
  return _optionShown;  
}

void SimpleMenu::NextMenuPos(){
  if(_menuPos >= _menuMaxPos){
    if(_menuJumpScrool){
      _menuPos = 1;
    }
  }else{
    _menuPos++;  
  }
}

void SimpleMenu::PrevMenuPos(){
  if(_menuPos <= 1){
    if(_menuJumpScrool){
      _menuPos = _menuMaxPos;
    }
  }else{
    _menuPos--;  
  }
}

void SimpleMenu::SelectMenuPos(){
  
}

void SimpleMenu::SetMenuPos(int pos){
  if(pos < 0){_menuPos=0;}
  if(pos > _menuMaxPos){_menuPos=_menuMaxPos;}
  _menuPos=pos;
}

void SimpleMenu::Redraw(){
  _ClearDisplay();
  _ShowList(_menuPos - 1);
  _DrawScrollBar(_menuMaxPos,_menuPos);
  //_DrawVerticalBar(10,10,40,10,2,5);
  display->display();
}

void SimpleMenu::ShowMenu(){
  _ClearDisplay();
  _ShowList(_menuPos - 1);
  _DrawScrollBar(_menuMaxPos,_menuPos);
  _menuShown = true; 
  display->display();
}

void SimpleMenu::ShowMsg(String message){
  _ClearDisplay();
  display->setCursor(0,15);
  display->setFont(&FreeSans9pt7b);
  //display->setTextSize(TEXT_SIZE);
  display->setTextColor(TEXT_COLOR);
  display->println("");
  display->println(message);
  display->display();
  _msgShown = true;
}

void SimpleMenu::_ClearDisplay(){
  display->clearDisplay();
  display->setCursor(0,0);
  _menuShown = false;
  _msgShown = false;
  _optionShown = false;
}

void SimpleMenu::_ShowList(int offset){
  display->setFont(&FreeSans9pt7b);
  display->setCursor(0,15);
  
  bool noSub = false;
  int  soffset = 0;
  int16_t x1, y1;
  uint16_t w, h;

  for(int i=0;i < jsondoc.size();i++){
    // Check if SubSections start
    if(jsondoc[i]["type"] == "Section"){noSub = true;}
    
    // Count SubSection Offset
    if(noSub and (jsondoc[i]["type"] != "Section")){soffset++;}

    // Print Menu
    if(i >= offset + soffset  and i < maxLines + offset + soffset){
      if(!noSub or (jsondoc[i]["type"] == "Section")){
        String data = jsondoc[i]["label"];
        if((i - soffset) == offset){
          display->getTextBounds(_GetDescr(data), display->getCursorX(), display->getCursorY(), &x1, &y1, &w, &h);
          display->fillRect(x1-2, y1-2, display->width(), h+4, MENU_HIGHLIGHT_BACKCOLOR);
          display->setTextColor(MENU_HIGHLIGHT_COLOR);
          display->println(_GetDescr(data));

          _menuDataIndex = i;
        }else{
          display->setTextColor(MENU_TEXT_COLOR);
          display->println(_GetDescr(data));  
        }
      }
    }
  } 
}

void SimpleMenu::_DrawScrollBar(int points,int pos,int bar_width){
    if(pos <= 0){pos = 1;}
    if(pos > points){pos = points;}
    if(bar_width < 1){bar_width = 1;}
    
    int pointer_height = (display->height()/points);
    int pointer_pos = pointer_height*(pos-1);

    display->fillRect(display->width()-bar_width-1, 0, bar_width, display->height(), TEXT_COLOR);
    display->fillRect(display->width()-bar_width, 1,  (bar_width-2), display->height()-2, BACK_COLOR);
    display->fillRect(display->width()-bar_width, pointer_pos, (bar_width-2), pointer_height, TEXT_COLOR);
}

void SimpleMenu::_DrawVerticalBar(int x0, int y0, int x1, int y1, int val, int max_val){
    if(val <= 0){val = 1;}
    if(val > max_val){val = max_val;}
    if(x0 > x1){int tmp_x=x0; x0 = x1; x1=tmp_x;}
    if(y0 > y1){int tmp_y=y0; y0 = y1; y1=tmp_y;}

    int vbar_height = y1-y0;
    int vbar_width =  x1-x0;
    int pointer_width = (vbar_width/max_val);
    int pointer_pos = pointer_width*(val-1);
    
    display->fillRect(x0  ,  y0,vbar_width  ,vbar_height  ,TEXT_COLOR);
    display->fillRect(x0+1,y0+1,vbar_width-2,vbar_height-2,BACK_COLOR);
    display->fillRect(pointer_pos,y0+1,pointer_width,vbar_height-2,TEXT_COLOR);
}

void SimpleMenu::_SetTitle(String title){
  
}

void SimpleMenu::_AddPoint_Boolean(){
  
}

void SimpleMenu::_AddPoint_Int(){
  
}

void SimpleMenu::_AddPoint_Selection(){
  
}

// Übersetzt anzuzeigene Texte ins Deutsche
String SimpleMenu::_GetDescr(String text){
#ifdef TRANSLATE_TEXT
    if(text == "Power")       {return "An/Aus";}
    if(text == "Brightness")  {return "Helligkeit";}
    if(text == "Pattern")     {return "Modus";}
    if(text == "Palette")     {return "Farben";}
    if(text == "Speed")       {return "Geschw.";}
#endif 
    return text;
}

int SimpleMenu::_GetMenuSize(String section){
  int menuCount = 0;
  bool SubSections = false;

  if(section = ""){
    for(int i=0;i < jsondoc.size();i++){
      if(jsondoc[i]["type"] == "Section"){
        SubSections = true;
        menuCount++;
      }else{
        if(!SubSections){
          menuCount++; 
        }  
      }     
    }
  }else{
    for(int i=0;i < jsondoc.size();i++){
      if((jsondoc[i]["type"] == "Section") and (jsondoc[i]["name"] == section)){
        SubSections = true;
        menuCount++;
      }else if(SubSections){
        if((jsondoc[i]["type"] == "Section")){break;  }
        menuCount++; 
      }  
    }     
  }  
  return menuCount; 
}
