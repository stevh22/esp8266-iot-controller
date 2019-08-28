#include "simplemenu.h"

SimpleMenu::SimpleMenu(Adafruit_SSD1306 &_display):display(&_display), jsondoc(DynamicJsonDocument(jsonCapacity)){ 
}

void SimpleMenu::SetData(const String data){
  deserializeJson(jsondoc, data);
  _menuMaxPos = _GetMenuSize();
}

void SimpleMenu::GetData(Stream &output){
  serializeJson(jsondoc, output);
  _dataChanged = false;
}

String SimpleMenu::GetChangedData(){
  _dataChanged = false;
  return jsonChanges.as<String>();
}

bool SimpleMenu::isMenuShown(){
  return _menuShown;  
}

bool SimpleMenu::isMsgShown(){
  return _msgShown;  
}

bool SimpleMenu::isOptionShown(){
  return _optionShown;  
}

bool SimpleMenu::isDataChanged(){
  return _dataChanged;  
}

void SimpleMenu::NextMenuPos(){
  int min_Pos,max_Pos;
  if(_selectedSection < 0){
    min_Pos = 1;
    max_Pos = _menuMaxPos;
  }else{
    min_Pos = _selectedSection - _menuDataOffset;
    max_Pos = _selectedSection - _menuDataOffset + _GetMenuSize(_selectedSection) -1; 
  }
  
  if(_menuPos >= max_Pos){
    if(_menuJumpScrool){
      _menuPos = min_Pos;
    }
  }else{
    _menuPos++;  
  }
  Redraw();
}

void SimpleMenu::PrevMenuPos(){
  int min_Pos,max_Pos;
  if(_selectedSection < 0){
    min_Pos = 1;
    max_Pos = _menuMaxPos;
  }else{
    min_Pos = _selectedSection - _menuDataOffset;
    max_Pos = _selectedSection - _menuDataOffset + _GetMenuSize(_selectedSection) -1; 
  }
  
  if(_menuPos <= min_Pos){
    if(_menuJumpScrool){
      _menuPos = max_Pos;
    }
  }else{
    _menuPos--;  
  }
  Redraw();
}

void SimpleMenu::SetMenuPos(int pos){
  int min_Pos,max_Pos;
  if(_selectedSection < 0){
    min_Pos = 1;
    max_Pos = _menuMaxPos;
  }else{
    min_Pos = _selectedSection - _menuDataOffset;
    max_Pos = _selectedSection - _menuDataOffset + _GetMenuSize(_selectedSection) -1; 
  }
  
  if(pos < min_Pos){_menuPos=min_Pos;}
  if(pos > max_Pos){_menuPos=max_Pos;}
  _menuPos=pos;
}

void SimpleMenu::SelectMenuPos(){
  _ShowOption(_menuDataIndex);
}

void SimpleMenu::OptionLeft(){
  switch(_selectedOptionType){
    case opt_Boolean:
      jsondoc[_selectedOption]["value"] = "1";
      break;
    case opt_Number:{
      JsonObject root = jsondoc[_selectedOption].as<JsonObject>();
      int val = root["value"];
      int val_min = root["min"];
      int val_max = root["max"];
      
      if(val_max > 8){
        jsondoc[_selectedOption]["value"] = val - OPTION_STEP_SIZE;
      }else{
        jsondoc[_selectedOption]["value"] = val - 1;
      }

      val = root["value"];
      if(val < val_min){
        jsondoc[_selectedOption]["value"] = val_min;
      }
      break;}
    case opt_Select:{
      JsonObject root = jsondoc[_selectedOption].as<JsonObject>();
      JsonArray options = root["options"].as<JsonArray>();
    
      int val = root["value"];
      int val_min = 0;
      int val_max = options.size()-1;

      jsondoc[_selectedOption]["value"] = val - 1;

      val = root["value"];
      if(val < val_min){
        jsondoc[_selectedOption]["value"] = val_min;
      }
      break;}
  }

  Redraw();
  jsonChanges = jsondoc[_selectedOption];
  _dataChanged = true; 
}

