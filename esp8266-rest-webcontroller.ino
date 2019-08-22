#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "SimpleMenu.h"

//================================================================
//   WIFI-Settings
//================================================================

#include "Secrets.h" // this file is intentionally not included in the sketch, so nobody accidentally commits their secret information.
// create a Secrets.h file with the following:

//// AP mode password
//// const char WiFiAPPSK[] = "your-password";

// Wi-Fi network to connect to (if not in AP mode)
// char* ssid = "your-ssid";
// char* pwd = "your-password";

//================================================================
//   Parameter
//================================================================
#define OLED_RESET LED_BUILTIN  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 64        // OLED display height, in pixels
#define SCREEN_ADDR 0x3C        // OLED i2c-Adresse

#define CONTROLLER_ADRESS       "esp-079448"

#define ROTARY_CLK D5
#define ROTARY_DAT D6
#define ROTARY_BTN D7
#define ROTARY_DEBOUNCE 150
#define ROTARY_BTN_DEBOUNCE 200
#define ROTARY_PRESS_DEBOUNCE 50

//================================================================
//   Global Variables
//================================================================
Adafruit_SSD1306 m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SimpleMenu menu(m_display);

volatile unsigned long RotaryBtnStateTime = 0;
volatile unsigned long RotaryStateTime = 0;
volatile byte RotaryChange = false;
volatile byte RotaryPressRotate = false;
volatile long RotaryCount = 0;
volatile long RotaryBtnCount = 0;

//================================================================
//   Setup-Code
//================================================================

void setup() {
  // for DEBUG
  Serial.begin(115200);
  
  // init OLED-Display
  m_display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR); 
  m_display.clearDisplay();
  m_display.display();

  // for Rotary Encoder
  pinMode(ROTARY_BTN, INPUT);
  pinMode(ROTARY_CLK, INPUT);
  pinMode(ROTARY_DAT, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(ROTARY_BTN), RotaryPress,  RISING);
  attachInterrupt(digitalPinToInterrupt(ROTARY_CLK), RotarySelect, CHANGE);

  // start Menu
  menu.ShowMsg("Suche Wlan");

  // connect to Wlan
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED){
    menu.ShowMsg("Suche Wlan.");
    delay(500);
    if(WiFi.status() == WL_CONNECTED){break;}
    menu.ShowMsg("Suche Wlan..");
    delay(500);
    if(WiFi.status() == WL_CONNECTED){break;}
    menu.ShowMsg("Suche Wlan...");
    delay(500);
  }

  menu.ShowMsg("Verbunden");
  GetDataFromController();
}
//================================================================
//   Loop-Code
//================================================================

void loop(){
  if(RotaryChange){
    if(RotaryBtnCount > 0){
      //Serial.print("Button Press Detected: ");
      //Serial.println(RotaryBtnCount);
      //menu.ShowMsg("BTN Press");
      
      if(menu.isMenuShown()){
        menu.SelectMenuPos();
      }else{
        menu.ShowMenu();
      }
    }else{
      //Serial.print("Rotary Detected: ");
      //Serial.println(RotaryCount);
      if(RotaryCount > 0){
        if(menu.isMenuShown()){
          menu.NextMenuPos();
        }else if(menu.isOptionShown()){
          menu.OptionRight();
        }
      }else if(RotaryCount < 0){
        if(menu.isMenuShown()){
          menu.PrevMenuPos();
        }else if(menu.isOptionShown()){
          menu.OptionLeft();
        }
      }
    }
    
    RotaryBtnCount = 0;
    RotaryCount = 0;
    RotaryChange = false;
  }
  if(menu.isDataChanged()){
      SendDataToController();
  }
}

//================================================================
//   Additional Functions
//================================================================

ICACHE_RAM_ATTR void RotaryPress(){
  if((millis() - RotaryBtnStateTime) > ROTARY_BTN_DEBOUNCE){
    if((millis() - RotaryStateTime ) > ROTARY_PRESS_DEBOUNCE){
      RotaryPressRotate = false;
    }
    
    if(!RotaryPressRotate){
      RotaryBtnCount++;
      RotaryChange = true;
    }

    RotaryBtnStateTime = millis(); 
  }
}

ICACHE_RAM_ATTR void RotarySelect(){
  if((millis() - RotaryStateTime) > ROTARY_DEBOUNCE){ 
    RotaryPressRotate = true;

    if(digitalRead(ROTARY_CLK) != digitalRead(ROTARY_DAT)){
      if(!digitalRead(ROTARY_BTN)){//Rechts
        RotaryCount++;
      }else{
        RotaryCount = RotaryCount + 100;
      } 
    }else{
      if(!digitalRead(ROTARY_BTN)){//Links
        RotaryCount--;
      }else{
        RotaryCount = RotaryCount - 100;
      }  
    }
    
    RotaryChange = true;
    RotaryStateTime = millis();
  }
}

