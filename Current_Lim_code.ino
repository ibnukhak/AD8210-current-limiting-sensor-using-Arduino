#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);
int arus = A0;
int set = A1;
const byte interPin = 2;
int pinLed = 4;
bool kondisi = false;
byte oled = 1;
float data_arus;
float data_set;
void setup() {
  pinMode(arus,INPUT);
  pinMode(set,INPUT);
  pinMode(pinLed,OUTPUT);
  pinMode(interPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(interPin),kondisi_on,RISING);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
}

void loop() {
  int con_1 = analogRead(arus);
  int con_2 = analogRead(set);
  int data_1 = map(constrain(analogRead(arus),509,893),509,893,0,600);
  int data_2 = map(analogRead(set),0,1023,0,600);
  data_arus = data_1 * 0.01;
  data_set = data_2 * 0.01;
  if(data_arus > data_set && data_arus != data_set){
    kondisi = false;
    oled = 1;
  }else digitalWrite(pinLed,kondisi);
  digitalWrite(pinLed,kondisi);
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  for(int i=0; i<128; i++){
    display.drawPixel(i, 0, WHITE);
    display.drawPixel(i, 63, WHITE);
    display.drawPixel(i, 20, WHITE);
    display.drawPixel(i, 40, WHITE);
  }for(int j=0; j<64; j++){
    display.drawPixel(0, j, WHITE);
    display.drawPixel(127, j, WHITE);
    display.drawPixel(60, j, WHITE);
  }
  display.setCursor(10,7);
  display.print("Actual");
  display.setCursor(10,27);
  display.print("Setting");
  display.setCursor(74,7);display.print(data_arus);
  display.setCursor(103,7);
  display.print("A");
  display.setCursor(74,27);display.print(data_set);
  display.setCursor(103,27);
  display.print("A");
  display.setCursor(10,48);
  display.print("SWITCH");
  switch (oled) {
  case 0:
    display.setCursor(74,48);display.print("CLOSED");
    break;
  case 1:
    display.setCursor(74,48);display.print("OPEN");
    break;
  default:display.setCursor(74,48);display.print("OPEN");
  }
  display.display();
}

void kondisi_on(){
  kondisi = true;
  oled = 0;
}
