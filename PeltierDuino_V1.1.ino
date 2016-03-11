/************ PeltierDuino ************/
//--- BIBLIOTECAS 
#include <LiquidCrystal.h> 
#include <OneWire.h>
#include <Wire.h>
#include <RTClib.h>  
#include "Variaveis.h"
#include <Event.h>
#include <Timer.h>
#include <EEPROM.h>

//--- Inicializacao dos Sensores                                      
RTC_DS1307 RTC;

/* DS18S20 Temperature chip i/o */
OneWire  ds(2);  // on pin 9
#define MAX_DS1820_SENSORS 2
byte addr[MAX_DS1820_SENSORS][8];

// digital pins
#define RL1_PELTIER 3    //Power to peltier+fans
#define RL2_PUMP    4    //Power to 12v pump

//--- LCD Key Pad Panel 
LiquidCrystal lcd(12, 13, 11, 10, 9, 8); //nano
//LiquidCrystal lcd(13,12, 11, 10, 9, 8); //uno - Proteus

//--- KEYPAD
// define some values used by the panel and buttons
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define LCD_WIDTH 16
#define LCD_HEIGHT 2

//--- RTC - Definicao Chars 
const int DS1307 = 0x68; // Address of DS1307 see data sheets
const char* days[] =
{"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* months[] =
{"January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December"};
 
byte second = 0;
byte minute = 0;
byte hour = 0;
byte weekday = 0;
byte monthday = 0;
byte month = 0;
byte year = 0;


//--- VOID SETUP 
void setup() {
  
  Serial.begin(9600); 
  lcd.begin(LCD_WIDTH, LCD_HEIGHT);

  // Inicializacao do RTC
  Wire.begin();
  RTC.begin(); 
  
  lcd.clear();
  lcd.print(F("PeltierDuino V1"));
  
  for(int i=0; i<17; i++){
    lcd.setCursor(i,1);
    lcd.print("-");
    delay(50);
    }
    delay (500);
    
  
  // digital pins
  pinMode(RL1_PELTIER,OUTPUT); 
  pinMode(RL2_PUMP,OUTPUT); 
  
  digitalWrite(RL1_PELTIER,HIGH); 
  digitalWrite(RL2_PUMP,HIGH);
  
  if (!ds.search(addr[0]))
  {
    lcd.setCursor(0,0);
    lcd.print("No more addresses.");
    ds.reset_search();
    delay(1000);
    return;
  }
  if ( !ds.search(addr[1]))
  {
    lcd.setCursor(0,0);
    lcd.print("No more addresses.");
    ds.reset_search();
    delay(1000);
    return;
  }
  

  
  //--- Config values
 Config();            
             
//--- DESMARCAR PARA ACERTAR A HORA 
//Acertar_Hora();


//discoverOneWireDevices();

}
/**** fim do setup *****/



void loop() {
    Data_Print();
    Keypad();
    D18B20();
    Keypad();
    Control();
    Keypad();
}

//--- FIM VOID LOOP 


 byte decToBcd(byte val) {
  return ((val/10*16) + (val%10));
}
byte bcdToDec(byte val) {
  return ((val/16*10) + (val%16));
}

//---
void setTime() {
 
  Serial.print(F("Please enter the current year, 00-99. - "));
  year = readByte();
  Serial.println(year);
  Serial.print(F("Please enter the current month, 1-12. - "));
  month = readByte();
  Serial.println(months[month-1]);
  Serial.print(F("Please enter the current day of the month, 1-31. - "));
  monthday = readByte();
  Serial.println(monthday);
  Serial.println(F("Please enter the current day of the week, 1-7."));
  Serial.print(F("1 Sun | 2 Mon | 3 Tues | 4 Weds | 5 Thu | 6 Fri | 7 Sat - "));
  weekday = readByte();
  Serial.println(days[weekday-1]);
  Serial.print(F("Please enter the current hour in 24hr format, 0-23. - "));
  hour = readByte();
  Serial.println(hour);
  Serial.print(F("Please enter the current minute, 0-59. - "));
  minute = readByte();
  Serial.println(minute);
  second = 0;
  Serial.println(F("The data has been entered."));
 
  // The following codes transmits the data to the RTC
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(weekday));
  Wire.write(decToBcd(monthday));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.write(byte(0));
  Wire.endTransmission();
  // Ends transmission of data
}

byte readByte() {
  while (!Serial.available()) delay(10);
  byte reading = 0;
  byte incomingByte = Serial.read();
  while (incomingByte != '\n') {
    if (incomingByte >= '0' && incomingByte <= '9')
      reading = reading * 10 + (incomingByte - '0');
    else;
    incomingByte = Serial.read();
  }
  Serial.flush();
  return reading;
}

//---
void printTime() {
  char buffer[3];
  readTime();
  Serial.print(days[weekday-1]);
  Serial.print(F(" "));
  Serial.print(months[month-1]);
  Serial.print(F(" "));
  Serial.print(monthday);
  Serial.print(F(", 20"));
  Serial.print(year);
  Serial.print(F(" "));
  /*if (hour > 12) {
    hour -= 12;
    AMPM = " PM";
  }
  else AMPM = " AM";*/
  Serial.print(hour);
  Serial.print(F(":"));
  sprintf(buffer, "%02d", minute);
  Serial.print(buffer);
  //Serial.println(AMPM);
}

//---
void readTime() {
  Wire.beginTransmission(DS1307);
  Wire.write(byte(0));
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 7);
  second = bcdToDec(Wire.read());
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read());
  weekday = bcdToDec(Wire.read());
  monthday = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}

//--- FIM  DO PROGRAMA 