void GetDataFromController(){
    HTTPClient http;
    http.begin(CONTROLLER_ADRESS,80,"/all");
    int httpCode = http.GET();

    if(httpCode > 0){
      menu.SetData(http.getString());
      menu.ShowMenu();
    }else{
      menu.ShowMsg("Keine Lampe\ngefunden."); 
      
      //const String json = "[{\"name\":\"power\",\"label\":\"Power\",\"type\":\"Boolean\",\"value\":255},{\"name\":\"brightness\",\"label\":\"Brightness\",\"type\":\"Number\",\"value\":255,\"min\":1,\"max\":255},{\"name\":\"pattern\",\"label\":\"Pattern\",\"type\":\"Select\",\"value\":1,\"options\":[\"Pride\",\"Color Waves\",\"Rainbow Twinkles\",\"Snow Twinkles\",\"Cloud Twinkles\",\"Incandescent Twinkles\",\"Retro C9 Twinkles\",\"Red & White Twinkles\",\"Blue & White Twinkles\",\"Red, Green & White Twinkles\",\"Fairy Light Twinkles\",\"Snow 2 Twinkles\",\"Holly Twinkles\",\"Ice Twinkles\",\"Party Twinkles\",\"Forest Twinkles\",\"Lava Twinkles\",\"Fire Twinkles\",\"Cloud 2 Twinkles\",\"Ocean Twinkles\",\"Rainbow\",\"Rainbow With Glitter\",\"Solid Rainbow\",\"Confetti\",\"Sinelon\",\"Beat\",\"Juggle\",\"Fire\",\"Water\",\"Solid Color\"]},{\"name\":\"palette\",\"label\":\"Palette\",\"type\":\"Select\",\"value\":7,\"options\":[\"Rainbow\",\"Rainbow Stripe\",\"Cloud\",\"Lava\",\"Ocean\",\"Forest\",\"Party\",\"Heat\"]},{\"name\":\"speed\",\"label\":\"Speed\",\"type\":\"Number\",\"value\":30,\"min\":1,\"max\":255},{\"name\":\"autoplay\",\"label\":\"Autoplay\",\"type\":\"Section\"},{\"name\":\"autoplay\",\"label\":\"Autoplay\",\"type\":\"Boolean\",\"value\":255},{\"name\":\"autoplayDuration\",\"label\":\"Autoplay Duration\",\"type\":\"Number\",\"value\":255,\"min\":0,\"max\":255},{\"name\":\"solidColor\",\"label\":\"Solid Color\",\"type\":\"Section\"},{\"name\":\"solidColor\",\"label\":\"Color\",\"type\":\"Color\",\"value\":\"255,255,255\"},{\"name\":\"fire\",\"label\":\"Fire & Water\",\"type\":\"Section\"},{\"name\":\"cooling\",\"label\":\"Cooling\",\"type\":\"Number\",\"value\":49,\"min\":0,\"max\":255},{\"name\":\"sparking\",\"label\":\"Sparking\",\"type\":\"Number\",\"value\":60,\"min\":0,\"max\":255},{\"name\":\"twinkles\",\"label\":\"Twinkles\",\"type\":\"Section\"},{\"name\":\"twinkleSpeed\",\"label\":\"Twinkle Speed\",\"type\":\"Number\",\"value\":4,\"min\":0,\"max\":8},{\"name\":\"twinkleDensity\",\"label\":\"Twinkle Density\",\"type\":\"Number\",\"value\":5,\"min\":0,\"max\":8}]";
      //const String json = "[{\"label\":\"Hauptmenu\",\"type\":\"SimpelMenu\"},{\"name\":\"twinkleSpeed\",\"label\":\"Twinkle Speed\",\"type\":\"Number\",\"value\":4,\"min\":0,\"max\":8},{\"name\":\"twinkleDensity\",\"label\":\"Twinkle Density\",\"type\":\"Number\",\"value\":5,\"min\":0,\"max\":8}]";
      //menu.SetData(json);
      //menu.ShowMenu();
    }
    http.end();
}

void SendDataToController(){
  const size_t capacity = JSON_ARRAY_SIZE(30) + JSON_OBJECT_SIZE(5) + 540;
  DynamicJsonDocument jsonDoc(capacity);
  deserializeJson(jsonDoc, menu.GetChangedData());

  String val = jsonDoc["value"].as<String>();
  String val_name = jsonDoc["name"].as<String>();

  HTTPClient http;   
  http.begin(CONTROLLER_ADRESS,80,(String)"/" + val_name); 
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST((String)"value=" + val); 

  if(httpResponseCode>0){
    if(httpResponseCode == 200){
      String response = http.getString();
      if(response != val){
        menu.ShowMsg("Wrong Data");
      }
    }
  }else{
    menu.ShowMsg("POST\nError."); 
  }
  http.end();
}