void SimpleMenu::OptionRight(){
  switch(_selectedOptionType){
    case opt_Boolean:
      jsondoc[_selectedOption]["value"] = "0";
      break;
    case opt_Number:{
      JsonObject root = jsondoc[_selectedOption].as<JsonObject>();
      int val = root["value"];
      int val_min = root["min"];
      int val_max = root["max"];
      
      if(val_max > 8){
        jsondoc[_selectedOption]["value"] = val + OPTION_STEP_SIZE;
      }else{
        jsondoc[_selectedOption]["value"] = val + 1;
      }

      val = root["value"];
      if(val > val_max){
        jsondoc[_selectedOption]["value"] = val_max;
      }
      break;}
    case opt_Select:{
      JsonObject root = jsondoc[_selectedOption].as<JsonObject>();
      JsonArray options = root["options"].as<JsonArray>();
    
      int val = root["value"];
      int val_min = 0;
      int val_max = options.size()-1;

      jsondoc[_selectedOption]["value"] = val + 1;
      
      val = root["value"];
      if(val > val_max){
        jsondoc[_selectedOption]["value"] = val_max;
      }
      break;}
  }
  
  Redraw();  
  jsonChanges = jsondoc[_selectedOption];
  _dataChanged = true; 
}

void SimpleMenu::Redraw(){
  if(_menuShown){
    ShowMenu();
  }else if(_msgShown){
    ShowMsg();
  }else if(_optionShown){
    _ShowOption();
  }
}

void SimpleMenu::ShowMenu(){
  if(jsondoc.size() == 0){return;}
  _ClearDisplay();
  
  _ShowList( _menuPos+_menuDataOffset, _selectedSection);
  if(_selectedSection <0){
    _DrawScrollBar( _menuMaxPos, _menuPos);
  }else{
    _DrawScrollBar( _GetMenuSize(_selectedSection), _menuPos+_menuDataOffset-_selectedSection+1);
  }
  
  display->display();
  _menuShown = true; 
}

void SimpleMenu::ShowMsg(String message){
  _ClearDisplay();
  
  display->setCursor(0,15);
  display->setFont(&FreeSans9pt7b);
  display->setTextColor(TEXT_COLOR);
  display->println("");
  if(message != ""){
     _lastMsg = message;
  }
  display->println(_lastMsg);
  
  display->display();
  _msgShown = true;
}

void SimpleMenu::_ShowOption(int option){
  _ClearDisplay();

  if(option < 0){
    option = _selectedOption;
  }else{
    _selectedOption = option;
    String data_type = jsondoc[option]["type"];

    if(data_type == "Boolean"){
      _selectedOptionType = opt_Boolean;
    }else if(data_type == "Number"){
      _selectedOptionType = opt_Number;
    }else if(data_type == "Select"){
      _selectedOptionType = opt_Select;
    }else if(data_type == "Section"){
      _selectedOptionType = opt_Submenu;
    }else if(data_type == "Color"){
      _selectedOptionType = opt_Color;
    }else{
      _selectedOptionType = opt_None;
    }
  }
   
  String title = jsondoc[option]["label"];
  switch(_selectedOptionType){
    case opt_Boolean:{
      _DrawTitle(_GetDescr(title));
      _AddPoint_Boolean();
      display->display();
      _optionShown = true;
      break;}
    case opt_Number:{
      _DrawTitle(_GetDescr(title));
      _AddPoint_Int();
      display->display();
      _optionShown = true;
      break;}
    case opt_Select:{
      _DrawTitle(_GetDescr(title));
      _AddPoint_Selection();
      display->display();
      _optionShown = true;
      break;}
    case opt_Submenu:{
      if(_selectedSection < 0){
        _selectedSection = _selectedOption;
        _menuDataOffset = _menuDataIndex - _menuPos;
      }else{
        _selectedSection = -1;
        _menuDataOffset = -1;
      }
      
      _menuShown = true;
      _optionShown = false;
      Redraw();
      break;}

    case opt_Color:{
      _DrawTitle(_GetDescr(title));
      _AddPoint_ColorMixer();
      //_AddPoint_ColorSelection();
      display->display();
      _optionShown = true;
      break;}
    default:{
      _DrawTitle(_GetDescr(title));
      display->println("not supported");
      display->display();
      _optionShown = true;
      break;}
  }
}

