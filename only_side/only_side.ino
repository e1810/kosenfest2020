#include<time.h>
#include <Adafruit_NeoPixel.h>
#include<WiFi.h>

const char ssid[6] = "deemo";
const char passwd[10] = "humhumfoo";
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

const int PIN = 15;
const int PERIOD = 50000; //[microseconds]
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);
int sideLedData[19] = {0, 0, 0, 0, 10, 0, 0, 10, 0, 0, 12, 0, 0, 11, 0, 0, 11, 0, 0};
char sideChar1[13][6] = {".####", "..##.", ".####", ".####", ".#..#", ".####", ".####", ".####", ".####", ".####", "....#", ".....", "....."};
char sideChar2[13][6] = {".####", ".###.", ".####", ".####", ".#..#", ".####", ".####", ".####", ".####", ".####", "....#", ".....", "....."};
char sideChar3[13][6] = {".#..#", ".###.", "....#", "....#", ".#..#", ".#...", ".##..", "....#", ".#..#", ".#..#", "...#.", "..#..", "....."};
char sideChar4[13][6] = {".#..#", "..##.", ".####", ".####", ".####", ".####", ".####", "....#", ".####", ".####", "...#.", ".....", "....."};
char sideChar5[13][6] = {".#..#", "..##.", ".####", ".####", ".####", ".####", ".####", "....#", ".####", ".####", "..#..", ".....", "....."};
char sideChar6[13][6] = {".#..#", "..##.", ".#...", "....#", "....#", "....#", ".#..#", "....#", ".#..#", "....#", "..#..", ".....", "....."};
char sideChar7[13][6] = {".####", "..##.", ".####", ".####", "....#", ".####", ".####", "....#", ".####", ".####", ".#...", "..#..", "....."};
char sideChar8[13][6] = {".####", ".####", ".####", ".####", "....#", ".####", ".####", "....#", ".####", ".####", ".#...", ".....", "....."};
int topLedData[2][2][3] = {{{0,0,0}, {0,0,0}}, {{0,0,0}, {0,0,0}}};

//-----functions for side led---------
void setData(int* timeData, int offset, int digits, int num) {
  while (digits) {
    digits--;
    timeData[offset + digits] = num % 10;
    num /= 10;
  }
}


void setupSideLed(int* timeData) {
  time_t _now = time(0);
  tm *now = localtime(&_now);
  
  setData(timeData, 0, 4, now->tm_year + 1900);
  setData(timeData, 5, 2, now->tm_mon+1);
  setData(timeData, 8, 2, now->tm_mday);
  setData(timeData, 11, 2, (now->tm_hour+7)%24);
  setData(timeData, 14, 2, now->tm_min);
  setData(timeData, 17, 2, now->tm_sec);
}


void glowSideLed(int deg) {
  if(deg>=190){
    for(int i=16; i<24; i++) pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
    return;
  }

  int I = deg / 10, J = deg % 10/2; 
  if(sideChar1[sideLedData[I]][J]=='#') pixels.setPixelColor(16, pixels.Color(0, 0, 100));
  else pixels.setPixelColor(16, pixels.Color(0, 0, 0));
  if(sideChar2[sideLedData[I]][J]=='#') pixels.setPixelColor(17, pixels.Color(0, 0, 100));
  else pixels.setPixelColor(17, pixels.Color(0, 0, 0));
  if(sideChar3[sideLedData[I]][J]=='#') pixels.setPixelColor(18, pixels.Color(0, 0, 100));
  else pixels.setPixelColor(18, pixels.Color(0, 0, 0));
  if(sideChar4[sideLedData[I]][J]=='#') pixels.setPixelColor(19, pixels.Color(0, 0, 100));
  else pixels.setPixelColor(19, pixels.Color(0, 0, 0));
  if(sideChar5[sideLedData[I]][J]=='#') pixels.setPixelColor(20, pixels.Color(0, 0, 100));
  else pixels.setPixelColor(20, pixels.Color(0, 0, 0));
  if(sideChar6[sideLedData[I]][J]=='#') pixels.setPixelColor(21, pixels.Color(0, 0, 100));
  else pixels.setPixelColor(21, pixels.Color(0, 0, 0));
  if(sideChar7[sideLedData[I]][J]=='#') pixels.setPixelColor(22, pixels.Color(0, 0, 100));
  else pixels.setPixelColor(22, pixels.Color(0, 0, 0));
  if(sideChar8[sideLedData[I]][J]=='#') pixels.setPixelColor(23, pixels.Color(0, 0, 100));
  else pixels.setPixelColor(23, pixels.Color(0, 0, 0));

  pixels.show();
}


//-----general functions --------
void drawClock(){
  setupSideLed(sideLedData);
  for(int i=0; i<360; i+=2){
    glowSideLed(i);
  }
  //delayMicroseconds(10);
}


void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}



//-------main functions------------
void setup(){
  Serial.begin(9600);
  pixels.begin();
  
  WiFi.begin(ssid, passwd);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.println("wait for connecting...");
  }
  Serial.println(" CONNECTED");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  for(int i=0; i<16; i++){
    if(i<4) pixels.setPixelColor(i, pixels.Color(0, 50, 50));
    else if(i<8) pixels.setPixelColor(i, pixels.Color(0, 50, 0));
    else if(i<12) pixels.setPixelColor(i, pixels.Color(50, 50, 0));
    else pixels.setPixelColor(i, pixels.Color(50, 0, 0));
  }
  pixels.show();
}


void loop(){
  //Serial.println(millis());
  //printLocalTime();
  drawClock();
}
