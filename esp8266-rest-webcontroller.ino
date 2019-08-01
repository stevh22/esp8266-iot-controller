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
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SimpleMenu menu(display);

int CURSOR_POS = 1;
int MENU_SIZE = 0;
int DISPLAY_OFFSET = 0;
volatile unsigned long ButtonStateTime = 0;

//================================================================
//   Setup-Code
//================================================================

void setup() {
  // init OLED-Display
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR); 
  display.clearDisplay();
  display.display();

  // for Buttons
  pinMode(KEY_BUTTON, INPUT_PULLUP);
  //attachInterrupt(KEY_BUTTON, ButtonPress, FALLING);

  // start Menu
  menu.SetMsg("Suche Wlan");

  // connect to Wlan
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
}

//================================================================
//   Loop-Code
//================================================================

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    //ShowNoWlan();
    //ShowEntryInfo(String("Test"),String("Testmsg..\n1234..."));
    menu.SetMsg("Verbunden");
  }else{
    //ShowMenu(MAIN_MENU,MAIN_MENU_SIZE);
    menu.SetMsg("Nicht Verbunden");
  }
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
}

void ShowMenu(String MenuArray[],int MenuSize){
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
}

void ShowEntryInfo(String EntryTitle, String EntryInfo){
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
}

void ShowNoWlan(){
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(TEXT_COLOR);
  display.println("");
  display.println("Kein WLAN");
  display.display();
}/*/