void SimpleMenu::_ClearDisplay(){
  display->clearDisplay();
  display->setCursor(0,0);
  _menuShown = false;
  _msgShown = false;
  _optionShown = false;
}

void SimpleMenu::_ShowList(int offset,int section){
  display->setFont(&FreeSans9pt7b);
  display->setCursor(0,15);

  bool Sub = false;
  bool noSub = false;
  int  soffset = 0;
  int16_t x1, y1;
  uint16_t w, h;
  String data = "";

  if(section < 0){
    //Print Mainmenu
    for(int i=0;i < jsondoc.size();i++){
      // Check if SubSections start
      if(jsondoc[i]["type"] == "Section"){noSub = true;}
      
      // Count SubSection Offset
      if(noSub and (jsondoc[i]["type"] != "Section")){soffset++;}
  
      // Print Menu
      if(i >= offset + soffset  and i < maxLines + offset + soffset){
        if(!noSub or (jsondoc[i]["type"] == "Section")){
          data = jsondoc[i]["label"].as<String>();
          
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
  }else{
    //Print SubMenu
    for(int i=0;i < jsondoc.size();i++){
      // Check if SubSections starts
      if(jsondoc[i]["type"] == "Section"){
        if(i == section){       // Check if SubSections starts
          Sub = true;
        }else if(i > section){  // Check if SubSections ends
          break;
        }
      }
       
      // Print Menu
      if(i >= offset  and i < maxLines + offset){
        if(Sub){
          if(i == section){
            data = "back to Menu";
          }else{
            data = jsondoc[i]["label"].as<String>();
          }
          
          if(i == offset){
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

void SimpleMenu::_DrawVerticalBar(int x0, int y0, int x1, int y1, int val, int min_val, int max_val){
    if(val < 0){val = 0;}
    if(val > max_val){val = max_val;}
    if(x0 > x1){int tmp_x=x0; x0 = x1; x1=tmp_x;}
    if(y0 > y1){int tmp_y=y0; y0 = y1; y1=tmp_y;}

    int vbar_height = y1-y0;
    int vbar_width =  x1-x0;
    int pointer_width = (vbar_width/(max_val-min_val));
    if(pointer_width < 5){
      pointer_width = 5;
    };
    int pointer_pos = map(val, min_val, max_val, x0, x0+vbar_width-pointer_width);
    
    display->fillRect(x0  ,  y0,vbar_width  ,vbar_height  ,TEXT_COLOR);
    display->fillRect(x0+1,y0+1,vbar_width-2,vbar_height-2,BACK_COLOR);
    display->fillRect(pointer_pos,y0+1,pointer_width,vbar_height-2,TEXT_COLOR);
}

void SimpleMenu::_DrawTitle(String title){
    display->setFont(&FreeSans9pt7b);
    display->setTextColor(TEXT_COLOR);
    
    int16_t x1, y1;
    uint16_t w, h;
    
    display->getTextBounds(title, 0, 15, &x1, &y1, &w, &h);

    int title_pos_x = (display->width()-w)/2;
    int title_pos_y = (y1+h);
    
    display->fillRect(0, title_pos_y + 4, display->width(), 2, MENU_HIGHLIGHT_BACKCOLOR);
    display->setCursor(title_pos_x,title_pos_y);
    display->println(title);
    display->setCursor(0,display->getCursorY()+10);
}

void SimpleMenu::_AddPoint_Boolean(){
    display->setTextColor(TEXT_COLOR);

    String tText = " / ";
    int16_t x1, y1 , x2 , y2 , x3 , y3;
    uint16_t w1, h1 , w2, h2 , w3 , h3;
    display->getTextBounds(_GetDescr("On") ,  0, display->getCursorY(), &x1, &y1, &w1, &h1);
    display->getTextBounds(tText           , w1, display->getCursorY(), &x2, &y2, &w2, &h2);
    display->getTextBounds(_GetDescr("Off"), w2, display->getCursorY(), &x3, &y3, &w3, &h3);

    int text_pos_x = (display->width()-(w1+w2+w3))/2;
    if(jsondoc[_selectedOption]["value"].as<int>() > 0){
      display->setTextColor(MENU_HIGHLIGHT_COLOR);
      display->fillRect( text_pos_x-3, y1-2, w1+6, h1+4, MENU_HIGHLIGHT_BACKCOLOR);
      display->setCursor(text_pos_x,display->getCursorY());
      display->print(_GetDescr("On"));
      display->setTextColor(TEXT_COLOR);
      display->print(tText);
      display->println(_GetDescr("Off"));  
    }else{
      display->setTextColor(TEXT_COLOR);
      display->setCursor(text_pos_x,display->getCursorY());
      display->print(_GetDescr("On"));
      display->print(tText);
      display->setTextColor(MENU_HIGHLIGHT_COLOR);
      display->fillRect( text_pos_x+w1+w2+x3-4, y3-2, w3+6, h3+4, MENU_HIGHLIGHT_BACKCOLOR);
      display->println(_GetDescr("Off"));
    }
}

void SimpleMenu::_AddPoint_Int(){   
    int16_t x1, y1, x2, y2;
    uint16_t w1, h1, w2, h2;
    
    display->setTextColor(TEXT_COLOR);
    display->getTextBounds(jsondoc[_selectedOption]["value"].as<String>(),  0, display->getCursorY(), &x1, &y1, &w1, &h1);
    display->getTextBounds(jsondoc[_selectedOption]["max"].as<String>(),  0, display->getCursorY(), &x2, &y2, &w2, &h2);
    _DrawVerticalBar(2,
                    display->getCursorY()-10,
                    display->width()-w2-8,
                    display->getCursorY(), 
                    jsondoc[_selectedOption]["value"].as<int>(),
                    jsondoc[_selectedOption]["min"].as<int>(),
                    jsondoc[_selectedOption]["max"].as<int>());
    display->setCursor(display->width()-(w2/2)-(w1/2)-4,display->getCursorY());
    display->println(jsondoc[_selectedOption]["value"].as<String>());
}

void SimpleMenu::_AddPoint_Selection(){
    display->setTextColor(TEXT_COLOR);
    
    JsonObject root = jsondoc[_selectedOption].as<JsonObject>();
    JsonArray options = root["options"].as<JsonArray>();
    
    int val = root["value"];
    int val_max = options.size()-1;

    String text = "";
    String text_option = options[val];
    if(val > 0){text += "< ";}else{text += "  ";}
    text += text_option;
    if(val < val_max){text += " >";}else{text += "  ";}

    int16_t x1, y1;
    uint16_t w1, h1;
    display->getTextBounds(text ,  0, display->getCursorY(), &x1, &y1, &w1, &h1);
    display->setCursor((display->width()-(w1))/2 ,display->getCursorY());
    display->println(text);
}

void SimpleMenu::_AddPoint_ColorMixer(){
    //{\"name\":\"solidColor\",\"label\":\"Color\",\"type\":\"Color\",\"value\":\"255,255,255\"}
    display->println("new");
}

void SimpleMenu::_AddPoint_ColorSelection(){
    //{\"name\":\"solidColor\",\"label\":\"Color\",\"type\":\"Color\",\"value\":\"255,255,255\"}
    display->println("new");
}

// Übersetzt anzuzeigene Texte ins Deutsche
String SimpleMenu::_GetDescr(String text){
#ifdef TRANSLATE_TEXT
    if(text == "Power")       {return "Strom";}
    if(text == "Brightness")  {return "Helligkeit";}
    if(text == "Pattern")     {return "Modus";}
    if(text == "Palette")     {return "Farben";}
    if(text == "Speed")       {return "Tempo";}
    if(text == "On")          {return "An";}
    if(text == "Off")         {return "Aus";
    if(text == "Autoplay Duration")       {return "Auto. Dauer";}}
#endif
    if(text == "Autoplay Duration")       {return "Auto. Duration";} 
    return text;
}

int SimpleMenu::_GetMenuSize(int section){
  int menuCount = 0;
  bool SubSections = false;

  if(section < 0){
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
      if(i == section){
        SubSections = true;
        menuCount++;
      }else if(SubSections){
        if((jsondoc[i]["type"] == "Section")){break;}
        menuCount++; 
      }  
    }     
  }  
  return menuCount; 
}
