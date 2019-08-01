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

#define KEY_BUTTON D3
#define MENU_FONT_SIZE 2

const int MAIN_MENU_SIZE = 4;
String MAIN_MENU[MAIN_MENU_SIZE] = {"Lichtmodi:","Funken","Weiss","Rainbow"};
//================================================================
//   Global Variables
//================================================================
Adafruit_SSD1306 m_display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SimpleMenu menu(m_display);

int CURSOR_POS = 1;
int MENU_SIZE = 0;
int DISPLAY_OFFSET = 0;
volatile unsigned long ButtonStateTime = 0;

//================================================================
//   Setup-Code
//================================================================

void setup() {
  // init OLED-Display
  m_display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR); 
  m_display.clearDisplay();
  m_display.display();

  // for Buttons
  pinMode(KEY_BUTTON, INPUT_PULLUP);
  //attachInterrupt(KEY_BUTTON, ButtonPress, FALLING);

  // start Menu
  menu.ShowMsg("Suche Wlan");

  // connect to Wlan
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  
  char* json = "[{\"name\":\"power\",\"label\":\"Power\",\"type\":\"Boolean\",\"value\":255},{\"name\":\"brightness\",\"label\":\"Brightness\",\"type\":\"Number\",\"value\":255,\"min\":1,\"max\":255},{\"name\":\"pattern\",\"label\":\"Pattern\",\"type\":\"Select\",\"value\":1,\"options\":[\"Pride\",\"Color Waves\",\"Rainbow Twinkles\",\"Snow Twinkles\",\"Cloud Twinkles\",\"Incandescent Twinkles\",\"Retro C9 Twinkles\",\"Red & White Twinkles\",\"Blue & White Twinkles\",\"Red, Green & White Twinkles\",\"Fairy Light Twinkles\",\"Snow 2 Twinkles\",\"Holly Twinkles\",\"Ice Twinkles\",\"Party Twinkles\",\"Forest Twinkles\",\"Lava Twinkles\",\"Fire Twinkles\",\"Cloud 2 Twinkles\",\"Ocean Twinkles\",\"Rainbow\",\"Rainbow With Glitter\",\"Solid Rainbow\",\"Confetti\",\"Sinelon\",\"Beat\",\"Juggle\",\"Fire\",\"Water\",\"Solid Color\"]},{\"name\":\"palette\",\"label\":\"Palette\",\"type\":\"Select\",\"value\":7,\"options\":[\"Rainbow\",\"Rainbow Stripe\",\"Cloud\",\"Lava\",\"Ocean\",\"Forest\",\"Party\",\"Heat\"]},{\"name\":\"speed\",\"label\":\"Speed\",\"type\":\"Number\",\"value\":30,\"min\":1,\"max\":255},{\"name\":\"autoplay\",\"label\":\"Autoplay\",\"type\":\"Section\"},{\"name\":\"autoplay\",\"label\":\"Autoplay\",\"type\":\"Boolean\",\"value\":255},{\"name\":\"autoplayDuration\",\"label\":\"Autoplay Duration\",\"type\":\"Number\",\"value\":255,\"min\":0,\"max\":255},{\"name\":\"solidColor\",\"label\":\"Solid Color\",\"type\":\"Section\"},{\"name\":\"solidColor\",\"label\":\"Color\",\"type\":\"Color\",\"value\":\"255,255,255\"},{\"name\":\"fire\",\"label\":\"Fire & Water\",\"type\":\"Section\"},{\"name\":\"cooling\",\"label\":\"Cooling\",\"type\":\"Number\",\"value\":49,\"min\":0,\"max\":255},{\"name\":\"sparking\",\"label\":\"Sparking\",\"type\":\"Number\",\"value\":60,\"min\":0,\"max\":255},{\"name\":\"twinkles\",\"label\":\"Twinkles\",\"type\":\"Section\"},{\"name\":\"twinkleSpeed\",\"label\":\"Twinkle Speed\",\"type\":\"Number\",\"value\":4,\"min\":0,\"max\":8},{\"name\":\"twinkleDensity\",\"label\":\"Twinkle Density\",\"type\":\"Number\",\"value\":5,\"min\":0,\"max\":8}]";
  menu.SetData(json);
  //menu.Redraw();
}
//================================================================
//   Loop-Code
//================================================================

void loop() {
  /*if(WiFi.status() != WL_CONNECTED){
    //ShowNoWlan();
    //ShowEntryInfo(String("Test"),String("Testmsg..\n1234..."));
    menu.ShowMsg("Nicht\nVerbunden");
  }else{
    //ShowMenu(MAIN_MENU,MAIN_MENU_SIZE);
    menu.ShowMsg("Verbunden");
  }//*/
  delay(100);
}

//================================================================
//   Additional Functions
//================================================================

/*
void ButtonPress(){
  if((millis() - ButtonStateTime) > 50){ 
    if( CURSOR_POS >= MENU_SIZE){
      CURSOR_POS = 1;
    }else{
      CURSOR_POS = CURSOR_POS + 1;
    }
    DoAction(CURSOR_POS);
    ButtonStateTime = millis();
  }
}

void DoAction(int ActionID){
  // Set Lamp-Mode
  HTTPClient http;
  http.begin("http://192.168.1.12/test.html"); //HTTP

  // start connection and send HTTP header
  int httpCode = http.GET();
  http.end();
}*/

